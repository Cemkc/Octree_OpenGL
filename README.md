# Distance Based Optimization Using Octree

This repository contains the source code for an application aimed to show the optimization methods that can be used to instantiate many objects in a 3D scene without sacrificing signifcant performance.

## How to use

After installing the folder that contains the exe file, run the exe file. 
Upon launching the application, the user will be presented with a configuration menu. Using this menu, certain settings can be adjusted before the scene is loaded.

![Configuration Menu](/githubAssets/Images/ConfigMenu.png)

**Number of objects to spawn**</br>
Determines how many objects will be spawned to the scene.</br>
If the algorithm is set to `BRUTE_FORCE` all the objects that are spawned will run their Update() methods. It is recommended to not exceed 5000.

**Algorithm To Use**</br>
When the button is clicked it will switch between `BRUTE_FORCE` and `OCTREE`.

**Object Initialization Method**</br>
When the button is clicked it will switch between `RANDOM` and `GRID`.</br>
- `RANDOM` spawns objects randomly withing the boundaries.</br>
- `GRID` spawns objects on a grid.

**Start Scene**</br>
User can run the scene after they are satisfied with their configurations by clicking the "Demo Scene" button.</br>

## Controls

- Mouse to adjust camera rotation (sensitivity can be set from the scene menu).
- WASD to move the camera on forwards and right directions.
- E to move the camera on positive up direction.
- Q to move the camera on negative up direction.
- LShift to increase the speed of the camera.
- ESC to Enable cursor and interact with UI.

## Key Points

### Object Logic

Each instantiated object besides of being rendered, run thier `Update()` methods. The `Update()` method checks if the camera is at a certain distance to the calling object and if it is, sets the color of the object to blue.</br>
`Update()` method contains the following code:
```c++
void GameObject::Update()
{
	if (glm::length(scene::CameraWithCube::cameraPos - transform.position) < 1.5f) {
		color = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	}

	double sum = 0.0;
	for (int i = 0; i < 10000; ++i) {
		sum += sqrt(i * 0.001);
	}

}
```
Along with the distance check logic, each object runs a for loop that performs a square root operation. This is done so that the performance bottleneck is caused by the CPU rather than GPU.

### Color Coding

Each object in the scene can take 3 different collor; red, blue, yellow That indicates behaviour of the object.
- If the object is red; the object is not running it's logic code.
- If the object is yellow; the object is running it's logic code.
- If the object is blue; the object is running it's logic code and Camera is closer than a certain distance to the object.

## How to read

When the scene is loaded user can inspect Frame Rate value and current running algorith from the UI menu.</br>

![Scene Menu](/githubAssets/Images/MainSceneMenu.png)

## Demonstration Video
