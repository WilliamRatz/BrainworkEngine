#ifndef CAMERA_H
#define CAMERA_H
#include "VK_Object.h"

class Camera
{
private:
	Matrix<float, 4, 4> MoveForward();
	Matrix<float, 4, 4> MoveBackward();
	Matrix<float, 4, 4> MoveLeft();
	Matrix<float, 4, 4> MoveRight();
	Matrix<float, 4, 4> MoveUp();
	Matrix<float, 4, 4> MoveDown();

	double cursorPosX;
	double cursorPosY;

	bool dragging;

public:
	Matrix<float, 4, 4> mat;
	float moveSpeed = 5;
	static void Camera_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void Mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void Cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	

	static Camera getViewCamera;

	Camera();
	Camera(const Camera& cam);
	~Camera();

	void SetCameraToWindow(GLFWwindow* window);
};

#endif // !CAMERA_H
