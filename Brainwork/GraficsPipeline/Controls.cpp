#include "Controls.h"

bool Controls::W_PRESSING = false;
bool Controls::A_PRESSING = false;
bool Controls::D_PRESSING = false;
bool Controls::S_PRESSING = false;
bool Controls::Q_PRESSING = false;
bool Controls::E_PRESSING = false;

bool Controls::ARROW_UP_PRESSING = false;
bool Controls::ARROW_LEFT_PRESSING = false;
bool Controls::ARROW_RIGHT_PRESSING = false;
bool Controls::ARROW_DOWN_PRESSING = false;

bool Controls::MOUSE_LEFT_PRESSING = false;
bool Controls::MOUSE_RIGHT_PRESSING = false;

double Controls::CURSOR_POS_X = 0.0;
double Controls::CURSOR_POS_Y = 0.0;

double Controls::SCROLL_OFFSET_X = 1.0;
double Controls::SCROLL_OFFSET_Y = 1.0;

void Controls::Key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_W:
			W_PRESSING = true;
			return;

		case GLFW_KEY_A:
			A_PRESSING = true;
			return;

		case GLFW_KEY_D:
			D_PRESSING = true;
			return;

		case GLFW_KEY_S:
			S_PRESSING = true;
			return;

		case GLFW_KEY_Q:
			Q_PRESSING = true;
			return;

		case GLFW_KEY_E:
			E_PRESSING = true;
			return;

		case GLFW_KEY_UP:
			ARROW_UP_PRESSING = true;
			return;

		case GLFW_KEY_LEFT:
			ARROW_LEFT_PRESSING = true;
			return;

		case GLFW_KEY_RIGHT:
			ARROW_RIGHT_PRESSING = true;
			return;

		case GLFW_KEY_DOWN:
			ARROW_DOWN_PRESSING = true;
			return;

		}
	}
	else if (action == GLFW_RELEASE)
	{
		switch (key)
		{
		case GLFW_KEY_W:
			W_PRESSING = false;
			return;

		case GLFW_KEY_A:
			A_PRESSING = false;
			return;

		case GLFW_KEY_D:
			D_PRESSING = false;
			return;

		case GLFW_KEY_S:
			S_PRESSING = false;
			return;

		case GLFW_KEY_Q:
			Q_PRESSING = false;
			return;

		case GLFW_KEY_E:
			E_PRESSING = false;
			return;

		case GLFW_KEY_UP:
			ARROW_UP_PRESSING = false;
			return;

		case GLFW_KEY_LEFT:
			ARROW_LEFT_PRESSING = false;
			return;

		case GLFW_KEY_RIGHT:
			ARROW_RIGHT_PRESSING = false;
			return;

		case GLFW_KEY_DOWN:
			ARROW_DOWN_PRESSING = false;
			return;

		}
	}
}

void Controls::Mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			MOUSE_LEFT_PRESSING = true;
			return;

		case GLFW_MOUSE_BUTTON_RIGHT:
			MOUSE_RIGHT_PRESSING = true;
			return;
		}
	}
	else if (action == GLFW_RELEASE)
	{
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			MOUSE_LEFT_PRESSING = false;
			return;

		case GLFW_MOUSE_BUTTON_RIGHT:
			MOUSE_RIGHT_PRESSING = false;
			return;
		}
	}
}

void Controls::Cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	CURSOR_POS_X = xpos;
	CURSOR_POS_Y = ypos;
}

#include <iostream>


void Controls::Scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (SCROLL_OFFSET_X + xoffset < 11 && SCROLL_OFFSET_X + xoffset > 0)
	{
		SCROLL_OFFSET_X += xoffset;
	}

	if (SCROLL_OFFSET_Y + yoffset < 11 && SCROLL_OFFSET_Y + yoffset > 0)
	{
		SCROLL_OFFSET_Y += yoffset;
	}
}
