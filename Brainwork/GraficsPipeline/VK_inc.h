#ifndef VK_INC
#define VK_INC

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <BW_Math.h>
#include <iostream>
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

const int WIDTH = 800;
const int HEIGHT = 800;

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

#endif // !VK_INC