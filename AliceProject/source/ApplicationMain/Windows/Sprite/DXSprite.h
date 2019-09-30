#pragma once
#include "../DirectX11Manager.h"
#include "../../../SpriteBase/SpriteBase.h"
class DXSprite :
  public SpriteBase
{
public:
  DXSprite();
  DXSprite(int screenWidth, int screenHeight);
  DXSprite(const DXSprite &r);
  virtual ~DXSprite();

  DXSprite& operator=(const DXSprite &r){ copy(r); return *this; }

  static void begin_first();
  static void clearDrawList();
  void setScreenSize(int w, int h);
  void setSize(int w, int h);
  void setPivot(float x, float y);
  void getPivot(float *x, float *y);
  void setPos(float x, float y);
  void getPos(float *x, float *y);
  void setRotate(float deg);
  float getRotate();
  void setScale(float sx, float sy);
  void getScale(float *sx, float *sy);
  void setTexture(DX11Texture* Texture, bool isResize);
  ID3D11ShaderResourceView* getTexture();
  void setUV(float left, float top, float width, float height);
  void getUV_LT(float *left, float *top);
  void getUV_WH(float *width, float *height);
  void setRGB(float r, float g, float b);
  void getRGB(float *r, float *g, float *b);
  void setAlpha(float a);
  float getAlpha();
  void setPriority(float z);
  float getPriority();
  void setActivity(bool isActive);
  bool getActivity();
  void draw();
  static void drawAll();

private:
  static DX11Effect *effect;
  static InputLayout il;
  static VertexBuffer vb;
  static ConstantBuffer cb;
  static vector<UINT> idxs;
  static IndexBuffer ib;
  static list<DXSprite*> SpriteList;

  int scW, scH;
  int polyW, polyH;
  float pivotX, pivotY;
  float posX, posY, posZ;
  float rad;
  float scaleX, scaleY;
  ShaderTexture tex;
  float uvLeft, uvTop, uvW, uvH;
  float r, g, b;
  float alpha;
  float priority;
  bool bActivity;

  //ÉRÉsÅ[
  void copy(const DXSprite &r);
};

