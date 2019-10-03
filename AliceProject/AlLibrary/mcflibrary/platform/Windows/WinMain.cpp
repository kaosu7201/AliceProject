
#include "DirectX/DirectX11Manager.h"
#include "DirectX/Sprite/DXSprite.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  if (FAILED(g_DX11Manager.Init(hInstance, nCmdShow)))
    return -1;

  DXSprite::begin_first();

  MSG msg = { 0 };

  //メッセージループ
  while (WM_QUIT != msg.message)
  {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else
    {
      g_DX11Manager.DrawBegin();

      g_DX11Manager.DrawEnd();
    }
  }
  return 0;
}
