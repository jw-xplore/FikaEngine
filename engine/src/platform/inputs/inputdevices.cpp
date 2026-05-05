#include "inputdevices.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Input
{
	Key::Code Key::FromGLFW(int key)
	{
		switch (key)
		{
		case GLFW_KEY_SPACE: return Code::Space;
		case GLFW_KEY_APOSTROPHE: return Code::Apps;
		case GLFW_KEY_COMMA: return Code::Comma;
		case GLFW_KEY_MINUS: return Code::InvalidKey;
		case GLFW_KEY_PERIOD: return Code::Period;
		case GLFW_KEY_SLASH: return Code::Slash;
		case GLFW_KEY_0: return Code::Key0;
		case GLFW_KEY_1: return Code::Key1;
		case GLFW_KEY_2: return Code::Key2;
		case GLFW_KEY_3: return Code::Key3;
		case GLFW_KEY_4: return Code::Key4;
		case GLFW_KEY_5: return Code::Key5;
		case GLFW_KEY_6: return Code::Key6;
		case GLFW_KEY_7: return Code::Key7;
		case GLFW_KEY_8: return Code::Key8;
		case GLFW_KEY_9: return Code::Key9;
		case GLFW_KEY_SEMICOLON: return Code::Semicolon;
		case GLFW_KEY_EQUAL: return Code::Equality;
		case GLFW_KEY_A: return Code::A;
		case GLFW_KEY_B: return Code::B;
		case GLFW_KEY_C: return Code::C;
		case GLFW_KEY_D: return Code::D;
		case GLFW_KEY_E: return Code::E;
		case GLFW_KEY_F: return Code::F;
		case GLFW_KEY_G: return Code::G;
		case GLFW_KEY_H: return Code::H;
		case GLFW_KEY_I: return Code::I;
		case GLFW_KEY_J: return Code::J;
		case GLFW_KEY_K: return Code::K;
		case GLFW_KEY_L: return Code::L;
		case GLFW_KEY_M: return Code::M;
		case GLFW_KEY_N: return Code::N;
		case GLFW_KEY_O: return Code::O;
		case GLFW_KEY_P: return Code::P;
		case GLFW_KEY_Q: return Code::Q;
		case GLFW_KEY_R: return Code::R;
		case GLFW_KEY_S: return Code::S;
		case GLFW_KEY_T: return Code::T;
		case GLFW_KEY_U: return Code::U;
		case GLFW_KEY_V: return Code::V;
		case GLFW_KEY_W: return Code::W;
		case GLFW_KEY_X: return Code::X;
		case GLFW_KEY_Y: return Code::Y;
		case GLFW_KEY_Z: return Code::Z;
		case GLFW_KEY_LEFT_BRACKET: return Code::LeftBracket;
		case GLFW_KEY_BACKSLASH: return Code::BackSlash;
		case GLFW_KEY_RIGHT_BRACKET: return Code::RightBracket;
		case GLFW_KEY_GRAVE_ACCENT: return Code::InvalidKey;
		case GLFW_KEY_WORLD_1: return Code::InvalidKey;
		case GLFW_KEY_WORLD_2: return Code::InvalidKey;

			/* Function keys */
		case GLFW_KEY_ESCAPE: return Code::Escape;
		case GLFW_KEY_ENTER: return Code::Return;
		case GLFW_KEY_TAB: return Code::Tab;
		case GLFW_KEY_BACKSPACE: return Code::Back;
		case GLFW_KEY_INSERT: return Code::Insert;
		case GLFW_KEY_DELETE: return Code::Delete;
		case GLFW_KEY_RIGHT: return Code::Right;
		case GLFW_KEY_LEFT: return Code::Left;
		case GLFW_KEY_DOWN: return Code::Down;
		case GLFW_KEY_UP: return Code::Up;
		case GLFW_KEY_PAGE_UP: return Code::PageUp;
		case GLFW_KEY_PAGE_DOWN: return Code::PageDown;
		case GLFW_KEY_HOME: return Code::Home;
		case GLFW_KEY_END: return Code::End;
		case GLFW_KEY_CAPS_LOCK: return Code::Capital;
		case GLFW_KEY_SCROLL_LOCK: return Code::Scroll;
		case GLFW_KEY_NUM_LOCK: return Code::NumLock;
		case GLFW_KEY_PRINT_SCREEN: return Code::Print;
		case GLFW_KEY_PAUSE: return Code::Pause;
		case GLFW_KEY_F1: return Code::F1;
		case GLFW_KEY_F2: return Code::F2;
		case GLFW_KEY_F3: return Code::F3;
		case GLFW_KEY_F4: return Code::F4;
		case GLFW_KEY_F5: return Code::F5;
		case GLFW_KEY_F6: return Code::F6;
		case GLFW_KEY_F7: return Code::F7;
		case GLFW_KEY_F8: return Code::F8;
		case GLFW_KEY_F9: return Code::F9;
		case GLFW_KEY_F10: return Code::F10;
		case GLFW_KEY_F11: return Code::F11;
		case GLFW_KEY_F12: return Code::F12;
		case GLFW_KEY_F13: return Code::F13;
		case GLFW_KEY_F14: return Code::F14;
		case GLFW_KEY_F15: return Code::F15;
		case GLFW_KEY_F16: return Code::F16;
		case GLFW_KEY_F17: return Code::F17;
		case GLFW_KEY_F18: return Code::F18;
		case GLFW_KEY_F19: return Code::F19;
		case GLFW_KEY_F20: return Code::F20;
		case GLFW_KEY_F21: return Code::F21;
		case GLFW_KEY_F22: return Code::F22;
		case GLFW_KEY_F23: return Code::F23;
		case GLFW_KEY_F24: return Code::F24;
		case GLFW_KEY_F25: return Code::InvalidKey;
		case GLFW_KEY_KP_0: return Code::NumPad0;
		case GLFW_KEY_KP_1: return Code::NumPad1;
		case GLFW_KEY_KP_2: return Code::NumPad2;
		case GLFW_KEY_KP_3: return Code::NumPad3;
		case GLFW_KEY_KP_4: return Code::NumPad4;
		case GLFW_KEY_KP_5: return Code::NumPad5;
		case GLFW_KEY_KP_6: return Code::NumPad6;
		case GLFW_KEY_KP_7: return Code::NumPad7;
		case GLFW_KEY_KP_8: return Code::NumPad8;
		case GLFW_KEY_KP_9: return Code::NumPad9;
		case GLFW_KEY_KP_DECIMAL: return Code::Decimal;
		case GLFW_KEY_KP_DIVIDE: return Code::Divide;
		case GLFW_KEY_KP_MULTIPLY: return Code::Multiply;
		case GLFW_KEY_KP_SUBTRACT: return Code::Subtract;
		case GLFW_KEY_KP_ADD: return Code::Add;
		case GLFW_KEY_KP_ENTER: return Code::NumPadEnter;
		case GLFW_KEY_KP_EQUAL: return Code::InvalidKey;
		case GLFW_KEY_LEFT_SHIFT: return Code::LeftShift;
		case GLFW_KEY_LEFT_CONTROL: return Code::LeftControl;
		case GLFW_KEY_LEFT_ALT: return Code::LeftAlt;
		case GLFW_KEY_LEFT_SUPER: return Code::InvalidKey;
		case GLFW_KEY_RIGHT_SHIFT: return Code::RightShift;
		case GLFW_KEY_RIGHT_CONTROL: return Code::RightControl;
		case GLFW_KEY_RIGHT_ALT: return Code::RightAlt;
		case GLFW_KEY_RIGHT_SUPER: return Code::InvalidKey;
		case GLFW_KEY_MENU: return Code::Menu;
		default: return Code::InvalidKey;
		}
	}
}
