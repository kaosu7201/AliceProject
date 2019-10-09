#include "InputDevice.h"

CDefaultController::CDefaultController()
{
  InputDevice.CreateInput();
}

void CDefaultController::UpDate()
{
}

bool CDefaultController::GetButtonState(AlControllerButton ctrl, STATE_TYPE get_type)
{
  bool key(false), mouse(false), pad(false);
  
  return false;
}

const AlVector2 CDefaultController::GetLeftStick() const
{
  return AlVector2();
}

const AlVector2 CDefaultController::GetRightStick() const
{
  return AlVector2();
}

AlVector2 CDefaultController::GetRelativePos()
{
  return AlVector2();
}

AlVector2 CDefaultController::GetAbsScreenPos()
{
  return AlVector2();
}

double CDefaultController::GetWheelMove()
{
  return 0;
}

void CDefaultController::SetDefault()
{

}

void CDefaultController::SetConfigKeyBoard(AlControllerButton ctrl, KEYBOARD_BUTTON key)
{
  m_setting[ctrl].key = key;
}

void CDefaultController::SetConfigMouse(AlControllerButton ctrl, MOUSE_BUTTON mouse)
{
  m_setting[ctrl].mouse = mouse;
}

void CDefaultController::SetConfigGamepad(AlControllerButton ctrl, GAMEPAD_BUTTON pad)
{
  m_setting[ctrl].pad = pad;
}
