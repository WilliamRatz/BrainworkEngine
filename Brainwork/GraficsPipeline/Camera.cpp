#include "Camera.h"

Camera Camera::ViewCamera = Camera();

Camera::Camera()
{
	m_matrix.translate3D(0, 0, 5);
}

Camera::Camera(const Camera& cam)
{
	m_matrix = cam.m_matrix;
}

Camera::~Camera()
{
}

void Camera::CameraUpdate(GLFWwindow *window)
{
	if (Controls::W_PRESSING || Controls::ARROW_UP_PRESSING)
	{
		Camera::ViewCamera.MoveForward();
	}

	if (Controls::A_PRESSING || Controls::ARROW_LEFT_PRESSING)
	{
		Camera::ViewCamera.MoveLeft();
	}

	if (Controls::D_PRESSING || Controls::ARROW_RIGHT_PRESSING)
	{
		Camera::ViewCamera.MoveRight();
	}

	if (Controls::S_PRESSING || Controls::ARROW_DOWN_PRESSING)
	{
		Camera::ViewCamera.MoveBackward();
	}

	if (Controls::Q_PRESSING)
	{
		Camera::ViewCamera.MoveUp();
	}

	if (Controls::E_PRESSING)
	{
		Camera::ViewCamera.MoveDown();

	}

	if (Controls::MOUSE_LEFT_PRESSING) 
	{
		double tempX = Controls::CURSOR_POS_X;
		double tempY = Controls::CURSOR_POS_Y;
		glfwGetCursorPos(window, &Controls::CURSOR_POS_X, &Controls::CURSOR_POS_Y);
		
		Camera::ViewCamera.RotateCamera(tempX, tempY);
	}
}

Matrix<float, 4, 4> Camera::GetCameraMatrix()
{
	return m_matrix.transpose();
}

void Camera::SetCameraToWindow(GLFWwindow* window)
{
	Camera::ViewCamera = *this;
	glfwSetKeyCallback(window, Controls::key_callback);
	glfwSetCursorPosCallback(window, Controls::Cursor_position_callback);
	glfwSetMouseButtonCallback(window, Controls::Mouse_button_callback);
}

void Camera::MoveForward()
{
	m_matrix.translate3D(0, 0, -m_moveSpeed);
}
void Camera::MoveBackward()
{
	m_matrix.translate3D(0, 0, m_moveSpeed);
}
void Camera::MoveLeft()
{
	m_matrix.translate3D(m_moveSpeed, 0, 0);
}
void Camera::MoveRight()
{
	m_matrix.translate3D(-m_moveSpeed, 0, 0);
}
void Camera::MoveUp()
{
	m_matrix.translate3D(0, m_moveSpeed, 0);
}
void Camera::MoveDown()
{
	m_matrix.translate3D(0, -m_moveSpeed, 0);
}
void Camera::RotateCamera(double p_cursorX, double p_cursorY)
{
	m_matrix.rotation3DAroundXlocal((p_cursorY - Controls::CURSOR_POS_Y)*m_rotationSpeed);
	m_matrix.rotation3DAroundYlocal((p_cursorX - Controls::CURSOR_POS_X)*m_rotationSpeed);
}
