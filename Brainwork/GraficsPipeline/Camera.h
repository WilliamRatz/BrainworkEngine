#ifndef CAMERA_H
#define CAMERA_H
#include <Inc_BWMath.h>
#include "Controls.h"

class Camera
{
private:
	Matrix<float, 4, 4> m_rotationMatrix;
	Matrix<float, 4, 4> m_transformMatrix;
	float				m_moveSpeed = 0.001f;
	float				m_rotationSpeed = 0.061f;

	void MoveForward();
	void MoveBackward();
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	void RotateCamera(double cursorX, double cursorY);

public:
	static	Camera		ViewCamera;
	Camera				();
	Camera				(const Camera& cam);
	~Camera				();

	Matrix<float, 4, 4> GetCameraMatrix();
	void				SetCameraToWindow(GLFWwindow* window);
	
	static	void		CameraUpdate(GLFWwindow *window);
};

#endif // CAMERA_H
