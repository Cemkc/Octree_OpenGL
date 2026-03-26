[![Octree Optimization Showcase](https://img.youtube.com/vi/ZJ1vbPq08L4/maxresdefault.jpg)](https://www.youtube.com/watch?v=ZJ1vbPq08L4)
*Click the image above to watch the full technical breakdown and demonstration.*

## 📌 Project Overview
This project was engineered to solve a specific, high-level architectural case study: *"How do you optimize distance-checking operations in a densely populated 3D scene?"* To answer this, I developed a custom C++ and OpenGL benchmarking application that visually and mathematically compares brute-force O(n²) spatial queries against an optimized O(log n) **Octree Spatial Partitioning** algorithm. The application allows users to dynamically switch between rendering methods at runtime to observe the massive differences in CPU overhead and framerate stability.

## 🛠️ Tech Stack
* **Language:** C++
* **Graphics API:** OpenGL / GLSL
* **Libraries:** GLFW, GLEW, GLM (Mathematics)
* **UI:** Dear ImGui

## 🚀 Technical & Optimization Highlights

### Algorithmic Complexity Reduction (O(n²) vs O(log n))
In a brute-force scenario, every object in the scene must calculate its distance relative to the camera, resulting in an exponential processing bottleneck as entity counts rise. 
* By engineering a custom, templated `Octree` data structure, the 3D space is recursively subdivided into 8 bounding boxes.
* The algorithm eliminates unnecessary distance checks by only evaluating objects residing within the camera's active or adjacent sub-nodes, drastically reducing CPU load.

### Hardware Isolation & Bottleneck Profiling
To ensure the benchmarking tool was accurately measuring spatial partitioning efficiency rather than GPU rendering limits, I deliberately isolated the CPU. 
* Injected a heavy mathematical operation (a 10,000-iteration `sqrt` loop) into the `Update()` method of each active game object. 
* This guaranteed that the performance bottleneck was strictly CPU-bound, providing an accurate, real-world stress test for the Octree algorithm.

### Visual Debugging & State Management
Implemented a real-time color-coding system to visually debug the algorithmic culling:
* 🔴 **Red:** Object is culled/inactive (bypassing the heavy logic loop).
* 🟡 **Yellow:** Object is active and evaluating its distance, but outside the threshold.
* 🔵 **Blue:** Object is active and within the camera's collision radius.

## 💻 Code Architecture: Octree Subdivision
*The core spatial partitioning logic. When a node exceeds its capacity, it recursively subdivides the 3D space into 8 uniform child bounds and reallocates its contained entities.*

```cpp
void Subdivide() {
    glm::vec3 newHalfSize = m_Bounds.halfSize / 2.0f;
    glm::vec3 offset[8] = {
        glm::vec3(-newHalfSize.x,  newHalfSize.y, -newHalfSize.z),
        glm::vec3( newHalfSize.x,  newHalfSize.y, -newHalfSize.z),
        glm::vec3(-newHalfSize.x,  newHalfSize.y,  newHalfSize.z),
        glm::vec3( newHalfSize.x,  newHalfSize.y,  newHalfSize.z),
        glm::vec3(-newHalfSize.x, -newHalfSize.y, -newHalfSize.z),
        glm::vec3( newHalfSize.x, -newHalfSize.y, -newHalfSize.z),
        glm::vec3(-newHalfSize.x, -newHalfSize.y,  newHalfSize.z),
        glm::vec3( newHalfSize.x, -newHalfSize.y,  newHalfSize.z)
    };

    for (int i = 0; i < 8; ++i) {
        BoundingBox childBox{
            m_Bounds.center + offset[i],
            newHalfSize
        };
        m_Children[i] = std::make_unique<Octree<T>>(childBox, m_Capacity);

        std::vector<OctreeData> objectData;
        for (int j = 0; j < m_Objects.size(); j++) {
            if (childBox.containsPoint((m_Objects[j].position))) {
                objectData.push_back(m_Objects[j]);
            }
        }
        m_Children[i]->m_Objects = objectData;
    }

    m_Objects.clear();
    m_Divided = true;
}
