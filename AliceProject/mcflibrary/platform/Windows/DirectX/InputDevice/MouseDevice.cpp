#include "MouseDevice.h"

void CDIMouse::UpDate()
{
}

bool CDIMouse::GetButtonState(MOUSE_BUTTON button, STATE_TYPE get_type)
{
  return false;
}

bool CDIMouse::GetRelativePos(double & x, double & y)
{
  return false;
}

bool CDIMouse::GetAbsScreenPos(double & x, double & y)
{
  return false;
}

bool CDIMouse::GetWheelMove(double & z)
{
  return false;
}

IMouseInput CDIMouse::Create()
{
  return IMouseInput();
}
