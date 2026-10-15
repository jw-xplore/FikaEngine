#include "gamepad.h"
#include "GLFW/glfw3.h"
#include <iostream>

namespace FikaEngine
{
	void Gamepad::handleInput()
	{
		// Buttons
		int buttonsCount;
		const unsigned char* buttons = glfwGetJoystickButtons(id, &buttonsCount);

		for (int i = 0; i < buttonsCount; i++)
		{
			Gamepad::GamepadButton input = ButtonFromGLFW(i);

			buttonPressed[input] = (buttonReleased[input]) && (buttons[i] == GLFW_PRESS);
			buttonReleased[input] = (buttons[i] == GLFW_RELEASE);
			buttonHeld[input] = (buttons[i] == GLFW_PRESS);
		}

		// Axes
		int axesCount;
		const float* axes = glfwGetJoystickAxes(id, &axesCount);

		for (int i = 0; i < axesCount; i++)
		{
			Gamepad::GamepadAxes input = AxisFromGLFW(i);
			axesValues[input] = axes[i];

			// Adjust triggers to 0 - 1
			if (input == Gamepad::GamepadAxes::LT || input == Gamepad::GamepadAxes::RT)
			{
				axesValues[input] = (axesValues[input] + 1) / 2;
			}
		}
	}

	Gamepad::GamepadButton Gamepad::ButtonFromGLFW(int key)
	{
		switch (key)
		{
			// Buttons
		case 0: return Gamepad::GamepadButton::A; break;
		case 1: return Gamepad::GamepadButton::B; break;
		case 2: return Gamepad::GamepadButton::X; break;
		case 3: return Gamepad::GamepadButton::Y; break;

			// Bumbers
		case 4: return Gamepad::GamepadButton::LeftBumper; break;
		case 5: return Gamepad::GamepadButton::RightBumper; break;

			// Back - Start
		case 6: return Gamepad::GamepadButton::Back; break;
		case 7: return Gamepad::GamepadButton::Start; break;

			// Sticks
		case 8: return Gamepad::GamepadButton::LeftStick; break;
		case 9: return Gamepad::GamepadButton::RightStick; break;

			// DPAD
		case 10: return Gamepad::GamepadButton::DPAD_Up; break;
		case 11: return Gamepad::GamepadButton::DPAD_Right; break;
		case 12: return Gamepad::GamepadButton::DPAD_Down; break;
		case 13: return Gamepad::GamepadButton::DPAD_Left; break;
		}
	}

	Gamepad::GamepadAxes Gamepad::AxisFromGLFW(int input)
	{
		switch (input)
		{
		case 0: return Gamepad::GamepadAxes::LS_Horizontal; break;
		case 1: return Gamepad::GamepadAxes::LS_Vertical; break;
		case 2: return Gamepad::GamepadAxes::RS_Horizontal; break;
		case 3: return Gamepad::GamepadAxes::RS_Vertical; break;
		case 4: return Gamepad::GamepadAxes::LT; break;
		case 5: return Gamepad::GamepadAxes::RT; break;
		}
	}

}