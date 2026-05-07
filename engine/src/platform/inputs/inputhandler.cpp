#include "inputhandler.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace Input
{

	struct HIDState
	{
		Keyboard keyboard;
		Mouse mouse;
	};

	static HIDState* hid = nullptr;

	//------------------------------------------------------------------------------
	/**
	*/
	void InputHandler::init(GLFWwindow* window)
	{
		if (hid == nullptr)
			hid = new HIDState();

		//glfwSetKeyCallback(window, OnGLKeyCallback);
		glfwSetMouseButtonCallback(window, onGLMousePressCallback);
		glfwSetCursorPosCallback(window, onGLMouseMoveCallback);
		glfwSetScrollCallback(window, onGLMouseScrollCallback);
	}

	void InputHandler::onGLKeyCallback(GLFWwindow* win, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(win, GLFW_TRUE);
			return;
		}

		handleKeyEvent(key, scancode, action, mods);
	}
	void InputHandler::onGLMousePressCallback(GLFWwindow* win, int button, int action, int mods) { handleMousePressEvent(button, action, mods); }
	void InputHandler::onGLMouseMoveCallback(GLFWwindow* win, double x, double y) { handleMouseMoveEvent(x, y); }
	void InputHandler::onGLMouseScrollCallback(GLFWwindow* win, double x, double y)
	{
		hid->mouse.currentYScroll = y;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void InputHandler::beginFrame()
	{
		for (int i = 0; i < Key::Code::NumKeyCodes; i++)
		{
			if (hid->keyboard.released[i])
				hid->keyboard.held[i] = false;

			hid->keyboard.pressed[i] = false;
			hid->keyboard.released[i] = false;
		}

		for (int i = 0; i < Mouse::Button::NumMouseButtons; i++)
		{
			if (hid->mouse.released[i])
				hid->mouse.held[i] = false;

			hid->mouse.pressed[i] = false;
			hid->mouse.released[i] = false;
		}

		hid->mouse.delta = glm::vec2(0);
		hid->mouse.previousPosition = hid->mouse.position;
		hid->mouse.currentYScroll = 0;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void InputHandler::handleKeyEvent(int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			Key::Code code = Key::FromGLFW(key);
			hid->keyboard.pressed[code] = true;
			hid->keyboard.held[code] = true;

			// Special case buttons:
			if (code == Key::Code::LeftControl || code == Key::Code::RightControl)
			{
				hid->keyboard.pressed[Key::Code::Control] = true;
				hid->keyboard.held[Key::Code::Control] = true;
			}
			else if (code == Key::Code::LeftShift || code == Key::Code::RightShift)
			{
				hid->keyboard.pressed[Key::Code::Shift] = true;
				hid->keyboard.held[Key::Code::Shift] = true;
			}
			else if (code == Key::Code::LeftAlt || code == Key::Code::RightAlt)
			{
				hid->keyboard.pressed[Key::Code::Alt] = true;
				hid->keyboard.held[Key::Code::Alt] = true;
			}
		}
		else if (action == GLFW_RELEASE)
		{
			Key::Code code = Key::FromGLFW(key);
			hid->keyboard.released[code] = true;

			// Special case buttons:
			if (code == Key::Code::LeftControl || code == Key::Code::RightControl)
			{
				hid->keyboard.released[Key::Code::Control] = true;
			}
			else if (code == Key::Code::LeftShift || code == Key::Code::RightShift)
			{
				hid->keyboard.released[Key::Code::Shift] = true;
			}
			else if (code == Key::Code::LeftAlt || code == Key::Code::RightAlt)
			{
				hid->keyboard.released[Key::Code::Alt] = true;
			}
		}
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void InputHandler::handleMousePressEvent(int button, int action, int mods)
	{
		assert(button < Mouse::Button::NumMouseButtons);
		if (action == GLFW_PRESS)
		{
			hid->mouse.pressed[button] = true;
			hid->mouse.held[button] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			hid->mouse.released[button] = true;
		}
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void InputHandler::handleMouseMoveEvent(double x, double y)
	{
		hid->mouse.position = glm::vec2(x, y);
		hid->mouse.delta = hid->mouse.position - hid->mouse.previousPosition;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	Keyboard* getDefaultKeyboard()
	{
		assert(hid != nullptr);
		return &hid->keyboard;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	Mouse* getDefaultMouse()
	{
		assert(hid != nullptr);
		return &hid->mouse;
	}
}