
#include "PlWindows.h"
#include "DirectX/Sprite/DXSprite.h"
#include "DirectX/Font/DXFont.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  PlWindows* lpPlatform = PlWindows::CreatePlatform();
  if (FAILED(lpPlatform->DXManager.Init(hInstance, nCmdShow)))
    return -1;

  lpPlatform->Initialize();

  DXSprite::begin_first();
  DXFont::init();
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
      lpPlatform->CallFrameProcess();
    }
  }
  return 0;
}
