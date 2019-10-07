#include "InputDevice.h"

CDefaultController::CDefaultController()
{
}

void CDefaultController::UpDate()
{
}

bool CDefaultController::GetButtonState(AlControllerButton ctrl, STATE_TYPE get_type)
{
  bool key(false), mouse(false), pad(false);
  
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
  m_setting[ctrl].pad = pad;
}

void CDefaultController::SetConfigMouse(AlControllerButton ctrl, MOUSE_BUTTON mouse)
{
  m_setting[ctrl].mouse = mouse;
}
