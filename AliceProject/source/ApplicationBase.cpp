#include "ApplicationBase.h"


ApplicationBase* ApplicationBase::_lpInstance = 0;
ApplicationBase::ApplicationBase()
{
  _lpInstance = this;
}


ApplicationBase::~ApplicationBase()
{
}

bool ApplicationBase::CallInitialize()
{
  return Initialize();
}

bool ApplicationBase::CallTerminate()
{
  return Terminate();
}

bool ApplicationBase::CallInput()
{
  return Input();
}

bool ApplicationBase::CallProcess()
{
  return Process();
}

bool ApplicationBase::CallRender()
{
  return Render();
}
