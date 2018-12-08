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

void Camera::CameraUpdate(GLFWwindow *window)
{
	if (Controls::W_PRESSING || Controls::ARROW_UP_PRESSING)
	{
		Camera::getViewCamera.MoveForward();
	}

	if (Controls::A_PRESSING || Controls::ARROW_LEFT_PRESSING)
	{
		Camera::getViewCamera.MoveLeft();
	}

	if (Controls::D_PRESSING || Controls::ARROW_RIGHT_PRESSING)
	{
		Camera::getViewCamera.MoveRight();
	}

	if (Controls::S_PRESSING || Controls::ARROW_DOWN_PRESSING)
	{
		Camera::getViewCamera.MoveBackward();
	}

	if (Controls::Q_PRESSING)
	{
		Camera::getViewCamera.MoveUp();
	}

	if (Controls::E_PRESSING)
	{
		Camera::getViewCamera.MoveDown();

	}

	if (Controls::MOUSE_LEFT_PRESSING) 
	{
		double tempX = Controls::CURSOR_POS_X;
		double tempY = Controls::CURSOR_POS_Y;
		glfwGetCursorPos(window, &Controls::CURSOR_POS_X, &Controls::CURSOR_POS_Y);
		Camera::getViewCamera.mat.rotation3DAroundY(tempX - Controls::CURSOR_POS_X);
		Camera::getViewCamera.mat.rotation3DAroundX(tempY - Controls::CURSOR_POS_Y);
	}
}

void Camera::SetCameraToWindow(GLFWwindow* window)
{
	Camera::getViewCamera = *this;
	glfwSetKeyCallback(window, Controls::key_callback);
	glfwSetCursorPosCallback(window, Controls::Cursor_position_callback);
	glfwSetMouseButtonCallback(window, Controls::Mouse_button_callback);
}





Matrix<float, 4, 4> Camera::MoveForward()
{
	Matrix<float, 4, 4> tempMat;
	tempMat.translate3D(0, 0, -moveSpeed);
	tempMat = tempMat.transpose();
	mat *= tempMat;
	return mat;
}
Matrix<float, 4, 4> Camera::MoveBackward()
{
	Matrix<float, 4, 4> tempMat;
	tempMat.translate3D(0, 0, moveSpeed);
	tempMat = tempMat.transpose();
	mat *= tempMat;
	return mat;
}
Matrix<float, 4, 4> Camera::MoveLeft()
{
	Matrix<float, 4, 4> tempMat;
	tempMat.translate3D(moveSpeed, 0, 0);
	tempMat = tempMat.transpose();
	mat *= tempMat;
	return mat;
}
Matrix<float, 4, 4> Camera::MoveRight()
{
	Matrix<float, 4, 4> tempMat;
	tempMat.translate3D(-moveSpeed, 0, 0);
	tempMat = tempMat.transpose();
	mat *= tempMat;
	return mat;
}
Matrix<float, 4, 4> Camera::MoveUp()
{
	Matrix<float, 4, 4> tempMat;
	tempMat.translate3D(0, moveSpeed, 0);
	tempMat = tempMat.transpose();
	mat *= tempMat;
	return mat;
}
Matrix<float, 4, 4> Camera::MoveDown()
{
	Matrix<float, 4, 4> tempMat;
	tempMat.translate3D(0, -moveSpeed, 0);
	tempMat = tempMat.transpose();
	mat *= tempMat;
	return mat;
}