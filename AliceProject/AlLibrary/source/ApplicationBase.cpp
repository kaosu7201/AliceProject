#include "ApplicationBase.h"



ApplicationBase::ApplicationBase()
{
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
