#include "input_manager.h"

namespace FikaEngine
{
	// TODO: Check if this can be moved into the input manager
	static Keyboard keyboard;
	static Mouse mouse;

	InputManager::InputManager()
	{

	}

	InputManager::~InputManager()
	{

	}

	void InputManager::init(GLFWwindow* window)
	{
		//keyboard = new Keyboard();
		//mouse = new Mouse();

		glfwSetKeyCallback(window, onGLKeyCallback);
		glfwSetMouseButtonCallback(window, onGLMousePressCallback);
		glfwSetCursorPosCallback(window, onGLMouseMoveCallback);
		glfwSetScrollCallback(window, onGLMouseScrollCallback);
	}

	void InputManager::beginFrame()
	{
		// Restart keyboard
		for (int i = 0; i < Key::Code::NumKeyCodes; i++)
		{
			if (keyboard.releasedKeys[i])
				keyboard.heldKeys[i] = false;

			keyboard.pressedKeys[i] = false;
			keyboard.releasedKeys[i] = false;
		}

		// Restart mouse
		for (int i = 0; i < Mouse::Button::NumMouseButtons; i++)
		{
			if (mouse.releasedBtns[i])
				mouse.heldBtns[i] = false;

			mouse.pressedBtns[i] = false;
			mouse.releasedBtns[i] = false;
		}

		mouse.positionDelta = glm::vec2(0);
		mouse.previousPosition = mouse.position;
		mouse.scrollInput = 0;
	}

	bool InputManager::isKeyPressed(Key::Code key)
	{
		return keyboard.pressedKeys[key];
	}

	bool InputManager::isKeyReleased(Key::Code key)
	{
		return keyboard.releasedKeys[key];
	}

	bool InputManager::isKeyHeld(Key::Code key)
	{
		return keyboard.heldKeys[key];
	}

	bool InputManager::isMousePressed(Mouse::Button button)
	{
		return mouse.pressedBtns[button];
	}

	bool InputManager::isMouseReleased(Mouse::Button button)
	{
		return mouse.releasedBtns[button];
	}

	bool InputManager::isMouseHeld(Mouse::Button button)
	{
		return mouse.heldBtns[button];
	}

	glm::vec2 InputManager::mousePosition()
	{
		return mouse.position;
	}

	double InputManager::mouseScroll()
	{
		return mouse.scrollInput;
	}

	void InputManager::onGLKeyCallback(GLFWwindow* win, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(win, GLFW_TRUE);
			return;
		}

		handleKeyEvent(key, scancode, action, mods);
	}

	void InputManager::onGLMousePressCallback(GLFWwindow* win, int button, int action, int mods)
	{
		handleMousePressEvent(button, action, mods);
	}

	void InputManager::onGLMouseMoveCallback(GLFWwindow* win, double x, double y)
	{
		handleMouseMoveEvent(x, y);
	}

	void InputManager::onGLMouseScrollCallback(GLFWwindow* win, double x, double y)
	{
		mouse.scrollInput = y;
	}

	void InputManager::handleKeyEvent(int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			Key::Code code = Key::FromGLFW(key);
			keyboard.pressedKeys[code] = true;
			keyboard.heldKeys[code] = true;

			// Special case buttons:
			if (code == Key::Code::LeftControl || code == Key::Code::RightControl)
			{
				keyboard.pressedKeys[Key::Code::Control] = true;
				keyboard.heldKeys[Key::Code::Control] = true;
			}
			else if (code == Key::Code::LeftShift || code == Key::Code::RightShift)
			{
				keyboard.pressedKeys[Key::Code::Shift] = true;
				keyboard.heldKeys[Key::Code::Shift] = true;
			}
			else if (code == Key::Code::LeftAlt || code == Key::Code::RightAlt)
			{
				keyboard.pressedKeys[Key::Code::Alt] = true;
				keyboard.heldKeys[Key::Code::Alt] = true;
			}
		}
		else if (action == GLFW_RELEASE)
		{
			Key::Code code = Key::FromGLFW(key);
			keyboard.releasedKeys[code] = true;

			// Special case buttons:
			if (code == Key::Code::LeftControl || code == Key::Code::RightControl)
			{
				keyboard.releasedKeys[Key::Code::Control] = true;
			}
			else if (code == Key::Code::LeftShift || code == Key::Code::RightShift)
			{
				keyboard.releasedKeys[Key::Code::Shift] = true;
			}
			else if (code == Key::Code::LeftAlt || code == Key::Code::RightAlt)
			{
				keyboard.releasedKeys[Key::Code::Alt] = true;
			}
		}
	}

	void InputManager::handleMousePressEvent(int button, int action, int mods)
	{
		assert(button < Mouse::Button::NumMouseButtons);
		if (action == GLFW_PRESS)
		{
			mouse.pressedBtns[button] = true;
			mouse.heldBtns[button] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			mouse.releasedBtns[button] = true;
		}
	}

	void InputManager::handleMouseMoveEvent(double x, double y)
	{
		mouse.position = glm::vec2(x, y);
		mouse.positionDelta = mouse.position - mouse.previousPosition;
	}

	Keyboard& InputManager::getKeyboard()
	{
		return keyboard;
	}

	Mouse& InputManager::getMouse()
	{
		return mouse;
	}
} // namespace FikaEngine
