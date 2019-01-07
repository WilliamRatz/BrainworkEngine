#ifndef VK_INC
#define VK_INC

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
//


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

const int WIDTH = 1920;
const int HEIGHT = 1080;

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

#endif // !VK_INC