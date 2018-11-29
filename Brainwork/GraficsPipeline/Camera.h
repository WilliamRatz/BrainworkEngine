#ifndef CAMERA_H
#define CAMERA_H
#include "VK_Object.h"

static void Camera_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
class Camera
{
private:
	static void DOOO() {

	}
public:
	Matrix<float, 4, 4> mat;
	
	~Camera();

	friend static void Camera_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	Camera()
	{
		glfwSetKeyCallback(VK_Object::window, Camera_key_callback);

	}
};

static void Camera_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Camera::DOOO();
	if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		std::cout << "W";
	}
	if (key == GLFW_KEY_A && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		std::cout << "A";
	}
	if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		std::cout << "S";
	}
	if (key == GLFW_KEY_D && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		std::cout << "D";
	}
	if (key == GLFW_KEY_Q && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		std::cout << "Q";
	}
	if (key == GLFW_KEY_E && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		std::cout << "E";
	}
}

#endif // !CAMERA_H