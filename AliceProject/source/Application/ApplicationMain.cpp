#include "ApplicationMain.h"
#include "mcfallib.h"

#include <AlFbxMesh.h>

ApplicationMain g_oApplicationMain;
ApplicationMain::ApplicationMain()
{
}


ApplicationMain::~ApplicationMain()
{
}

bool ApplicationMain::Initialize()
{
	LoadFbxMesh("EXLumia.fbx","Player");
	//LoadFbxMesh("a.fbx", "Player");
	return false;
}

bool ApplicationMain::Terminate()
{
  return false;
}

bool ApplicationMain::Input()
{
  return false;
}

bool ApplicationMain::Process()
{
  return false;
}

bool ApplicationMain::Render()
{
  gFbxModel["Player"]->Render();
  DrawPrintf(400, 360, AlColor4{ 1,1,1,1 }, "abcdefg%f", 10.6754);
  return false;
}
