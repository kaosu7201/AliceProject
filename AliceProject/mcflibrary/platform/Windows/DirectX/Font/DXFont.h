#pragma once
#include "../../PlWindows.h"
#include <map>

class DXFont
{
public:
  static void init();
  static ID3D11ShaderResourceView* GetFontTexture(const char *c);
  static ID3D11ShaderResourceView* CreateFontTexture(const char *c);
  static void DrawFont(const char *c, int x, int y, AlColor4 color);

  static void SetfontXY(int x, int y) { fontX = x; fontY = y; }

private:
  static map<string, DX11Texture> FontTex;
  static HDC hdc;
  static int fontX, fontY;
};