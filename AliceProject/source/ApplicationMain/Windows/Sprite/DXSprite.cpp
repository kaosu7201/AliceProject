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
ShaderTexture DXSprite::texture;
VertexBuffer DXSprite::vb;
vector<UINT> DXSprite::idxs;
IndexBuffer DXSprite::ib;


DXSprite::DXSprite()
{
}


DXSprite::~DXSprite()
{
}

void DXSprite::begin_first()
{
  effect = CreateShader("Assets/Shaders/2DPipeLine.hlsl");

  //InputLayoutの作成
  D3D11_INPUT_ELEMENT_DESC elem[] = {
    { "POSITION",	0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	0,	D3D11_INPUT_PER_VERTEX_DATA,	0},
    { "COLOR"	,	0,	DXGI_FORMAT_R32G32B32A32_FLOAT,	0,	12,	D3D11_INPUT_PER_VERTEX_DATA,	0},
    { "TEXCOORD",	0,	DXGI_FORMAT_R32G32_FLOAT,		0,	28,	D3D11_INPUT_PER_VERTEX_DATA,	0},
  };
  il.Attach(g_DX11Manager.CreateInputLayout(elem, 3, "Assets/Shaders/2DPipeLine.hlsl", "vsMain"));

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

  //インデックス情報の設定
  idxs = { 0,1,2,2,3,1 };

  ib.Attach(g_DX11Manager.CreateIndexBuffer(idxs.data(), static_cast<UINT>(idxs.size())));

  texture.Attach(g_DX11Manager.CreateTextureFromFile("oharaibou.png"));
}

void DXSprite::drawAll()
{
  //ポリゴンを書くための各種パラメータセット
  g_DX11Manager.SetVertexShader(effect->vs.Get());
  g_DX11Manager.SetPixelShader(effect->ps.Get());

  g_DX11Manager.SetInputLayout(il.Get());
  g_DX11Manager.SetVertexBuffer(vb.Get(), sizeof(Vertex));
  g_DX11Manager.SetIndexBuffer(ib.Get());
  g_DX11Manager.SetTexture2D(0, texture.Get());

  //DrawCall
  g_DX11Manager.DrawIndexed(static_cast<UINT>(idxs.size()));
}
