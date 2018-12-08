#ifndef CAMERA_H
#define CAMERA_H
#include <BW_Math.h>
#include "Controls.h"

class Camera
{
private:
	Matrix<float, 4, 4> MoveForward();
	Matrix<float, 4, 4> MoveBackward();
	Matrix<float, 4, 4> MoveLeft();
	Matrix<float, 4, 4> MoveRight();
	Matrix<float, 4, 4> MoveUp();
	Matrix<float, 4, 4> MoveDown();

	

public:
	Matrix<float, 4, 4> mat;
	float moveSpeed = 0.01;

	
	static void CameraUpdate(GLFWwindow *window);

	static Camera getViewCamera;

	Camera();
	Camera(const Camera& cam);
	~Camera();

	void SetCameraToWindow(GLFWwindow* window);
};

#endif // !CAMERA_H
