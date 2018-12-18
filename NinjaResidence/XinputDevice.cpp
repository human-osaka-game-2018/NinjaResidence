/**
* @file XinputDevice.cpp
* @brief XinputDevice関連処理を行う
* @author Toshiya Matsuoka
*/
#include "DirectX.h"

#include "XinputDevice.h"


void XinputDevice::GetControl(int GamePadNumber)
{
	XInputGetState(GamePadNumber, &m_Xinput);
}

PADSTATE XinputDevice::GetButton(ButtonIndex index)
{
	return m_PadState[index];
}

void XinputDevice::BottonCheck() {

	CheckButtonState(XINPUT_GAMEPAD_A, ButtonA);
	CheckButtonState(XINPUT_GAMEPAD_B, ButtonB);
	CheckButtonState(XINPUT_GAMEPAD_X, ButtonX);
	CheckButtonState(XINPUT_GAMEPAD_Y, ButtonY);
	CheckButtonState(XINPUT_GAMEPAD_START, ButtonStart);
	CheckButtonState(XINPUT_GAMEPAD_BACK, ButtonBack);
	CheckButtonState(XINPUT_GAMEPAD_LEFT_SHOULDER, ButtonLB);
	CheckButtonState(XINPUT_GAMEPAD_RIGHT_SHOULDER, ButtonRB);
	CheckButtonState(XINPUT_GAMEPAD_DPAD_UP, ButtonUP);
	CheckButtonState(XINPUT_GAMEPAD_DPAD_DOWN, ButtonDOWN);
	CheckButtonState(XINPUT_GAMEPAD_DPAD_LEFT, ButtonLEFT);
	CheckButtonState(XINPUT_GAMEPAD_DPAD_RIGHT, ButtonRIGHT);
	CheckButtonState(XINPUT_GAMEPAD_START, ButtonStart);
	CheckButtonState(XINPUT_GAMEPAD_BACK, ButtonBack);
	CheckButtonState(XINPUT_GAMEPAD_LEFT_THUMB, ButtonLeftThumb);
	CheckButtonState(XINPUT_GAMEPAD_RIGHT_THUMB, ButtonRightThumb);

}

void XinputDevice::DeviceUpdate(int GamePadNumber) {

	GetControl(GamePadNumber);
	BottonCheck();
}
void XinputDevice::CheckButtonState(WORD ButtomID, ButtonIndex ButtomIndex)
{
	if (m_Xinput.Gamepad.wButtons & ButtomID)
	{
		if (m_PadOldState[ButtomIndex] == PadOn)
		{
			m_PadState[ButtomIndex] = PadOn;
		}
		else
		{
			m_PadState[ButtomIndex] = PadPush;
		}

		m_PadOldState[ButtomIndex] = PadOn;
	}
	else
	{
		if (m_PadOldState[ButtomIndex] == PadOn)
		{
			m_PadState[ButtomIndex] = PadRelease;
		}
		else
		{
			m_PadState[ButtomIndex] = PadOff;
		}
		m_PadOldState[ButtomIndex] = PadOff;
	}

}

int XinputDevice::GetAnalogTrigger(AnalogTrigger Trigger)
{
	switch (Trigger)
	{
	case LEFT_TRIGGER:
		return m_Xinput.Gamepad.bLeftTrigger;
	case RIGHT_TRIGGER:
		return m_Xinput.Gamepad.bRightTrigger;

	}
}

bool XinputDevice::GetAnalogL(Analog AnalogState)
{
	switch (AnalogState)
	{
	case ANALOGUP:
		if (m_Xinput.Gamepad.sThumbLY > -65535 / 4)
		{
			return true;
		}
		break;
	case ANALOGDOWN:
		if (m_Xinput.Gamepad.sThumbLY < 65535 / 4)
		{
			return true;
		}
		break;
	case ANALOGLEFT:
		if (m_Xinput.Gamepad.sThumbLX <-65535 / 4)
		{
			return true;
		}
		break;
	case ANALOGRIGHT:
		if (m_Xinput.Gamepad.sThumbLX >65535 / 4)
		{
			return true;
		}
		break;
	default:
		return false;
	}
	return false;
}

bool XinputDevice::GetAnalogR(Analog AnalogState)
{
	switch (AnalogState)
	{
	case ANALOGUP:
		if (m_Xinput.Gamepad.sThumbRY > -65535 / 4)
		{
			return true;
		}
		break;
	case ANALOGDOWN:
		if (m_Xinput.Gamepad.sThumbRY < 65535 / 4)
		{
			return true;
		}
		break;
	case ANALOGLEFT:
		if (m_Xinput.Gamepad.sThumbRX <-65535 / 4)
		{
			return true;
		}
		break;
	case ANALOGRIGHT:
		if (m_Xinput.Gamepad.sThumbRX >65535 / 4)
		{
			return true;
		}
		break;
	default:
		return false;
	}
	return false;
}

int XinputDevice::GetAnalogLValue(Analog AnalogState)
{
	switch (AnalogState)
	{
	case ANALOG_Y:
		return m_Xinput.Gamepad.sThumbLY;
		break;
	case ANALOG_X:
		return m_Xinput.Gamepad.sThumbLX;
		break;
	default:
		return 0;
	}
}

int XinputDevice::GetAnalogRValue(Analog AnalogState)
{
	switch (AnalogState)
	{
	case ANALOG_Y:
		return m_Xinput.Gamepad.sThumbRY;
		break;
	case ANALOG_X:
		return m_Xinput.Gamepad.sThumbRX;
		break;
	default:
		return 0;
	}
}
