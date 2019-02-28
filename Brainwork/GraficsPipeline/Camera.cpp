#include "Camera.h"

Camera Camera::ViewCamera = Camera();

Camera::Camera()
{
	m_transformMatrix.translate3D(8, 0, 5);
}

Camera::Camera(const Camera& cam)
{
	m_transformMatrix = cam.m_transformMatrix;
	m_rotationMatrix = cam.m_rotationMatrix;
}

Camera::~Camera()
{
}

void Camera::CameraUpdate(GLFWwindow *window)
{
	
	Camera::ViewCamera.m_moveSpeed = 0.001 * Controls::SCROLL_OFFSET_Y;
	
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
	return (m_rotationMatrix * m_transformMatrix).transpose();
}

void Camera::SetCameraToWindow(GLFWwindow* window)
{
	Camera::ViewCamera = *this;
	glfwSetKeyCallback(window, Controls::Key_callback);
	glfwSetCursorPosCallback(window, Controls::Cursor_position_callback);
	glfwSetMouseButtonCallback(window, Controls::Mouse_button_callback);
	glfwSetScrollCallback(window, Controls::Scroll_callback);
}

void Camera::MoveForward()
{
	m_transformMatrix.translate3D(this->GetCameraMatrix().Backwards().normalize() * m_moveSpeed);
}
void Camera::MoveBackward()
{
	m_transformMatrix.translate3D(this->GetCameraMatrix().Forward().normalize() * m_moveSpeed);
}
void Camera::MoveLeft()
{
	m_transformMatrix.translate3D(this->GetCameraMatrix().Right().normalize() * m_moveSpeed);
}
void Camera::MoveRight()
{
	m_transformMatrix.translate3D(this->GetCameraMatrix().Left().normalize() * m_moveSpeed);
}
void Camera::MoveUp()
{
	m_transformMatrix.translate3D(0, m_moveSpeed, 0);
}
void Camera::MoveDown()
{
	m_transformMatrix.translate3D(0, -m_moveSpeed, 0);

}
void Camera::RotateCamera(double p_cursorX, double p_cursorY)
{
	//m_rotationMatrix.rotation3DAroundArbitararyAxis(m_rotationSpeed, m_transformMatrix.getTransform().normalize());
	m_rotationMatrix.rotation3DAroundY((p_cursorX - Controls::CURSOR_POS_X)*m_rotationSpeed);
	m_rotationMatrix.rotation3DAroundX((p_cursorY - Controls::CURSOR_POS_Y)*m_rotationSpeed);
}

