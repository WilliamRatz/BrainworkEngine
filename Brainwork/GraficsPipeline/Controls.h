#ifndef CONTROLS_H
#define CONTROLS_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class Controls
{
public:
	static bool		W_PRESSING;
	static bool		A_PRESSING;
	static bool		D_PRESSING;
	static bool		S_PRESSING;
	static bool		Q_PRESSING;
	static bool		E_PRESSING;

	static bool		ARROW_UP_PRESSING;
	static bool		ARROW_LEFT_PRESSING;
	static bool		ARROW_RIGHT_PRESSING;
	static bool		ARROW_DOWN_PRESSING;
	
	static bool		MOUSE_LEFT_PRESSING;
	static bool		MOUSE_RIGHT_PRESSING;

	static double	CURSOR_POS_X;
	static double	CURSOR_POS_Y;


	static void		key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void		Mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void		Cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
};

#endif // !CONTROLS_H
