#include <Windows.h>

#include "DirectX11Manager.h"
#include "Defs.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  DirectX11Manager manager;

  if (FAILED(manager.Init(hInstance, nCmdShow))) return -1;
  MSG msg = { 0 };

  //メッセージループ
  while (WM_QUIT != msg.message)
  {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }

    manager.DrawBegin();



    manager.DrawEnd();
  }


  return 0;
}
