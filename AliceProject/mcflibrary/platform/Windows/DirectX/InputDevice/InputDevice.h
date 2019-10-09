#pragma once
#include "../DirectX11Manager.h"

#include "ButtonSetEnum.h"
#include "AlController.h"
#include "KeyboardDevice.h"
#include "MouseDevice.h"


struct ButtonSet
{
  KEYBOARD_BUTTON key;
  GAMEPAD_BUTTON pad;
  MOUSE_BUTTON mouse;
};

class CDefaultController : public _IController
{
  typedef _IController *Super;
private:
  ButtonSet m_setting[GCBTN_NUM];
  DXInput InputDevice;
public:
  CDefaultController();
  ~CDefaultController() {}
  void UpDate();

  //入力処理
  bool GetButtonState(AlControllerButton ctrl, STATE_TYPE get_type = PRESENT);
  const AlVector2 GetLeftStick() const;
  const AlVector2 GetRightStick() const;
  AlVector2 GetRelativePos();
  AlVector2 GetAbsScreenPos();
  double GetWheelMove();

  //キーコンフィグ
  void SetDefault();
  void SetConfigKeyBoard(AlControllerButton ctrl, KEYBOARD_BUTTON key);
  void SetConfigMouse(AlControllerButton ctrl, MOUSE_BUTTON key);
  void SetConfigGamepad(AlControllerButton ctrl, GAMEPAD_BUTTON pad);
};