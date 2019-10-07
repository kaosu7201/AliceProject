#pragma once
#include "ApplicationBase.h"
class ApplicationMain :
  public ApplicationBase
{
public:
  ApplicationMain();
  virtual ~ApplicationMain();

private:
  bool Initialize();
  bool Terminate();
  bool Input();
  bool Process();
  bool Render();
};

