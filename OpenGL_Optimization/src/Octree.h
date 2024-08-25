#pragma once

#include <vector>
#include <memory>
#include <array>
#include <glm/glm.hpp>

// Struct to hold the object and its position

// Structure representing the bounds of an Octree node
struct BoundingBox {
    glm::vec3 center;   // Center of the bounding box
    glm::vec3 halfSize; // Half the size of the bounding box in each dimension

    bool containsPoint(const glm::vec3& point) const {
        return (point.x >= center.x - halfSize.x && point.x <= center.x + halfSize.x) &&
            (point.y >= center.y - halfSize.y && point.y <= center.y + halfSize.y) &&
            (point.z >= center.z - halfSize.z && point.z <= center.z + halfSize.z);
    }

    bool intersectsBox(const BoundingBox& other) const {
        return (center.x - halfSize.x <= other.center.x + other.halfSize.x &&
            center.x + halfSize.x >= other.center.x - other.halfSize.x &&
            center.y - halfSize.y <= other.center.y + other.halfSize.y &&
            center.y + halfSize.y >= other.center.y - other.halfSize.y &&
            center.z - halfSize.z <= other.center.z + other.halfSize.z &&
            center.z + halfSize.z >= other.center.z - other.halfSize.z);
    }
};

// Templated Octree class
template <typename T>
class Octree {
public:
    Octree(BoundingBox boundary, int capacity)
        : m_Bounds(boundary), m_Capacity(capacity), m_Divided(false) {}


    bool Insert(T* object, const glm::vec3& position, int count = 0) {
        if (!m_Divided) {
            if (m_Objects.size() < m_Capacity) {
                m_Objects.push_back({ object, position });
                return true;
            }
            else {
                Subdivide();
                Insert(object, position);
            }
        }

        // After 20 insert trials break
        if (count == 20) return false;

        for (int i = 0; i < 8; i++) {
            if (m_Children[i]->GetBounds()->containsPoint(position)) {
                m_Children[i]->Insert(object, position, count++);
            }
        }
    }

    void Subdivide() {
        glm::vec3 newHalfSize = m_Bounds.halfSize / 2.0f;
        glm::vec3 offset[8] = {
            glm::vec3(-newHalfSize.x, newHalfSize.y, -newHalfSize.z),
            glm::vec3(newHalfSize.x, newHalfSize.y, -newHalfSize.z),
            glm::vec3(-newHalfSize.x, newHalfSize.y, newHalfSize.z),
            glm::vec3(newHalfSize.x, newHalfSize.y, newHalfSize.z),
            glm::vec3(-newHalfSize.x, -newHalfSize.y, -newHalfSize.z),
            glm::vec3(newHalfSize.x, -newHalfSize.y, -newHalfSize.z),
            glm::vec3(-newHalfSize.x, -newHalfSize.y, newHalfSize.z),
            glm::vec3(newHalfSize.x, -newHalfSize.y, newHalfSize.z)
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

    std::vector<T*> GetObjectsInPoint(glm::vec3 point) {
        std::vector<T*> result;
        Octree<T>* tree = SubSpaceContainingPoint(point);
        for (int i = 0; i < tree->m_Objects.size(); i++) {
            result.push_back(tree->m_Objects[i].object);
        }
        return result;
    }

    Octree<T>* SubSpaceContainingPoint(glm::vec3 point) {
        if (!m_Divided) {
            if (m_Bounds.containsPoint(point)) {
                return this;
            }
            return nullptr; 
        }

        for (int i = 0; i < 8; ++i) {
            if (m_Children[i] && m_Children[i]->m_Bounds.containsPoint(point)) {
                return m_Children[i]->SubSpaceContainingPoint(point);
            }
        }

        return nullptr;
    }

    BoundingBox* GetBounds() {
        return &m_Bounds;
    }

private:
    struct OctreeData {
        T* object;
        glm::vec3 position;
    };

    BoundingBox m_Bounds; 
    std::vector<OctreeData> m_Objects;
    std::array<std::unique_ptr<Octree<T>>, 8> m_Children;
    int m_Capacity;         
    bool m_Divided; 
};