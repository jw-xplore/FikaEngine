#pragma once

namespace FikaEngine
{
    struct Gamepad
    {
        int id = 0;

        // Input buttons
        enum GamepadButton
        {
            A, B, X, Y,
            Back, Start,
            DPAD_Right, DPAD_Left, DPAD_Up, DPAD_Down,
            RightStick, LeftStick, // Thumbstick clicks
            RightBumper, LeftBumper,
            GamepadButtonCount,
        };

        constexpr static const char* const gamepadButtonNames[GamepadButton::GamepadButtonCount] =
        {
            "A", "B", "X", "Y",
            "Back", "Start",
            "DPAD_Right", "DPAD_Left", "DPAD_Up", "DPAD_Down",
            "RightStick", "LeftStick",
            "RightBumper", "LeftBumper"
        };

        bool buttonPressed[GamepadButton::GamepadButtonCount];
        bool buttonReleased[GamepadButton::GamepadButtonCount];
        bool buttonHeld[GamepadButton::GamepadButtonCount];

        // Axes - Thumbs sticks and triggers
        enum GamepadAxes
        {
            LS_Horizontal, LS_Vertical,
            RS_Horizontal, RS_Vertical,
            LT, RT,
            GamepadAxesCount,
        };

        constexpr static const char* const gamepadAxesNames[GamepadAxes::GamepadAxesCount] =
        {
            "LS_Horizontal", "LS_Vertical",
            "RS_Horizontal", "RS_Vertical",
            "Left Trigger", "Right Trigger",
        };

        float axesValues[GamepadAxes::GamepadAxesCount];

        void handleInput();
        static GamepadButton ButtonFromGLFW(int key);
        static GamepadAxes AxisFromGLFW(int input);
    };
}