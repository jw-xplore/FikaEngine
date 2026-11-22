#pragma once
#include <string>

namespace FikaEngine
{
    struct Gamepad
    {
        int id = 0;

        // Input buttons
        enum GamepadButton
        {
            A, B, X, Y,
            Back, Start, Guide,
            LeftThumb, RightThumb, // Thumbstick clicks
            LeftBumper, RightBumper,
            DPAD_Up, DPAD_Right, DPAD_Down, DPAD_Left,
            GamepadButtonCount,
        };

        bool buttonPressed[GamepadButton::GamepadButtonCount];
        bool buttonReleased[GamepadButton::GamepadButtonCount];
        bool buttonHeld[GamepadButton::GamepadButtonCount];

        // Axes - Thumbs sticks and triggers
        enum GamepadAxes
        {
            LS_X, LS_Y,
            RS_X, RS_Y,
            LT, RT,
            GamepadAxesCount,
        };

        float axesValues[GamepadAxes::GamepadAxesCount];

        void handleInput();
        static GamepadButton buttonFromGLFW(int key);
        static std::string buttonNameFromGLFW(int key);
        static GamepadAxes axisFromGLFW(int input);
        static std::string axisNameFromGLFW(int input);
    };
}