#pragma once
#include "../DirectX11Manager.h"
#include "../../../SpriteBase/SpriteBase.h"
class DXSprite :
  public SpriteBase
{
public:
  DXSprite();
  virtual ~DXSprite();

  static void begin_first();

  static void drawAll();

private:
  static DX11Effect *effect;
  static InputLayout il;
  static ShaderTexture texture;
  static VertexBuffer vb;
  static vector<UINT> idxs;
  static IndexBuffer ib;
};

