#include "DXSprite.h"

//頂点情報を設定
struct Vertex
{
  XMFLOAT3 pos;
  XMFLOAT4 col;
  XMFLOAT2 uv;
};

DX11Effect* DXSprite::effect;
InputLayout DXSprite::il;
list<DXSprite*> DXSprite::SpriteList;
VertexBuffer DXSprite::vb;
ConstantBuffer DXSprite::cb;
vector<UINT> DXSprite::idxs;
IndexBuffer DXSprite::ib;

struct ConstantBufferData
{
  XMMATRIX mtxWorld;
  XMMATRIX mtxProj;
  float uv_left;
  float uv_top;
  float uv_width;
  float uv_height;
  float alpha;
};

DXSprite::DXSprite(int screenWidth, int screenHeight) :
  polyW(128), polyH(128),
  pivotX(), pivotY(),
  posX(), posY(), posZ(),
  rad(),
  scaleX(1.0f), scaleY(1.0f),
  uvLeft(), uvTop(),
  uvW(1.0f), uvH(1.0f),
  alpha(1.0f),
  bActivity(true)
{
  setScreenSize(screenWidth, screenHeight);
}

DXSprite::DXSprite(const DXSprite & r)
{
  copy(r);
}

DXSprite::DXSprite() :
  polyW(128), polyH(128),
  pivotX(), pivotY(),
  posX(), posY(), posZ(),
  rad(),
  scaleX(1.0f), scaleY(1.0f),
  uvLeft(), uvTop(),
  uvW(1.0f), uvH(1.0f),
  alpha(1.0f),
  bActivity(true)
{
  setScreenSize(640, 480);
}

DXSprite::~DXSprite()
{
}

void DXSprite::begin_first()
{
  effect = CreateShader("Assets/Shaders/2DPipeLine1.hlsl");

  //InputLayoutの作成
  D3D11_INPUT_ELEMENT_DESC elem[] = {
    { "POSITION",	0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	0,	D3D11_INPUT_PER_VERTEX_DATA,	0},
    { "COLOR"	,	0,	DXGI_FORMAT_R32G32B32A32_FLOAT,	0,	12,	D3D11_INPUT_PER_VERTEX_DATA,	0},
    { "TEXCOORD",	0,	DXGI_FORMAT_R32G32_FLOAT,		0,	28,	D3D11_INPUT_PER_VERTEX_DATA,	0},
  };
  il.Attach(g_DX11Manager.CreateInputLayout(elem, 3, "Assets/Shaders/2DPipeLine1.hlsl", "vsMain"));

  //頂点情報を設定
  struct Vertex
  {
    XMFLOAT3 pos;
    XMFLOAT4 col;
    XMFLOAT2 uv;
  };
  vector<Vertex> vertexs =
  {
    { XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT4(1,1,1,1),XMFLOAT2(0,0)},
    { XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT4(1,1,1,1),XMFLOAT2(1,0)},
    { XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT4(1,1,1,1),XMFLOAT2(0,1)},
    { XMFLOAT3(1.0f, 1.0f, 0.0f), XMFLOAT4(1,1,1,1),XMFLOAT2(1,1)}
  };

  vb.Attach(g_DX11Manager.CreateVertexBuffer(vertexs.data(), static_cast<UINT>(vertexs.size())));

  //コンスタントバッファの作成
  g_DX11Manager.CreateConstantBuffer(sizeof(ConstantBufferData), &cb);

  //インデックス情報の設定
  idxs = { 0,1,2,2,1,3 };

  ib.Attach(g_DX11Manager.CreateIndexBuffer(idxs.data(), static_cast<UINT>(idxs.size())));
}

void DXSprite::clearDrawList()
{
  SpriteList.clear();
}

void DXSprite::setScreenSize(int w, int h)
{
  scW = w;
  scH = h;
}

void DXSprite::setSize(int w, int h)
{
  polyW = w;
  polyH = h;
}

void DXSprite::setPivot(float x, float y)
{
  pivotX = x;
  pivotY = y;
}

void DXSprite::getPivot(float * x, float * y)
{
  *x = pivotX;
  *y = pivotY;
}

void DXSprite::setPos(float x, float y)
{
  posX = x;
  posY = y;
}

void DXSprite::getPos(float * x, float * y)
{
  *x = posX;
  *y = posY;
}

void DXSprite::setRotate(float deg)
{
  rad = deg;
}

float DXSprite::getRotate()
{
  return rad;
}

void DXSprite::setScale(float sx, float sy)
{
  scaleX = sx;
  scaleY = sy;
}

void DXSprite::getScale(float * sx, float * sy)
{
  *sx = scaleX;
  *sy = scaleY;
}

void DXSprite::setTexture(DX11Texture* Texture, bool isResize)
{
  ID3D11ShaderResourceView* tex;
  if (Texture)
    tex = Texture->tex.Get();
  if(tex)
  Texture->tex->AddRef();
  if (this->tex)
    this->tex->Release();
  this->tex.Attach(tex);

  if (isResize == true)
  {
    polyW = Texture->blkW;
    polyH = Texture->blkH;
  }
}

ID3D11ShaderResourceView * DXSprite::getTexture()
{
  return tex.Get();
}

void DXSprite::setUV(float left, float top, float width, float height)
{
  uvLeft = left;
  uvTop = top;
  uvW = width;
  uvH = height;
}

void DXSprite::getUV_LT(float * left, float * top)
{
  *left = uvLeft;
  *top = uvTop;
}

void DXSprite::getUV_WH(float * width, float * height)
{
  *width = uvW;
  *height = uvH;
}

void DXSprite::setRGB(float r, float g, float b)
{
  this->r = r;
  this->g = g;
  this->b = b;
}

void DXSprite::getRGB(float * r, float * g, float * b)
{
  *r = this->r;
  *g = this->g;
  *b = this->b;
}

void DXSprite::setAlpha(float a)
{
  alpha = a;
}

float DXSprite::getAlpha()
{
  return alpha;
}

void DXSprite::setPriority(float z)
{
  priority = z;
}

float DXSprite::getPriority()
{
  return priority;
}

void DXSprite::setActivity(bool isActive)
{
  bActivity = isActive;
}

bool DXSprite::getActivity()
{
  return bActivity;
}

void DXSprite::setTrans(bool isTrans)
{
  bTrans = isTrans;
}

bool DXSprite::getTrans()
{
  return bTrans;
}

void DXSprite::draw(bool isTrans)
{
  if (isTrans != true)
  {
    alpha = (float)g_pal / 255.0f;
  }
  else
  {
    alpha = 1;
  }
  SpriteList.push_back(this);
}

void DXSprite::drawAll()
{
  ConstantBufferData constantBuffer;
  constantBuffer.mtxProj = XMMatrixIdentity();
  constantBuffer.mtxProj.r[0].m128_f32[3] = -1;
  constantBuffer.mtxProj.r[1].m128_f32[3] = 1;

  for (auto itr = SpriteList.begin(); itr != SpriteList.end(); itr++)
  {
    DXSprite* sp = *itr;
    if (sp->bActivity == false)
      continue;
    constantBuffer.mtxProj.r[0].m128_f32[0] = 2.0f / sp->scW;
    constantBuffer.mtxProj.r[1].m128_f32[1] = -2.0f / sp->scH;

    // ワールド変換行列作成
    XMMATRIX world, scale, rot;
    float pivot_x, pivot_y;
    world = XMMatrixScaling((float)sp->polyW, (float)sp->polyH, 1.0f);
    scale = XMMatrixScaling(sp->scaleX, sp->scaleY, 1.0f);
    pivot_x = (sp->polyW * sp->scaleX) * sp->pivotX;
    pivot_y = (sp->polyH * sp->scaleY) * sp->pivotY;
    rot = XMMatrixRotationZ(sp->rad);
    world.r[0].m128_f32[3] = -sp->pivotX;
    world.r[1].m128_f32[3] = -sp->pivotY;
    world = world * scale * rot;
    world.r[0].m128_f32[3] = sp->posX + pivot_x;
    world.r[1].m128_f32[3] = sp->posY + pivot_y;

    constantBuffer.mtxWorld = world;
    constantBuffer.uv_left = sp->uvLeft;
    constantBuffer.uv_top = sp->uvTop;
    constantBuffer.uv_width = sp->uvW;
    constantBuffer.uv_height = sp->uvH;
    constantBuffer.alpha = sp->alpha;
    g_DX11Manager.UpdateConstantBuffer(cb.Get(), constantBuffer);

    //ポリゴンを書くための各種パラメータセット
    g_DX11Manager.SetVertexShader(effect->vs.Get());
    g_DX11Manager.SetPixelShader(effect->ps.Get());

    ID3D11Buffer * tmpCb[] = { cb.Get() };
    g_DX11Manager.m_pImContext->VSSetConstantBuffers(0, 1, tmpCb);

    g_DX11Manager.SetInputLayout(il.Get());
    g_DX11Manager.SetVertexBuffer(vb.Get(), sizeof(Vertex));
    g_DX11Manager.SetIndexBuffer(ib.Get());
    g_DX11Manager.SetTexture2D(0, sp->tex.Get());

    //DrawCall
    g_DX11Manager.DrawIndexed(static_cast<UINT>(idxs.size()));
  }
}

void DXSprite::copy(const DXSprite &r)
{
  r.tex->AddRef();
  tex = r.tex;
  polyW = r.polyW;
  polyH = r.polyH;
  pivotX = r.pivotX;
  pivotY = r.pivotY;
  posX = r.posX;
  posY = r.posY;
  posZ = r.posZ;
  rad = r.rad;
  scaleX = r.scaleX;
  scaleY = r.scaleY;
  uvLeft = r.uvLeft;
  uvTop = r.uvTop;
  uvW = r.uvW;
  uvH = r.uvH;
  alpha = r.alpha;
  scW = r.scW;
  scH = r.scH;
  bActivity = r.bActivity;
}
