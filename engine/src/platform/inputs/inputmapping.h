#pragma once
#include <vector>
#include <map>
#include <string>
#include "inputhandler.h"

//----------------------------------------------
// Input types
//----------------------------------------------

enum EInputDevice
{
	DeviceKeyboard,
	DeviceMouse,
	//DeviceGamepadButtons,
	//DeviceGamepadAxes,
	EInputDeviceCount,
};

constexpr static const char* const DeviceNames[EInputDevice::EInputDeviceCount] =
{
	"Keyboard",
	"Mouse",
	//"Gamepad - Buttons",
	//"Gamepad - Axes",
};

enum EInputHandlingType
{
	Button,
	Axis,
};

struct InputMappingEntry
{
	std::string name;
	EInputDevice device;
	EInputHandlingType handlingType;
};

struct InputHandlingButton
{
	int button;
};

struct InputHandlingAxis
{
	int positive;
	int negative;
};

class InputEvent
{
public:
	InputMappingEntry inputData;

	virtual bool isPressed() { return false; }
	virtual float inputAxis() { return 0; }
};

class ButtonInputEvent : public InputEvent
{
public:
	InputHandlingButton input;

	ButtonInputEvent() {}
	ButtonInputEvent(EInputDevice device, int button);

	bool isPressed() override;
	float inputAxis() override;
};

class AxisInputEvent : public InputEvent
{
public:
	InputHandlingAxis input;

	AxisInputEvent() {}
	AxisInputEvent(EInputDevice device, int positive, int negative);

	bool isPressed() override;
	float inputAxis() override;
};

//----------------------------------------------
// Input system
//----------------------------------------------
class InputMapping
{
private:
	static InputMapping* instance;
	std::map<std::string, InputEvent*> actions;

public:
	const const char* filePath = "InputMapping.json";

	static InputMapping* GetInstance()
	{
		if (!instance)
			instance = new InputMapping();

		return instance;
	}

	InputMapping();
	~InputMapping();

	/**
	 * @brief Get action of matching string from input map.
	 * @param name 
	 * @return InputEvent pointer to action.
	 */
	inline InputEvent* getAction(std::string name) { return actions[name]; }

	/**
	 * @brief Replace current inputs map with default mapping. Doesn't influence input mapping file.
	 */
	void setDefaultInputMapping();

	/**
	 * @brief Load stored input mapping file from filePath.
	 */
	void loadInputMapping();

	/**
	 * @brief Save current state of inputs map at filePath.
	 */
	void saveInputMapping();
};