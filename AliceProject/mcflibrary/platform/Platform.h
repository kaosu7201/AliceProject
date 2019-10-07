#pragma once
#include "ApplicationBase.h"
class Platform
{
public:
  Platform();
  virtual ~Platform();

  virtual bool Initialize();
  virtual bool Terminate();
  virtual bool CallFrameProcess()
  {
    begin();
    if (Input() == false)
    {
      return false;
    }
    if (Process() == false)
    {
      return false;
    }
    if (Render() == false)
    {
      return false;
    }
    end();
    return true;
  }
  static Platform* GetInstance() { return lpInstance; }

protected:
  virtual void begin();
  virtual void end();
  virtual bool Input();
  virtual bool Process();
  virtual bool Render();

  static Platform* lpInstance;
};