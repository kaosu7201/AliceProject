#pragma once

#pragma once
#define _CRT_SECURE_NO_WARNINGS
//WindowsDirectX
#include <windows.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <DirectXTex.h>
#include <wrl/client.h>

#include <string>
#include <iostream>
#include <fstream>
#include <codecvt>
#include <vector>
#include <list>
#include <unordered_map>

#include "BlendMode/DX11BlendMode.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxgi.lib")

// DirectInput
#include "InputDevice/DXInput.h"
#define DIRECTINPUT_VERSION     0x0800          // DirectInputのバージョン指定
#include <dinput.h>
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

// define
#define DINPUT_KEYBOARD		(1<<0)
#define DINPUT_MOUSE			(1<<1)
#define DINPUT_JOYSTICK		(1<<2)

using Microsoft::WRL::ComPtr;
using namespace DirectX;
using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::list;

//書きやすいようにtypedef色々
typedef ComPtr<ID3D11Buffer> ConstantBuffer, VertexBuffer, IndexBuffer, StructuredBuffer;
typedef ComPtr<ID3D11InputLayout> InputLayout;
typedef ComPtr<ID3D11VertexShader> VertexShader;
typedef ComPtr<ID3D11GeometryShader> GeometryShader;
typedef ComPtr<ID3D11PixelShader> PixelShader;
typedef ComPtr<ID3D11ComputeShader> ComputeShader;
typedef ComPtr<ID3D11Texture2D> Texture2D;
typedef ComPtr<ID3D11ShaderResourceView> ShaderTexture;
typedef ComPtr<ID3D11UnorderedAccessView> ComputeOutputView;

class DirectX11Manager
{
  HWND hWnd = NULL;
public:
  HWND gethWd() { return hWnd; }
  //DX11
  ComPtr<ID3D11Device>			m_pDevice = nullptr;
  ComPtr<ID3D11DeviceContext>		m_pImContext = nullptr;
  ComPtr<IDXGISwapChain>			m_pSwapChain = nullptr;
  Texture2D						m_pRTTex = nullptr;
  ComPtr<ID3D11RenderTargetView>	m_pRTView = nullptr;
  D3D11_VIEWPORT					m_Viewport = { 0,0,0,0,0,0 };
  ComPtr<ID3D11RasterizerState>	m_pRasterizerState = nullptr;

  //Zバッファ
  ComPtr<ID3D11Texture2D>			m_pTexture2DDepth = nullptr;
  ComPtr<ID3D11DepthStencilState>	m_pDepthStencilState = nullptr;	// Ｚバッファ、ステンシルステート
  ComPtr<ID3D11DepthStencilView>	m_pDepthStencilView = nullptr;

  //サンプラー
  ComPtr<ID3D11SamplerState>		m_pSampler = nullptr; //通常テクスチャ(0-1サンプリング)

  HRESULT Init(HINSTANCE hInstance, int cCmdShow);

  //Shader
  ID3D11VertexShader* CreateVertexShader(const string& filename, const string& entrypath = "", bool erorr = true);
  ID3D11PixelShader* CreatePixelShader(const string& filename, const string& entrypath = "", bool erorr = true);
  ID3D11GeometryShader* CreateGeometryShader(const string& filename, const string& entrypath = "", bool erorr = true);
  ID3D11ComputeShader* CreateComputeShader(const string& filename, const string& entrypath = "");

  //inputlayout作成
  ID3D11InputLayout* CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* layout, UINT elem_num, const string& filename, const string& entrypath = "");

  //コンスタントバッファを作成
  bool CreateConstantBuffer(unsigned int bytesize, ID3D11Buffer** CBuffer);
  template<class x>
  void UpdateConstantBuffer(ID3D11Buffer* buffer, const x& cb)
  {
    m_pImContext->UpdateSubresource(buffer, 0, NULL, &cb, 0, 0);
  }

  //bufferCreate
  template<class x>
  ID3D11Buffer* CreateVertexBuffer(x* VertexData, UINT VertexNum)
  {
    //頂点バッファ作成
    D3D11_BUFFER_DESC hBufferDesc;
    ZeroMemory(&hBufferDesc, sizeof(hBufferDesc));
    hBufferDesc.ByteWidth = sizeof(x) * VertexNum;
    hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    hBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    hBufferDesc.CPUAccessFlags = 0;
    //hBufferDesc.MiscFlags = 0;
    //hBufferDesc.StructureByteStride = sizeof(float);

    D3D11_SUBRESOURCE_DATA hSubResourceData;
    ZeroMemory(&hSubResourceData, sizeof(hSubResourceData));
    hSubResourceData.pSysMem = VertexData;
    //hSubResourceData.SysMemPitch = 0;
    //hSubResourceData.SysMemSlicePitch = 0;

    ID3D11Buffer* hpBuffer;
    if (FAILED(m_pDevice->CreateBuffer(&hBufferDesc, &hSubResourceData, &hpBuffer)))
    {
      return nullptr;
    }
    return hpBuffer;
  }
  ID3D11Buffer* CreateIndexBuffer(UINT* Index, UINT IndexNum)
  {
    //インデックスバッファ作成
    D3D11_BUFFER_DESC hBufferDesc;
    ZeroMemory(&hBufferDesc, sizeof(hBufferDesc));
    hBufferDesc.ByteWidth = sizeof(UINT) * IndexNum;
    hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    hBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    hBufferDesc.CPUAccessFlags = 0;
    //hBufferDesc.MiscFlags = 0;
    //hBufferDesc.StructureByteStride = sizeof(UINT);

    D3D11_SUBRESOURCE_DATA hSubResourceData;
    ZeroMemory(&hSubResourceData, sizeof(hSubResourceData));
    hSubResourceData.pSysMem = Index;
    //hSubResourceData.SysMemPitch = 0;
    //hSubResourceData.SysMemSlicePitch = 0;

    ID3D11Buffer* hpBuffer;
    if (FAILED(m_pDevice->CreateBuffer(&hBufferDesc, &hSubResourceData, &hpBuffer)))
    {
      return nullptr;
    }
    return hpBuffer;
  }
  ID3D11Texture2D* CreateTexture2D(UINT Width, UINT Height, DXGI_FORMAT Format, UINT BindFlag, D3D11_USAGE Usage = D3D11_USAGE_DEFAULT)
  {
    ID3D11Texture2D* texture = nullptr;
    D3D11_TEXTURE2D_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Width = Width;
    desc.Height = Height;
    desc.MipLevels = 1;
    desc.Format = Format;
    desc.Usage = Usage;
    desc.BindFlags = BindFlag;
    desc.ArraySize = 1;
    desc.SampleDesc.Count = 1;
    HRESULT hr = m_pDevice->CreateTexture2D(&desc, nullptr, &texture);
    if (FAILED(hr))
      return nullptr;
    return texture;
  }

  ID3D11ShaderResourceView* CreateTextureFromFile(const wchar_t* filename);
  ID3D11ShaderResourceView* CreateTextureFromFile(const std::string filename);
  ID3D11ShaderResourceView* CreateTextureFromFile(const char* filename);

  //PipelineSetting
  void SetInputLayout(ID3D11InputLayout* VertexLayout);
  void SetVertexShader(ID3D11VertexShader* vs);
  void SetPixelShader(ID3D11PixelShader* ps);

  void SetVertexBuffer(ID3D11Buffer* VertexBuffer, UINT VertexSize);
  void SetIndexBuffer(ID3D11Buffer* IndexBuffer);

  void SetTexture2D(UINT RegisterNo, ID3D11ShaderResourceView* Texture);

  void DrawBegin();
  void DrawEnd();
  void Draw(UINT VertexNum);
  void DrawIndexed(UINT VertexNum); 
};


extern DirectX11Manager g_DX11Manager;

struct DX11Effect
{
  VertexShader vs;
  PixelShader ps;
};

DX11Effect* CreateShader(const string& filename);

class DX11Texture
{
public:
  DX11Texture();
  void DX11TextureLoad(string filename);
  void DX11BlkTextureLoad(string filename, int blkW, int blkH, int blkNum);
  void DX11TextureLoad(const char* filename);
  void DX11BlkTextureLoad(const char* filename, int blkW, int blkH, int blkNum);

  DX11Texture& operator[](int i) { 
    index = i; 
    return *this;
  }

  ID3D11ShaderResourceView* Get() { return tex.Get(); }

  ShaderTexture tex;
  TexMetadata MetaData;
  int index;
  int blkW;
  int blkH;
  int blkNum;
private:
  void LoadTextureMetaData(const wchar_t* filename, TexMetadata& metadata);

};

void setPremulpryFlag(bool flag);