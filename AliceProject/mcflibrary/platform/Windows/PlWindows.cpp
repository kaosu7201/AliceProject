#include "PlWindows.h"

DirectX11Manager PlWindows::DXManager;
PlWindows::PlWindows()
{
  Initialize();
}


PlWindows::~PlWindows()
{
}

bool PlWindows::Initialize()
{
  base::Initialize();
  return true;
}

bool PlWindows::Terminate()
{
  base::Terminate();
  return true;
}

bool PlWindows::Input()
{
  base::Input();
  return true;
}

bool PlWindows::Process()
{
  base::Process();
  return true;
}

bool PlWindows::Render()
{
  base::Render();
  return true;
}
