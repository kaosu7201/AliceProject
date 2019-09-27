#pragma once

//WindowsApplicationを使用するので必須
#include <windows.h>

#include <string>
#include <iostream>
using namespace std;
//DirectX11のAPIが入っている
#include <d3d11.h>
//シェーダーのコンパイラ
#include <d3dcompiler.h>
//ベクトルやFLOAT3など便利な算術ライブラリ
#include <DirectXMath.h>
//デバイスの管理をしやすくするためのDirectX版のスマートポインタのようなもの
#include <wrl/client.h>

//DirectXAPI関係のリンク
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

//DirectXMathがDirectXのネームスペースにある
using namespace DirectX;
//ComPtr(DirectX版のスマートポインタ)
using Microsoft::WRL::ComPtr;

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
  //Windowsのハンドル
  HWND hWnd = NULL;
public:
  //DX11のデバイス
  ComPtr<ID3D11Device>            m_pDevice = nullptr;
  //DX11の描画命令等を送るためのもの
  ComPtr<ID3D11DeviceContext>     m_pImContext = nullptr;
  //ハードウェアの情報が詰まっているもの
  ComPtr<IDXGISwapChain>          m_pSwapChain = nullptr;
  //ディスプレイのバッグバッファのテクスチャ
  Texture2D                       m_pRTTex = nullptr;
  //ディスプレイのバッグバッファのテクスチャを描画先として指定できるようにしたもの
  ComPtr<ID3D11RenderTargetView>  m_pRTView = nullptr;
  //ウィンドウのサイズの指定
  D3D11_VIEWPORT                  m_Viewport = { 0,0,0,0,0,0 };

  //初期化関数
  HRESULT Init(HINSTANCE hInstance, int cCmdShow);

  ID3D11VertexShader* CreateVertexShader(const string& filename, const string& entrypath = "", bool erorr = true);
  ID3D11PixelShader* CreatePixelShader(const string& filename, const string& entrypath = "", bool erorr = true);

  //inputlayout作成
  ID3D11InputLayout* CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* layout, UINT elem_num, const string& filename, const string& entrypath = "");


  void DrawBegin();
  void DrawEnd();
};

