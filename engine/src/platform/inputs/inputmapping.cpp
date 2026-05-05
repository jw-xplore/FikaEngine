#include "inputmapping.h"

//----------------------------------------------
// Input types
//----------------------------------------------
/*
ButtonInputEvent::ButtonInputEvent(EInputDevice device, int button)
{
	inputData.device = device;
	inputData.handlingType = EInputHandlingType::Button;
	input.button = button;
}

bool ButtonInputEvent::IsPressed()
{
	switch (inputData.device)
	{
	case EInputDevice::DeviceKeyboard: return Input::GetDefaultKeyboard()->held[input.button];
	case EInputDevice::DeviceMouse: return Input::GetDefaultMouse()->held[input.button];
	case EInputDevice::DeviceGamepadButtons: return Input::GetGamepad(0)->buttonHeld[input.button];

		// Gamepad axes
	case EInputDevice::DeviceGamepadAxes:
	{
		return Input::GetGamepad(0)->axesValues[input.button] > 0;
	}

	//End
	}

	return false;
}

float ButtonInputEvent::InputAxis()
{
	switch (inputData.device)
	{
	case EInputDevice::DeviceKeyboard: return Input::GetDefaultKeyboard()->held[input.button];
	case EInputDevice::DeviceMouse: return Input::GetDefaultMouse()->held[input.button];
	case EInputDevice::DeviceGamepadButtons: return Input::GetGamepad(0)->buttonHeld[input.button];
	case EInputDevice::DeviceGamepadAxes: return Input::GetGamepad(0)->axesValues[input.button];
	}

	return 0;
}

// Axis input
AxisInputEvent::AxisInputEvent(EInputDevice device, int positive, int negative)
{
	inputData.device = device;
	inputData.handlingType = EInputHandlingType::Axis;
	input.positive = positive;
	input.negative = negative;
}

bool AxisInputEvent::IsPressed()
{
	switch (inputData.device)
	{
	case DeviceKeyboard: return Input::GetDefaultKeyboard()->held[input.positive] || Input::GetDefaultKeyboard()->held[input.negative];
	case DeviceMouse: return Input::GetDefaultMouse()->held[input.positive] || Input::GetDefaultMouse()->held[input.negative];

		// Gamepad buttons
	case EInputDevice::DeviceGamepadButtons:
	{
		return Input::GetGamepad(0)->buttonHeld[input.positive] || Input::GetGamepad(0)->buttonHeld[input.negative];
	}

	// Gamepad axes
	case EInputDevice::DeviceGamepadAxes:
	{
		// Use only positive input
		return Input::GetGamepad(0)->axesValues[input.positive] != 0;
	}

	// End
	}

	return true;
}

float AxisInputEvent::inputAxis()
{
	switch (inputData.device)
	{

	case DeviceKeyboard:
	{
		if (Input::GetDefaultKeyboard()->held[input.positive])
			return 1;
		else if (Input::GetDefaultKeyboard()->held[input.negative])
			return -1;

		return 0;
	}

	case DeviceMouse:
	{
		if (Input::GetDefaultMouse()->held[input.positive])
			return 1;
		else if (Input::GetDefaultMouse()->held[input.negative])
			return -1;

		return 0;
	}

	// End
	}

	return 0;
}

//----------------------------------------------
// Input system
//----------------------------------------------

InputMapping* InputMapping::instance = new InputMapping();

InputMapping::InputMapping()
{
	LoadInputMapping();
}

InputMapping::~InputMapping()
{

}

void InputSyInputMappingstem::SetDefaultInputMapping()
{
	actions.clear();

	actions = {
		{ "Forward", new ButtonInputEvent(EInputDevice::DeviceKeyboard, Input::Key::W) },
		{ "Boost", new ButtonInputEvent(EInputDevice::DeviceKeyboard, Input::Key::Shift) },
		{ "Yaw", new AxisInputEvent(EInputDevice::DeviceKeyboard, Input::Key::Left, Input::Key::Right) }, // Around Y axis
		{ "Roll", new AxisInputEvent(EInputDevice::DeviceKeyboard, Input::Key::D, Input::Key::A) },
		{ "Pitch", new AxisInputEvent(EInputDevice::DeviceKeyboard, Input::Key::Up, Input::Key::Down) },
		{ "Shoot", new ButtonInputEvent(EInputDevice::DeviceKeyboard, Input::Key::Space) }
	};
}

void InputMapping::LoadInputMapping()
{
	// Read json
	std::ifstream file(this->filePath);
	if (!file.is_open())
	{
		// Fill with default setting
		SetDefaultInputMapping();
		SaveInputMapping();
		return;
	}

	// Parse data
	nlohmann::ordered_json jsonRes = nlohmann::ordered_json::parse(file);
	file.close();

	//tartingPopulation = jsonRes["worldData"]["population"];
	//ironOreAmount = jsonRes["worldData"]["ironOreAmount"];

	actions.clear();

	nlohmann::json inputMapping = jsonRes["inputMapping"];
	for (auto& action : inputMapping.items())
	{
		std::string name = action.value()["name"];

		InputEvent* event;

		// Setup handling
		EInputHandlingType type = action.value()["handlingType"];
		EInputDevice device = action.value()["device"];
		nlohmann::json handling = action.value()["handling"];

		switch (type)
		{
		case EInputHandlingType::Button: event = new ButtonInputEvent(device, handling["button"]); break;
		case EInputHandlingType::Axis: event = new AxisInputEvent(device, handling["positive"], handling["negative"]); break;
			// End
		}

		// Fill data
		event->inputData.name = name;
		actions[name] = event;
	}

}

void InputMapping::SaveInputMapping()
{
	nlohmann::json j;

	// Prepare list
	nlohmann::json list = nlohmann::json::array();

	for (auto const& action : actions)
	{
		InputMappingEntry mapping = action.second->inputData;

		nlohmann::json actionEntry = nlohmann::json::object();
		actionEntry.push_back({ "name", action.first });
		actionEntry.push_back({ "device", mapping.device });
		actionEntry.push_back({ "handlingType", mapping.handlingType });

		// Handling type serialization
		nlohmann::json handling = nlohmann::json::object();

		switch (mapping.handlingType)
		{
		case EInputHandlingType::Button:
		{
			ButtonInputEvent* event = dynamic_cast<ButtonInputEvent*>(action.second);
			handling.push_back({ "button", event->input.button });
			break;
		}

		case EInputHandlingType::Axis:
		{
			AxisInputEvent* event = dynamic_cast<AxisInputEvent*>(action.second);
			handling.push_back({ "positive", event->input.positive });
			handling.push_back({ "negative", event->input.negative });
			break;
		}

		// End
		}

		actionEntry["handling"] = handling;

		// Push to list
		list.push_back(actionEntry);
	}

	j["inputMapping"] = list;

	// Save
	std::ofstream file;
	file.open(filePath);
	file << std::setw(4) << j;
	file.close();
}
*/