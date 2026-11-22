#include "gamepad.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "core/fika_servers.h"

namespace FikaEngine
{
	void Gamepad::handleInput()
	{
		// Buttons
		int buttonsCount;
		const unsigned char* buttons = glfwGetJoystickButtons(id, &buttonsCount);

		for (int i = 0; i < buttonsCount; i++)
		{
			Gamepad::GamepadButton input = buttonFromGLFW(i);
 
			if (buttonPressed[input] && !buttonReleased[input])
			{
				buttonHeld[input] = (buttons[i] == GLFW_PRESS);
			}

			if (buttonHeld[input] && buttons[i] == GLFW_RELEASE)
			{
				buttonHeld[input] = false;
			}

			buttonPressed[input] = (buttonReleased[input]) && (buttons[i] == GLFW_PRESS);
			buttonReleased[input] = (buttons[i] == GLFW_RELEASE);

			if (buttonPressed[i])
			{
				FikaServers::consolePrint("Pressed: ", { std::to_string(i), ", ", buttonNameFromGLFW(i)});
			}
		}

		// Axes
		int axesCount;
		const float* axes = glfwGetJoystickAxes(id, &axesCount);

		for (int i = 0; i < axesCount; i++)
		{
			Gamepad::GamepadAxes input = axisFromGLFW(i);
			axesValues[input] = axes[i];

			// Adjust triggers to 0 - 1
			if (input == Gamepad::GamepadAxes::LT || input == Gamepad::GamepadAxes::RT)
			{
				axesValues[input] = (axesValues[input] + 1) / 2;
			}
		}
	}

	Gamepad::GamepadButton Gamepad::buttonFromGLFW(int key)
	{
		switch (key)
		{
			// Buttons
		case GLFW_GAMEPAD_BUTTON_A: return Gamepad::GamepadButton::A;
		case GLFW_GAMEPAD_BUTTON_B: return Gamepad::GamepadButton::B;
		case GLFW_GAMEPAD_BUTTON_X: return Gamepad::GamepadButton::X;
		case GLFW_GAMEPAD_BUTTON_Y: return Gamepad::GamepadButton::Y;

			// Bumbers
		case GLFW_GAMEPAD_BUTTON_LEFT_BUMPER: return Gamepad::GamepadButton::LeftBumper;
		case GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER: return Gamepad::GamepadButton::RightBumper;

			// Back - Start - Guide (Central button)
		case GLFW_GAMEPAD_BUTTON_BACK: return Gamepad::GamepadButton::Back;
		case GLFW_GAMEPAD_BUTTON_START: return Gamepad::GamepadButton::Start;
		case GLFW_GAMEPAD_BUTTON_GUIDE: return Gamepad::GamepadButton::Guide;

			// Sticks
		case GLFW_GAMEPAD_BUTTON_LEFT_THUMB: return Gamepad::GamepadButton::LeftThumb;
		case GLFW_GAMEPAD_BUTTON_RIGHT_THUMB: return Gamepad::GamepadButton::RightThumb;

			// DPAD
		case GLFW_GAMEPAD_BUTTON_DPAD_UP: return Gamepad::GamepadButton::DPAD_Up;
		case GLFW_GAMEPAD_BUTTON_DPAD_RIGHT: return Gamepad::GamepadButton::DPAD_Right;
		case GLFW_GAMEPAD_BUTTON_DPAD_DOWN: return Gamepad::GamepadButton::DPAD_Down;
		case GLFW_GAMEPAD_BUTTON_DPAD_LEFT: return Gamepad::GamepadButton::DPAD_Left;
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

	Gamepad::GamepadAxes Gamepad::axisFromGLFW(int input)
	{
		switch (input)
		{
		case GLFW_GAMEPAD_AXIS_LEFT_X: return Gamepad::GamepadAxes::LS_X;
		case GLFW_GAMEPAD_AXIS_LEFT_Y: return Gamepad::GamepadAxes::LS_Y;
		case GLFW_GAMEPAD_AXIS_RIGHT_X: return Gamepad::GamepadAxes::RS_X;
		case GLFW_GAMEPAD_AXIS_RIGHT_Y: return Gamepad::GamepadAxes::RS_Y;
		case GLFW_GAMEPAD_AXIS_LEFT_TRIGGER: return Gamepad::GamepadAxes::LT;
		case GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER: return Gamepad::GamepadAxes::RT;
		}
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