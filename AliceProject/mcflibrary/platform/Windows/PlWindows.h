#pragma once

#include "DirectX/DirectX11Manager.h"
#include "../Platform.h"
class PlWindows :
  public Platform
{
  typedef Platform base;
public:
  PlWindows();
  virtual ~PlWindows();

  bool Initialize();
  bool Terminate();

  static DirectX11Manager DXManager;
  static PlWindows* CreatePlatform()
  {
    return new PlWindows();
  }

  void DrawPrintf(int x, int y, AlColor4 color, string str);

private:
  void begin()
  {
    DXManager.DrawBegin();
  }
  void end()
  {
    DXManager.DrawEnd();
  }
  bool Input();
  bool Process();
  bool Render();
};

