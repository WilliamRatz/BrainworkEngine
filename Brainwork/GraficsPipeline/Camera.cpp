#include "Camera.h"

Camera Camera::getViewCamera = Camera();

Camera::Camera()
{
	mat[3][2] = 5.0;
}

Camera::Camera(const Camera& cam)
{
	mat = cam.mat;
}

Camera::~Camera()
{
}

void Camera::SetCameraToWindow(GLFWwindow* window)
{
	Camera::getViewCamera = *this;
	glfwSetKeyCallback(window, Camera::Camera_key_callback);
	glfwSetCursorPosCallback(window, Camera::Cursor_position_callback);
	glfwSetMouseButtonCallback(window, Camera::Mouse_button_callback);
}

void Camera::Camera_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {





	if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		Camera::getViewCamera.MoveForward();
		std::cout << "W MoveForward" << std::endl;
	}
	if (key == GLFW_KEY_A && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		Camera::getViewCamera.MoveLeft();
		std::cout << "A MoveLeft" << std::endl;
	}
	if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		Camera::getViewCamera.MoveBackward();
		std::cout << "S MoveBackward" << std::endl;
	}
	if (key == GLFW_KEY_D && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		Camera::getViewCamera.MoveRight();
		std::cout << "D MoveRight" << std::endl;
	}
	if (key == GLFW_KEY_Q && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		Camera::getViewCamera.MoveUp();
		std::cout << "Q MoveUp" << std::endl;
	}
	if (key == GLFW_KEY_E && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
		Camera::getViewCamera.MoveDown();
		std::cout << "E MoveDown" << std::endl;
	}
}

void Camera::Mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		Camera::getViewCamera.dragging = true;
		glfwGetCursorPos(window, &Camera::getViewCamera.cursorPosX, &Camera::getViewCamera.cursorPosY);
	}
	else
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		{
			Camera::getViewCamera.dragging = false;
		}
	}
}

void Camera::Cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (Camera::getViewCamera.dragging)
	{

		double tempX = Camera::getViewCamera.cursorPosX;
		double tempY = Camera::getViewCamera.cursorPosY;
		glfwGetCursorPos(window, &Camera::getViewCamera.cursorPosX, &Camera::getViewCamera.cursorPosY);
		Camera::getViewCamera.mat.rotation3DAroundY(tempX - Camera::getViewCamera.cursorPosX);
		Camera::getViewCamera.mat.rotation3DAroundX(tempY - Camera::getViewCamera.cursorPosY);
		std::cout << tempX - Camera::getViewCamera.cursorPosX << std::endl;
		std::cout << tempY - Camera::getViewCamera.cursorPosY << std::endl;
	}

}

Matrix<float, 4, 4> Camera::MoveForward()
{
	Matrix<float, 4, 4> tempMat;
	tempMat.translate3D(0, 0, -0.01 * moveSpeed);
	tempMat = tempMat.transpose();
	mat *= tempMat;
	return mat;
}
Matrix<float, 4, 4> Camera::MoveBackward()
{
	Matrix<float, 4, 4> tempMat;
	tempMat.translate3D(0, 0, 0.01* moveSpeed);
	tempMat = tempMat.transpose();
	mat *= tempMat;
	return mat;
}
Matrix<float, 4, 4> Camera::MoveLeft()
{
	Matrix<float, 4, 4> tempMat;
	tempMat.translate3D(0.01* moveSpeed, 0, 0);
	tempMat = tempMat.transpose();
	mat *= tempMat;
	return mat;
}
Matrix<float, 4, 4> Camera::MoveRight()
{
	Matrix<float, 4, 4> tempMat;
	tempMat.translate3D(-0.01* moveSpeed, 0, 0);
	tempMat = tempMat.transpose();
	mat *= tempMat;
	return mat;
}
Matrix<float, 4, 4> Camera::MoveUp()
{
	Matrix<float, 4, 4> tempMat;
	tempMat.translate3D(0, 0.01* moveSpeed, 0);
	tempMat = tempMat.transpose();
	mat *= tempMat;
	return mat;
}
Matrix<float, 4, 4> Camera::MoveDown()
{
	Matrix<float, 4, 4> tempMat;
	tempMat.translate3D(0, -0.01* moveSpeed, 0);
	tempMat = tempMat.transpose();
	mat *= tempMat;
	return mat;
}