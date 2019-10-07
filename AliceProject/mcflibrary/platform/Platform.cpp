#include "Platform.h"

Platform* Platform::lpInstance = 0;
Platform::Platform()
{
  lpInstance = this;
}

Platform::~Platform()
{
}

bool Platform::Initialize()
{
  ApplicationBase::CallGetInstance()->CallInitialize();
  return false;
}

bool Platform::Terminate()
{
  ApplicationBase::CallGetInstance()->CallTerminate();
  return false;
}

void Platform::begin()
{
}

void Platform::end()
{
}

bool Platform::Input()
{
  ApplicationBase::CallGetInstance()->CallInput();
  return false;
}

bool Platform::Process()
{
  ApplicationBase::CallGetInstance()->CallProcess();
  return false;
}

bool Platform::Render()
{
  ApplicationBase::CallGetInstance()->CallRender();
  return false;
}
