#pragma once
#include "ButtonSetEnum.h"
#include "AlController.h"

#define KEY_MAX 256
class IKeyInputDevice
{
public:
  IKeyInputDevice() {}
  virtual ~IKeyInputDevice() {}
  virtual void UpDate() = 0;
  virtual void Init() = 0;

  virtual bool GetKeyState(KEYBOARD_BUTTON key, STATE_TYPE get_type = PRESENT) = 0;
};
typedef IKeyInputDevice* IKeyInput;

class CDIKeyBoard :public IKeyInputDevice
{
public:
  CDIKeyBoard() {}
  virtual ~CDIKeyBoard() {}
  void UpDate();
  void Init();

  bool GetKeyState(KEYBOARD_BUTTON key, STATE_TYPE get_type = PRESENT);

  static IKeyInput Create();
private:
  // �L�[���
  BYTE keys[KEY_MAX];
  // �O�̃L�[���
  BYTE olds[KEY_MAX];
};