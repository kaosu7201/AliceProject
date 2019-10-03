#include "InputDevice.h"

CDefaultController::CDefaultController(IKeyInput keyboard, IMouseInput mouse)
{
}

void CDefaultController::UpDate()
{
}

bool CDefaultController::GetButtonState(AlControllerButton ctrl, STATE_TYPE get_type)
{
  return false;
}

void CDefaultController::GetRelativePos(double & x, double & y)
{
}

void CDefaultController::GetAbsScreenPos(double & x, double & y)
{
}

void CDefaultController::GetWheelMove(double & z)
{
}

void CDefaultController::SetDefault()
{

}

void CDefaultController::SetConfigKeyBoard(AlControllerButton ctrl, KEYBOARD_BUTTON key)
{
  m_setting[ctrl].key = key;
}

void CDefaultController::SetConfigGamePad(AlControllerButton ctrl, GAMEPAD_BUTTON pad)
{
}

void CDefaultController::SetConfigMouse(AlControllerButton ctrl, MOUSE_BUTTON mouse)
{
}
