#pragma once
#include <glm/glm.hpp>

namespace Input
{
    //------------------------------------------------------------------------------
    struct Mouse
    {
        enum Button
        {
            LeftButton = 0,
            RightButton = 1,
            MiddleButton = 2,

            NumMouseButtons,
            InvalidMouseButton,
        };

        constexpr static const char* const mouseButtonNames[Button::NumMouseButtons] =
        {
            "LeftButton","RightButton","MiddleButton"
        };

        /// contains all buttons that was pressed this frame. This is reset every frame
        bool pressed[Button::NumMouseButtons];

        /// contains all buttons that was released this frame. This is reset every frame
        bool released[Button::NumMouseButtons];

        /// contains all buttons that are currently being held. These are reset as buttons receive the release action
        bool held[Button::NumMouseButtons];

        // position in pixels. ([0-windowWidth], [0-windowHeight])
        glm::vec2 position;

        // delta position this frame
        glm::vec2 delta;

        // position previous frame
        glm::vec2 previousPosition;

        // Current frame vertical scroll
        double currentYScroll = 0;
    };

    //------------------------------------------------------------------------------
    struct Key
    {
        /// key codes
        enum Code
        {
            Back,
            Tab,
            Clear,
            Return,
            Shift,
            Control,
            Alt,
            Menu,
            Pause,
            Capital,
            Escape,
            Convert,
            NonConvert,
            Accept,
            ModeChange,
            Space,
            Prior,
            Next,
            End,
            Home,
            PageUp,
            PageDown,
            Left,
            Right,
            Up,
            Down,
            Select,
            Print,
            Execute,
            Snapshot,
            Insert,
            Delete,
            Help,
            LeftWindows,
            RightWindows,
            Apps,
            Sleep,
            NumPad0,
            NumPad1,
            NumPad2,
            NumPad3,
            NumPad4,
            NumPad5,
            NumPad6,
            NumPad7,
            NumPad8,
            NumPad9,
            NumPadEnter,
            Multiply,
            Add,
            Subtract,
            Separator,
            Decimal,
            Divide,
            F1,
            F2,
            F3,
            F4,
            F5,
            F6,
            F7,
            F8,
            F9,
            F10,
            F11,
            F12,
            F13,
            F14,
            F15,
            F16,
            F17,
            F18,
            F19,
            F20,
            F21,
            F22,
            F23,
            F24,
            NumLock,
            Scroll,
            Semicolon,
            Slash,
            Tilde,
            LeftBracket,
            RightBracket,
            BackSlash,
            Quote,
            Comma,
            Underbar,
            Period,
            Equality,
            LeftShift,
            RightShift,
            LeftControl,
            RightControl,
            LeftAlt,
            RightAlt,
            LeftMenu,
            RightMenu,
            BrowserBack,
            BrowserForward,
            BrowserRefresh,
            BrowserStop,
            BrowserSearch,
            BrowserFavorites,
            BrowserHome,
            VolumeMute,
            VolumeDown,
            VolumeUp,
            MediaNextTrack,
            MediaPrevTrack,
            MediaStop,
            MediaPlayPause,
            LaunchMail,
            LaunchMediaSelect,
            LaunchApp1,
            LaunchApp2,
            Key0,
            Key1,
            Key2,
            Key3,
            Key4,
            Key5,
            Key6,
            Key7,
            Key8,
            Key9,
            A,
            B,
            C,
            D,
            E,
            F,
            G,
            H,
            I,
            J,
            K,
            L,
            M,
            N,
            O,
            P,
            Q,
            R,
            S,
            T,
            U,
            V,
            W,
            X,
            Y,
            Z,

            NumKeyCodes,
            InvalidKey,
        };

        constexpr static const char* const CodeNames[Code::NumKeyCodes] =
        {
            "Back","Tab","Clear","Return","Shift","Control","Alt","Menu","Pause",
            "Capital","Escape","Convert","NonConvert","Accept","ModeChange",
            "Space","Prior","Next","End","Home","PageUp","PageDown","Left",
            "Right","Up","Down","Select","Print","Execute","Snapshot",
            "Insert","Delete","Help","LeftWindows","RightWindows","Apps","Sleep",

            "NumPad0","NumPad1","NumPad2","NumPad3","NumPad4","NumPad5","NumPad6",
            "NumPad7","NumPad8","NumPad9","NumPadEnter",

            "Multiply","Add","Subtract","Separator","Decimal","Divide",

            "F1","F2","F3","F4","F5","F6","F7","F8","F9","F10",
            "F11","F12","F13","F14","F15","F16","F17","F18","F19","F20",
            "F21","F22","F23","F24",

            "NumLock","Scroll","Semicolon","Slash","Tilde",
            "LeftBracket","RightBracket","BackSlash","Quote","Comma",
            "Underbar","Period","Equality",

            "LeftShift","RightShift","LeftControl","RightControl",
            "LeftAlt","RightAlt","LeftMenu","RightMenu",

            "BrowserBack","BrowserForward","BrowserRefresh","BrowserStop",
            "BrowserSearch","BrowserFavorites","BrowserHome",

            "VolumeMute","VolumeDown","VolumeUp",

            "MediaNextTrack","MediaPrevTrack","MediaStop","MediaPlayPause",

            "LaunchMail","LaunchMediaSelect","LaunchApp1","LaunchApp2",

            "Key0","Key1","Key2","Key3","Key4","Key5","Key6","Key7","Key8","Key9",

            "A","B","C","D","E","F","G","H","I","J","K","L","M",
            "N","O","P","Q","R","S","T","U","V","W","X","Y","Z"
        };

        static Key::Code FromGLFW(int key);
    };

    //------------------------------------------------------------------------------
    struct Keyboard
    {
        /// contains all keys that was pressed this frame. This is reset every frame
        bool pressed[Key::Code::NumKeyCodes];

        /// contains all keys that was released this frame. This is reset every frame
        bool released[Key::Code::NumKeyCodes];

        /// contains all keys that are currently being held. These are reset as buttons receive the release action
        bool held[Key::Code::NumKeyCodes];
    };

} // namespace Input
