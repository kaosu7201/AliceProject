#pragma once
#include <string>
#include "ApplicationBase.h"
#include "AlColor.h"
#include "AlFbxMesh.h"

using namespace std;
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

  virtual void DrawPrintf(int x, int y, AlColor4 color, string str) = 0;
  virtual void DrawFbxMesh(AlFbxMesh *mesh) = 0;

  virtual int TextureLoad(string filename) = 0;
  virtual int BlkTextureLoad(string filename, int blkW, int blkH, int blkNum) = 0;

protected:
  virtual void begin();
  virtual void end();
  virtual bool Input();
  virtual bool Process();
  virtual bool Render();

  static Platform* lpInstance;
};