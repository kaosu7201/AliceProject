#include "PlWindows.h"
#include "DirectX/Font/DXFont.h"
#include "DirectX/DirectX11Manager.h"

DirectX11Manager PlWindows::DXManager;

DX11Effect* PlWindows::effect;
InputLayout PlWindows::il;
VertexBuffer PlWindows::vb;
ConstantBuffer PlWindows::cb;
IndexBuffer PlWindows::ib;

PlWindows::PlWindows()
{
 
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

int PlWindows::TextureLoad(string filename)
{
  int idx = Texture.size();
  Texture.push_back(new DX11Texture);
  
  Texture[idx]->DX11TextureLoad(filename);
  return idx;
}

int PlWindows::BlkTextureLoad(string filename, int blkW, int blkH, int blkNum)
{
  int idx = Texture.size();
  Texture.push_back(new DX11Texture);
  
  Texture[idx]->DX11TextureLoad(filename);
  return idx;
}

void PlWindows::DrawIndexed(int start, int FacesNum, vector<AlU32> lpIndex, vector<PolygonVertex> Vertex, int hTexture)
{
	//コンスタントバッファの作成
	struct ConstantBufferData
	{
		XMFLOAT4X4 mtxWorld;
		XMFLOAT4X4 mtxView;
		XMFLOAT4X4 mtxProj;
	};

	if (!effect)
	{
		effect = CreateShader("Assets/Shaders/3DPipeLine.hlsl");

		//InputLayoutの作成
		D3D11_INPUT_ELEMENT_DESC elem[] = {
			{ "POSITION",	0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	0,	D3D11_INPUT_PER_VERTEX_DATA,	0},
			{ "NORMAL"  ,	0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	12,	D3D11_INPUT_PER_VERTEX_DATA,	0},
			{ "COLOR"	,	0,	DXGI_FORMAT_R32G32B32A32_FLOAT,	0,	24,	D3D11_INPUT_PER_VERTEX_DATA,	0},
			{ "TEXCOORD",	0,	DXGI_FORMAT_R32G32_FLOAT,		0,	40,	D3D11_INPUT_PER_VERTEX_DATA,	0},

		};
		il.Attach(PlWindows::DXManager.CreateInputLayout(elem, 4, "Assets/Shaders/3DPipeLine.hlsl", "vsMain"));
		
		PlWindows::DXManager.CreateConstantBuffer(sizeof(ConstantBufferData), &cb);	

		vb.Attach(PlWindows::DXManager.CreateVertexBuffer(Vertex.data(), static_cast<UINT>(Vertex.size())));

	//インデックス情報の設定
	//idxs = { 0,1,2,2,1,3 };

		ib.Attach(PlWindows::DXManager.CreateIndexBuffer(lpIndex.data(), static_cast<UINT>(lpIndex.size())));

	}

	ConstantBufferData constantBuffer;
	XMMATRIX worldMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);

	XMVECTOR eye = XMVectorSet(2.0f, 2.0f, -2.0f, 0.0f);
	XMVECTOR focus = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMMATRIX viewMatrix = XMMatrixLookAtLH(eye, focus, up);

	float    fov = XMConvertToRadians(45.0f);
	float    aspect = 1280 / 720;
	float    nearZ = 0.1f;
	float    farZ = 100.0f;
	XMMATRIX projMatrix = XMMatrixPerspectiveFovLH(fov, aspect, nearZ, farZ);

	XMStoreFloat4x4(&constantBuffer.mtxWorld, XMMatrixTranspose(worldMatrix));
	XMStoreFloat4x4(&constantBuffer.mtxView, XMMatrixTranspose(viewMatrix));
	XMStoreFloat4x4(&constantBuffer.mtxProj, XMMatrixTranspose(projMatrix));

	PlWindows::DXManager.UpdateConstantBuffer(cb.Get(), constantBuffer);

	//ポリゴンを書くための各種パラメータセット
	PlWindows::DXManager.SetVertexShader(effect->vs.Get());
	PlWindows::DXManager.SetPixelShader(effect->ps.Get());

	ID3D11Buffer * tmpCb[] = { cb.Get() };
	PlWindows::DXManager.m_pImContext->VSSetConstantBuffers(0, 1, tmpCb);

	PlWindows::DXManager.SetInputLayout(il.Get());
	PlWindows::DXManager.SetVertexBuffer(vb.Get(), sizeof(Vertex));
	PlWindows::DXManager.SetIndexBuffer(ib.Get());
	PlWindows::DXManager.SetTexture2D(0, Texture[hTexture]->Get());

	//DrawCall
	PlWindows::DXManager.DrawIndexed(static_cast<UINT>(FacesNum * 3), start);
}