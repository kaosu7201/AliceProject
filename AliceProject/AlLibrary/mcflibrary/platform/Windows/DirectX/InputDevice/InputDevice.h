#pragma once
#include "../DirectX11Manager.h"

#include "AlController.h"
#include "ButtonSetEnum.h"
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
public:
  CDefaultController(IKeyInput keyboard, IMouseInput mouse);
  ~CDefaultController() {}
  void UpDate();

  //入力処理
  bool GetButtonState(AlControllerButton ctrl, STATE_TYPE get_type = PRESENT);
  void GetRelativePos(double &x, double &y);
  void GetAbsScreenPos(double &x, double &y);
  void GetWheelMove(double &z);

  //キーコンフィグ
  void SetDefault();
  void SetConfigKeyBoard(AlControllerButton ctrl, KEYBOARD_BUTTON key);
  void SetConfigGamePad(AlControllerButton ctrl, GAMEPAD_BUTTON pad);
  void SetConfigMouse(AlControllerButton ctrl, MOUSE_BUTTON mouse);
};