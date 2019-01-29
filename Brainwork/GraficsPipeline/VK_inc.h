#ifndef VK_INC
#define VK_INC

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>


#include <BW_Inc.h>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <chrono>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <array>
#include <optional>
#include <set>

const int WIDTH = 1000;
const int HEIGHT = 800;

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

struct UniformBufferObject {
	Matrix<float, 4, 4> model;
	Matrix<float, 4, 4> view;
	Matrix<float, 4, 4> proj;
	Matrix<float, 4, 4> lightView;

	Vector4 groundColor;
};

struct LightInfoObject {
	Matrix<float, 4, 4> model;
	Matrix<float, 4, 4> lightView;
	Matrix<float, 4, 4> proj;
};

#define Print(x) std::cout << x << std::endl;


#endif // !VK_INC