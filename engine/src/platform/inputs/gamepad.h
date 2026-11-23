#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace FikaEngine
{
    struct Gamepad
    {
        int id = 0;
        const float DEAD_ZONE = 0.05f;

        // Input buttons
        enum GamepadButton
        {
            A = GLFW_GAMEPAD_BUTTON_A,
            B = GLFW_GAMEPAD_BUTTON_B,
            X = GLFW_GAMEPAD_BUTTON_X,
            Y = GLFW_GAMEPAD_BUTTON_Y,
            LeftBumper = GLFW_GAMEPAD_BUTTON_LEFT_BUMPER,
            RightBumper = GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER,
            Back = GLFW_GAMEPAD_BUTTON_BACK,
            Start = GLFW_GAMEPAD_BUTTON_START,
            Guide = GLFW_GAMEPAD_BUTTON_GUIDE,
            LeftThumb = GLFW_GAMEPAD_BUTTON_LEFT_THUMB,
            RightThumb = GLFW_GAMEPAD_BUTTON_RIGHT_THUMB,
            DPAD_Up = GLFW_GAMEPAD_BUTTON_DPAD_UP,
            DPAD_Right = GLFW_GAMEPAD_BUTTON_DPAD_RIGHT,
            DPAD_Down = GLFW_GAMEPAD_BUTTON_DPAD_DOWN,
            DPAD_Left = GLFW_GAMEPAD_BUTTON_DPAD_LEFT,
            GamepadButtonCount,
        };

        bool buttonPressed[GamepadButton::GamepadButtonCount];
        bool buttonReleased[GamepadButton::GamepadButtonCount];
        bool buttonHeld[GamepadButton::GamepadButtonCount];

        // Axes - Thumbs sticks and triggers
        enum GamepadAxes
        {
            LS_X = GLFW_GAMEPAD_AXIS_LEFT_X,
            LS_Y = GLFW_GAMEPAD_AXIS_LEFT_Y,
            RS_X = GLFW_GAMEPAD_AXIS_RIGHT_X,
            RS_Y = GLFW_GAMEPAD_AXIS_RIGHT_Y,
            LT = GLFW_GAMEPAD_AXIS_LEFT_TRIGGER,
            RT = GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER,
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