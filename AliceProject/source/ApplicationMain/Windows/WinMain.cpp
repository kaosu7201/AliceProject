
#include "DirectX11Manager.h"
#include "Sprite/DXSprite.h"
#include "Defs.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  if (FAILED(g_DX11Manager.Init(hInstance, nCmdShow)))
    return -1;

  DXSprite::begin_first();

  MSG msg = { 0 };

  DX11Texture texture;
  setPremulpryFlag(true);
  texture.DX11TextureLoad("oharaibou.png");

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
      DXSprite sp(1280, 720);
      sp.setTexture(&texture, true);
      sp.setPos(0, 0);
      sp.setScale(10, 10);
      SetDrawBlendMode(BLENDMODE_PMA_ALPHA, 255);
      sp.draw(true);
      DXSprite::drawAll();
      DXSprite::clearDrawList();
      g_DX11Manager.DrawEnd();
    }
  }
  return 0;
}
