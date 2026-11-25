#include "gamepad.h"
#include <iostream>
#include "core/fika_servers.h"

namespace FikaEngine
{
	void Gamepad::handleInput()
	{
		const int buttonsCount = 15;
		const int axesCount = 6;

		if (!glfwJoystickPresent(id))
		{
			//FikaServers::consolePrint("Gamepad not present: ", { std::to_string(id) });
			return;
		}

		if (!glfwJoystickIsGamepad(id))
		{
			//FikaServers::consolePrint("Device is not gamepad: ", { std::to_string(id) });
		}

		GLFWgamepadstate gamepadState;
		glfwGetGamepadState(id, &gamepadState);

		// Buttons
		for (int i = 0; i < buttonsCount; i++)
		{
			if (buttonPressed[i] && !buttonReleased[i])
			{
				buttonHeld[i] = (gamepadState.buttons[i] == GLFW_PRESS);
			}

			if (buttonHeld[i] && gamepadState.buttons[i] == GLFW_RELEASE)
			{
				buttonHeld[i] = false;
			}

			buttonPressed[i] = (buttonReleased[i]) && (gamepadState.buttons[i] == GLFW_PRESS);
			buttonReleased[i] = (gamepadState.buttons[i] == GLFW_RELEASE);

			// Debug
			if (buttonPressed[i])
			{
				FikaServers::consolePrint("Pressed: ", { std::to_string(i), ", ", buttonNameFromGLFW(i)});
			}
		}

		// Axes
		for (int i = 0; i < axesCount; i++)
		{
			axesValues[i] = gamepadState.axes[i];

			// Adjust triggers to 0 - 1
			if (i == Gamepad::GamepadAxes::LT || i == Gamepad::GamepadAxes::RT)
			{
				axesValues[i] = (axesValues[i] + 1) / 2;

				// Trigger filter
				if (axesValues[i] < DEAD_ZONE)
				{
					axesValues[i] = 0.0f;
				}
			}
			else
			{
				// Thumb filter
				if (abs(axesValues[i]) < DEAD_ZONE)
				{
					axesValues[i] = 0.0f;
				}
			}

			if (axesValues[i] > 0.0f)
			{
				FikaServers::consolePrint("Axis: ", { std::to_string(i), ", ", axisNameFromGLFW(i), ", value: ", std::to_string(axesValues[i]) });
			}
		}
	}

	std::string Gamepad::buttonNameFromGLFW(int key)
	{
		switch (key)
		{
			// Buttons
		case GLFW_GAMEPAD_BUTTON_A: return "A";
		case GLFW_GAMEPAD_BUTTON_B: return "B";
		case GLFW_GAMEPAD_BUTTON_X: return "X";
		case GLFW_GAMEPAD_BUTTON_Y: return "Y";

			// Bumbers
		case GLFW_GAMEPAD_BUTTON_LEFT_BUMPER: return "LeftBumper";
		case GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER: return "RightBumper";

			// Back - Start - Guide (Central button)
		case GLFW_GAMEPAD_BUTTON_BACK: return "Back";
		case GLFW_GAMEPAD_BUTTON_START: return "Start";
		case GLFW_GAMEPAD_BUTTON_GUIDE: return "Guide";

			// Sticks
		case GLFW_GAMEPAD_BUTTON_LEFT_THUMB: return "LeftThumb";
		case GLFW_GAMEPAD_BUTTON_RIGHT_THUMB: return "RightThumb";

			// DPAD
		case GLFW_GAMEPAD_BUTTON_DPAD_UP: return "DPAD_Up";
		case GLFW_GAMEPAD_BUTTON_DPAD_RIGHT: return "DPAD_Right";
		case GLFW_GAMEPAD_BUTTON_DPAD_DOWN: return "DPAD_Down";
		case GLFW_GAMEPAD_BUTTON_DPAD_LEFT: return "DPAD_Left";
		}

		return "";
	}

	std::string Gamepad::axisNameFromGLFW(int input)
	{
		switch (input)
		{
		case GLFW_GAMEPAD_AXIS_LEFT_X: return "LeftThumbX";
		case GLFW_GAMEPAD_AXIS_LEFT_Y: return "LeftThumbY";
		case GLFW_GAMEPAD_AXIS_RIGHT_X: return "RightThumbX";
		case GLFW_GAMEPAD_AXIS_RIGHT_Y: return "RightThumbY";
		case GLFW_GAMEPAD_AXIS_LEFT_TRIGGER: return "LeftTrigger";
		case GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER: return "RightTrigger";
		}

		return "";
	}

}