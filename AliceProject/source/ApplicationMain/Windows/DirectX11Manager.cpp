#include "DirectX11Manager.h"

DirectX11Manager g_DX11Manager;
extern bool g_PMAFlag;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
  {
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  case WM_KEYDOWN:
    if (wParam == VK_ESCAPE)
    {
      if (MessageBox(hWnd, "終了", "終了しますか？", MB_OKCANCEL) == IDOK)
        PostQuitMessage(0);
    }
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }

  return 0;
}

HRESULT DirectX11Manager::Init(HINSTANCE hInstance, int cCmdShow)
{
  WNDCLASSEX wcex = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, hInstance, NULL, NULL, NULL, NULL, "AliceGame", NULL };
  if (!RegisterClassEx(&wcex))
  {
    return E_FAIL;
  }

  RECT rc = { 0, 0, 1280, 720 };

  hWnd = CreateWindow(wcex.lpszClassName, "AliceGame", WS_DLGFRAME,
    CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top,
    NULL, NULL, hInstance, NULL);
  if (!hWnd)
  {
    return E_FAIL;
  }

  RECT wRect, cRect;  // ウィンドウ全体の矩形、クライアント領域の矩形
  int ww, wh;         // ウィンドウ全体の幅、高さ
  int cw, ch;         // クライアント領域の幅、高さ

  // ウィンドウ全体の幅・高さを計算
  GetWindowRect(hWnd, &wRect);
  ww = wRect.right - wRect.left;
  wh = wRect.bottom - wRect.top;
  // クライアント領域の幅・高さを計算
  GetClientRect(hWnd, &cRect);
  cw = cRect.right - cRect.left;
  ch = cRect.bottom - cRect.top;
  // クライアント領域以外に必要なサイズを計算
  ww = ww - cw;
  wh = wh - ch;
  // ウィンドウ全体に必要なサイズを計算
  ww = 1280 + ww;
  wh = 720 + wh;

  // 計算した幅と高さをウィンドウに設定
  SetWindowPos(hWnd, HWND_TOP, 0, 0, ww, wh, SWP_NOMOVE);

  ShowWindow(hWnd, SW_SHOW);
  UpdateWindow(hWnd);							// ウィンドウの表示
  SetFocus(hWnd);								// フォーカスのセット

#pragma region HardWare Check
  IDXGIFactory* factory;
  IDXGIAdapter* adapter;
  IDXGIOutput* adapterOutput;
  unsigned int numModes = 0;
  size_t stringLength;
  DXGI_ADAPTER_DESC adapterDesc;

  //グラフィック インタフェース ファクトリを作成
  auto hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)& factory);
  if (FAILED(hr))
  {
    return hr;
  }

  int GPUNumber = 0;
  int GPUMaxMem = 0;
  //一番強いGPUアダプタを検索
  for (int i = 0; i < 100; i++)
  {
    IDXGIAdapter* add;
    hr = factory->EnumAdapters(i, &add);
    if (FAILED(hr))
      break;
    hr = add->GetDesc(&adapterDesc);

    char videoCardDescription[128];
    //ビデオカード名を取得
    int error = wcstombs_s(&stringLength, videoCardDescription, 128, adapterDesc.Description, 128);
    if (error != 0)
    {
      break;
    }
    cout << "ビデオカード名 : " << videoCardDescription << endl;

    //ビデオカードメモリを取得（MB単位）
    int videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);
    cout << "ビデオメモリー : " << videoCardMemory << endl;

    //アウトプット（モニター）に番号IDを付ける
    hr = add->EnumOutputs(0, &adapterOutput);
    if (FAILED(hr))
    {
      continue;
    }

    //DXGI_FORMAT_R8G8B8A8_UNORM の表示形式数を取得する
    hr = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
    if (FAILED(hr))
    {
      continue;
    }
    cout << "RBGA8_UNORM Count : " << numModes << endl;

    if (videoCardMemory > GPUMaxMem)
    {
      GPUMaxMem = videoCardMemory;
      GPUNumber = i;
    }
    add->Release();
    //アダプタアウトプットを解放
    adapterOutput->Release();
    adapterOutput = 0;
  }

  //グラフィック インタフェース アダプターを作成
  hr = factory->EnumAdapters(GPUNumber, &adapter);
  if (FAILED(hr))
  {
    return hr;
  }
#pragma endregion

#pragma region DirectX11Init
  UINT cdev_flags = 0;
#ifdef _DEBUG
  cdev_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
  // スワップチェイン設定
  DXGI_SWAP_CHAIN_DESC sd;
  ZeroMemory(&sd, sizeof(sd));
  sd.BufferCount = 1;
  sd.BufferDesc.Width = rc.right;
  sd.BufferDesc.Height = rc.bottom;
  sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  sd.BufferDesc.RefreshRate.Numerator = 1000;
  sd.BufferDesc.RefreshRate.Denominator = 1;	//1/60 = 60fps
  sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  sd.OutputWindow = hWnd;
  sd.SampleDesc.Count = 1;
  sd.SampleDesc.Quality = 0;
  sd.Windowed = true;
  sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

  D3D_FEATURE_LEVEL featureLevels[] =
  {
    D3D_FEATURE_LEVEL_11_1,
  };

  // DirectX11デバイスとスワップチェイン作成
  hr = D3D11CreateDeviceAndSwapChain(adapter, D3D_DRIVER_TYPE_UNKNOWN, NULL,
    cdev_flags, featureLevels, 1, D3D11_SDK_VERSION, &sd,
    &m_pSwapChain, &m_pDevice, NULL, &m_pImContext);
  if (FAILED(hr))
  {
    return hr;
  }

  //アダプタを解放
  adapter->Release();
  adapter = 0;

  //ファクトリを解放
  factory->Release();
  factory = 0;

  //ステンシル用テクスチャーの設定（深層バッファ）
  D3D11_TEXTURE2D_DESC hTexture2dDesc;
  hTexture2dDesc.Width = sd.BufferDesc.Width;
  hTexture2dDesc.Height = sd.BufferDesc.Height;
  hTexture2dDesc.MipLevels = 1;
  hTexture2dDesc.ArraySize = 1;
  hTexture2dDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
  hTexture2dDesc.SampleDesc = sd.SampleDesc;
  hTexture2dDesc.Usage = D3D11_USAGE_DEFAULT;
  hTexture2dDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
  hTexture2dDesc.CPUAccessFlags = 0;
  hTexture2dDesc.MiscFlags = 0;
  //ステンシル用テクスチャの作成（深層バッファ）
  hr = m_pDevice->CreateTexture2D(&hTexture2dDesc, NULL, &m_pTexture2DDepth);
  if (FAILED(hr))
  {
    return hr;
  }

  D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
  //ステンシルステートの初期化（３Ｄ用）
  ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

  //ステンシルステート設定
  depthStencilDesc.DepthEnable = true;
  depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
  depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

  depthStencilDesc.StencilEnable = true;
  depthStencilDesc.StencilReadMask = 0xFF;
  depthStencilDesc.StencilWriteMask = 0xFF;

  depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
  depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
  depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
  depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

  depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
  depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
  depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
  depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

  //ステンシルステート作成
  hr = m_pDevice->CreateDepthStencilState(&depthStencilDesc, &m_pDepthStencilState);
  if (FAILED(hr))
  {
    return hr;
  }

  //ステンシルターゲット作成
  D3D11_DEPTH_STENCIL_VIEW_DESC hDepthStencilViewDesc;
  hDepthStencilViewDesc.Format = hTexture2dDesc.Format;
  hDepthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
  hDepthStencilViewDesc.Flags = 0;
  hr = m_pDevice->CreateDepthStencilView(m_pTexture2DDepth.Get(), &hDepthStencilViewDesc, &m_pDepthStencilView);
  if (FAILED(hr))
  {
    return hr;
  }

  // スワップチェインに用意されたバッファ（2Dテクスチャ）を取得
  hr = m_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&m_pRTTex));
  if (FAILED(hr))
  {
    return hr;
  }

  // レンダーターゲットView作成
  hr = m_pDevice->CreateRenderTargetView(m_pRTTex.Get(), NULL, &m_pRTView);
  if (FAILED(hr))
  {
    return hr;
  }

  // viewport
  m_Viewport.Width = static_cast<FLOAT>(rc.right - rc.left);
  m_Viewport.Height = static_cast<FLOAT>(rc.bottom - rc.top);
  m_Viewport.MinDepth = 0.0f;
  m_Viewport.MaxDepth = 1.0f;
  m_Viewport.TopLeftX = 0;
  m_Viewport.TopLeftY = 0;

  //ラスタライザ設定
  D3D11_RASTERIZER_DESC hRasterizerDesc = {
    D3D11_FILL_SOLID,
    D3D11_CULL_NONE,	//ポリゴンの裏表を無くす
    FALSE,
    0,
    0.0f,
    FALSE,
    FALSE,
    FALSE,
    FALSE,
    FALSE
  };
  hr = m_pDevice->CreateRasterizerState(&hRasterizerDesc, &m_pRasterizerState);
  if (FAILED(hr))
  {
    return hr;
  }

  // サンプラー作成
  D3D11_SAMPLER_DESC sampDesc;
  ZeroMemory(&sampDesc, sizeof(sampDesc));
  sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
  sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
  sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
  sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
  sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
  sampDesc.MinLOD = FLT_MIN;
  sampDesc.MaxLOD = FLT_MAX;
  hr = m_pDevice->CreateSamplerState(&sampDesc, &m_pSampler);
  if (FAILED(hr))
  {
    return hr;
  }
#pragma endregion

  return hr;
}

ID3D11VertexShader* DirectX11Manager::CreateVertexShader(const string & filename, const string & entrypath, bool erorr)
{
  ID3D11VertexShader* Shader;

#if defined(_DEBUG)
  // グラフィックデバッグツールによるシェーダーのデバッグを有効にする
  UINT	compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
  UINT	compileFlags = 0;
#endif
  ComPtr<ID3DBlob> blob;
  wchar_t ws[512];

  setlocale(LC_CTYPE, "jpn");
  mbstowcs(ws, filename.c_str(), 512);
  ComPtr<ID3DBlob> pErrorBlob = NULL;
  HRESULT hr = D3DCompileFromFile(ws, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entrypath.c_str(), "vs_5_0", compileFlags, 0, &blob, &pErrorBlob);

  // エラーチェック.
  if (FAILED(hr))
  {
    if (erorr)
    {
      // エラーメッセージを出力.
      if (pErrorBlob != NULL)
      {
        MessageBox(NULL, (char*)pErrorBlob->GetBufferPointer(), "", 0);
        return nullptr;
      }
    }
    else
    {
      string er = (char*)pErrorBlob->GetBufferPointer();
      if (er.find("entrypoint not found") == string::npos)
        MessageBox(NULL, (char*)pErrorBlob->GetBufferPointer(), "", 0);;
      cout << filename << "(" << entrypath << ") is notfound" << endl;
      return nullptr;
    }
  }

  hr = m_pDevice->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), NULL, &Shader);
  assert(SUCCEEDED(hr));

  return Shader;
}

ID3D11PixelShader* DirectX11Manager::CreatePixelShader(const string & filename, const string & entrypath, bool erorr)
{
  ID3D11PixelShader* Shader;

#if defined(_DEBUG)
  // グラフィックデバッグツールによるシェーダーのデバッグを有効にする
  UINT	compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
  UINT	compileFlags = 0;
#endif
  ComPtr<ID3DBlob> blob;
  wchar_t ws[512];

  setlocale(LC_CTYPE, "jpn");
  mbstowcs(ws, filename.c_str(), 512);
  ComPtr<ID3DBlob> pErrorBlob = NULL;
  HRESULT hr = D3DCompileFromFile(ws, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entrypath.c_str(), "ps_5_0", compileFlags, 0, &blob, &pErrorBlob);
  // エラーチェック.
  if (FAILED(hr))
  {
    if (erorr)
    {
      // エラーメッセージを出力.
      if (pErrorBlob != NULL && erorr)
      {
        MessageBox(NULL, (char*)pErrorBlob->GetBufferPointer(), "", 0);
        return nullptr;
      }
    }
    else
    {
      string er = (char*)pErrorBlob->GetBufferPointer();
      if (er.find("entrypoint not found") == string::npos)
        MessageBox(NULL, (char*)pErrorBlob->GetBufferPointer(), "", 0);;
      cout << filename << "(" << entrypath << ") is notfound" << endl;
      return nullptr;
    }
  }

  hr = m_pDevice->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), NULL, &Shader);
  assert(SUCCEEDED(hr));

  return Shader;
}

ID3D11GeometryShader* DirectX11Manager::CreateGeometryShader(const string & filename, const string & entrypath, bool erorr)
{
  ID3D11GeometryShader* Shader;


#if defined(_DEBUG)
  // グラフィックデバッグツールによるシェーダーのデバッグを有効にする
  UINT	compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
  UINT	compileFlags = 0;
#endif
  ComPtr<ID3DBlob> blob;
  wchar_t ws[512];

  setlocale(LC_CTYPE, "jpn");
  mbstowcs(ws, filename.c_str(), 512);
  ComPtr<ID3DBlob> pErrorBlob = NULL;
  HRESULT hr = D3DCompileFromFile(ws, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entrypath.c_str(), "gs_5_0", compileFlags, 0, &blob, &pErrorBlob);
  // エラーチェック.
  if (FAILED(hr))
  {
    if (erorr)
    {
      // エラーメッセージを出力.
      if (pErrorBlob != NULL)
      {
        MessageBox(NULL, (char*)pErrorBlob->GetBufferPointer(), "", 0);
        return nullptr;
      }
    }
    else
    {
      string er = (char*)pErrorBlob->GetBufferPointer();
      if (er.find("entrypoint not found") == string::npos)
        MessageBox(NULL, (char*)pErrorBlob->GetBufferPointer(), "", 0);;
      cout << filename << "(" << entrypath << ") is notfound" << endl;
      return nullptr;
    }
  }

  hr = m_pDevice->CreateGeometryShader(blob->GetBufferPointer(), blob->GetBufferSize(), NULL, &Shader);
  assert(SUCCEEDED(hr));
  return Shader;
}

ID3D11ComputeShader* DirectX11Manager::CreateComputeShader(const string & filename, const string & entrypath)
{
  ID3D11ComputeShader* Shader;


#if defined(_DEBUG)
  // グラフィックデバッグツールによるシェーダーのデバッグを有効にする
  UINT	compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
  UINT	compileFlags = 0;
#endif
  ComPtr<ID3DBlob> blob;
  wchar_t ws[512];

  setlocale(LC_CTYPE, "jpn");
  mbstowcs(ws, filename.c_str(), 512);
  ComPtr<ID3DBlob> pErrorBlob = NULL;
  HRESULT hr = D3DCompileFromFile(ws, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entrypath.c_str(), "cs_5_0", compileFlags, 0, &blob, &pErrorBlob);
  // エラーチェック.
  if (FAILED(hr))
  {
    string er = (char*)pErrorBlob->GetBufferPointer();
    if (er.find("entrypoint not found") == string::npos)
      MessageBox(NULL, (char*)pErrorBlob->GetBufferPointer(), "", 0);;
    cout << filename << "(" << entrypath << ") is notfound" << endl;
    return nullptr;
  }

  hr = m_pDevice->CreateComputeShader(blob->GetBufferPointer(), blob->GetBufferSize(), NULL, &Shader);
  assert(SUCCEEDED(hr));
  return Shader;
}

ID3D11InputLayout* DirectX11Manager::CreateInputLayout(D3D11_INPUT_ELEMENT_DESC * layout, UINT elem_num, const string & filename, const string & entrypath)
{
  ID3D11InputLayout* pVertexLayout;

#if defined(_DEBUG)
  // グラフィックデバッグツールによるシェーダーのデバッグを有効にする
  UINT	compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
  UINT	compileFlags = 0;
#endif
  ComPtr<ID3DBlob> blob;
  wchar_t ws[512];

  setlocale(LC_CTYPE, "jpn");
  mbstowcs(ws, filename.c_str(), 512);
  ComPtr<ID3DBlob> pErrorBlob = NULL;
  HRESULT hr = D3DCompileFromFile(ws, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entrypath.c_str(), "vs_5_0", compileFlags, 0, &blob, &pErrorBlob);
  // エラーチェック.
  if (FAILED(hr))
  {
    // エラーメッセージを出力.
    if (pErrorBlob != NULL)
    {
      MessageBox(NULL, (char*)pErrorBlob->GetBufferPointer(), "", 0);
    }
  }
  hr = m_pDevice->CreateInputLayout(layout, elem_num, blob->GetBufferPointer(),
    blob->GetBufferSize(), &pVertexLayout);
  assert(SUCCEEDED(hr));

  return pVertexLayout;
}

//コンスタントバッファを作成
bool DirectX11Manager::CreateConstantBuffer(unsigned int bytesize, ID3D11Buffer * *CBuffer)
{
  // コンスタントバッファ生成
  D3D11_BUFFER_DESC bd;

  ZeroMemory(&bd, sizeof(bd));
  bd.Usage = D3D11_USAGE_DEFAULT;
  bd.ByteWidth = bytesize;
  bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  bd.CPUAccessFlags = 0;
  HRESULT hr = m_pDevice->CreateBuffer(&bd, nullptr, CBuffer);
  if (FAILED(hr))
  {
    MessageBox(nullptr, "CreateBuffer(constant buffer) error", "Error", MB_OK);
    return false;
  }

  return true;
}

void ConvertPMAImage(ScratchImage &Out,const ScratchImage &image)
{
  TransformImage(image.GetImages(), image.GetImageCount(), image.GetMetadata(),
    [](XMVECTOR* outPixels, const XMVECTOR* inPixels, size_t width, size_t y)
  {
    static const XMVECTORF32 s_chromaKey = { 0.f, 1.f, 0.f, 0.f };
    static const XMVECTORF32 s_tolerance = { 0.2f, 0.2f, 0.2f, 0.f };

    UNREFERENCED_PARAMETER(y);

    for (size_t j = 0; j < width; ++j)
    {
      XMVECTOR value = inPixels[j];

      if (XMVector3NearEqual(value, s_chromaKey, s_tolerance))
      {
        value = g_XMZero;
      }
      else
      {
        value = XMVectorSelect(g_XMOne, value, g_XMSelect1110);
      }
      outPixels[j] = value;
    }
  }, Out);
}

ID3D11ShaderResourceView* DirectX11Manager::CreateTextureFromFile(const wchar_t* filename)
{
  ID3D11ShaderResourceView* ShaderResView;

  char ms[100];
  setlocale(LC_CTYPE, "jpn");
  wcstombs(ms, filename, 100);
  char* 拡張子 = strstr(ms, ".");

  if (拡張子 == NULL)
    return nullptr;

  if (strcmp(拡張子, ".tga") == 0 || strcmp(拡張子, ".TGA") == 0)
  {
    TexMetadata meta;
    GetMetadataFromTGAFile(filename, meta);

    std::unique_ptr<ScratchImage> image(new ScratchImage);
    HRESULT hr = LoadFromTGAFile(filename, &meta, *image);
    if (FAILED(hr))
      return nullptr;
    hr = CreateShaderResourceView(m_pDevice.Get(), image->GetImages(), image->GetImageCount(), meta, &ShaderResView);
    if (FAILED(hr))
      return nullptr;
    return ShaderResView;
  }
  else
  {
    TexMetadata meta;
    GetMetadataFromWICFile(filename, 0, meta);
    ScratchImage destImage;
    std::unique_ptr<ScratchImage> image(new ScratchImage);
    HRESULT hr = LoadFromWICFile(filename, 0, &meta, *image);
    ScratchImage result;
    if (FAILED(hr))
      return nullptr;
    if (g_PMAFlag == true)
    {
      ConvertPMAImage(result, *image);
      hr = CreateShaderResourceView(m_pDevice.Get(), result.GetImages(), result.GetImageCount(), meta, &ShaderResView);
      if (FAILED(hr))
        return nullptr;
    }
    else
    {
      hr = CreateShaderResourceView(m_pDevice.Get(), image->GetImages(), image->GetImageCount(), meta, &ShaderResView);
      if (FAILED(hr))
        return nullptr;
    }
    if (FAILED(hr))
      return nullptr;
    return ShaderResView;
  }
}
ID3D11ShaderResourceView* DirectX11Manager::CreateTextureFromFile(const std::string filename)
{
  if (filename.empty())
    return nullptr;
  return CreateTextureFromFile(filename.c_str());
}
ID3D11ShaderResourceView* DirectX11Manager::CreateTextureFromFile(const char* filename)
{
  wchar_t ws[512];

  setlocale(LC_CTYPE, "jpn");
  mbstowcs(ws, filename, 512);
  return CreateTextureFromFile(ws);
}

void DirectX11Manager::SetInputLayout(ID3D11InputLayout* VertexLayout)
{
  m_pImContext->IASetInputLayout(VertexLayout);
}
void DirectX11Manager::SetVertexShader(ID3D11VertexShader* vs)
{
  m_pImContext->VSSetShader(vs, nullptr, 0);
}
void DirectX11Manager::SetPixelShader(ID3D11PixelShader* ps)
{
  m_pImContext->PSSetShader(ps, nullptr, 0);
}
void DirectX11Manager::SetVertexBuffer(ID3D11Buffer* VertexBuffer, UINT VertexSize)
{
  UINT hOffsets = 0;
  m_pImContext->IASetVertexBuffers(0, 1, &VertexBuffer, &VertexSize, &hOffsets);
}
void DirectX11Manager::SetIndexBuffer(ID3D11Buffer* IndexBuffer)
{
  m_pImContext->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
}

void DirectX11Manager::SetTexture2D(UINT RegisterNo, ID3D11ShaderResourceView* Texture)
{
  m_pImContext->PSSetShaderResources(RegisterNo, 1, &Texture);
}

void DirectX11Manager::DrawBegin()
{
  //ポリゴンの生成方法の指定
  m_pImContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

  // 指定色で画面クリア
  float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //red,green,blue,alpha
  m_pImContext->ClearRenderTargetView(m_pRTView.Get(), ClearColor);
  float Cloar[4] = { 0,0,0,1 };
  m_pImContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

  m_pImContext->RSSetViewports(1, &m_Viewport);
  //ラスタライザーをコンテキストに設定
  m_pImContext->RSSetState(m_pRasterizerState.Get());
  //デバイスコンテキストにセットする
  m_pImContext->OMSetDepthStencilState(m_pDepthStencilState.Get(), 1);

  //サンプラーをセット
  ID3D11SamplerState* sampler = m_pSampler.Get();
  m_pImContext->PSSetSamplers(0, 1, &sampler);

  //RenderTargetをバックバッファ
  ID3D11RenderTargetView* rtv[1] = { m_pRTView.Get() };
  m_pImContext->OMSetRenderTargets(1, rtv, m_pDepthStencilView.Get());
}

void DirectX11Manager::DrawEnd()
{
  m_pSwapChain->Present(1, 0);
}

void DirectX11Manager::Draw(UINT VertexNum)
{
  m_pImContext->Draw(VertexNum, 0);
}
void DirectX11Manager::DrawIndexed(UINT VertexNum)
{
  m_pImContext->DrawIndexed(VertexNum, 0, 0);
}

DX11Effect* CreateShader(const string & filename)
{
  DX11Effect* ret = new DX11Effect();
  ret->vs.Attach(g_DX11Manager.CreateVertexShader(filename, "vsMain"));
  ret->ps.Attach(g_DX11Manager.CreatePixelShader(filename, "psMain"));
  return ret;
}

void setPremulpryFlag(bool flag)
{
  g_PMAFlag = flag;
}
static bool g_PMAFlag;

DX11Texture::DX11Texture()
{
}

void DX11Texture::DX11TextureLoad(string filename)
{
  if (filename.empty())
    return;
  return DX11TextureLoad(filename.c_str());
}

void DX11Texture::DX11BlkTextureLoad(string filename, int blkW, int blkH, int blkNum)
{
  if (filename.empty())
    return;
  return DX11TextureLoad(filename.c_str());
}

void DX11Texture::DX11TextureLoad(const char * filename)
{
  wchar_t ws[512];

  setlocale(LC_CTYPE, "jpn");
  mbstowcs(ws, filename, 512);
  LoadTextureMetaData(ws, MetaData);

  blkW = MetaData.width;
  blkH = MetaData.height;
  blkNum = 1;
  index = 0;

  tex.Attach(g_DX11Manager.CreateTextureFromFile(filename));
}

void DX11Texture::DX11BlkTextureLoad(const char * filename, int blkW, int blkH, int blkNum)
{
  wchar_t ws[512];

  setlocale(LC_CTYPE, "jpn");
  mbstowcs(ws, filename, 512);
  LoadTextureMetaData(ws, MetaData);

  this->blkW = blkW;
  this->blkH = blkH;
  int num = (MetaData.width / blkW) * (MetaData.height / blkH);
  if (num > blkNum)
  {
    this->blkNum = blkNum;
  }
  else
  {
    this->blkNum = num;
  }
  index = 0;

  tex.Attach(g_DX11Manager.CreateTextureFromFile(filename));
}

void DX11Texture::LoadTextureMetaData(const wchar_t* filename, TexMetadata& metadata)
{
  char ms[100];
  setlocale(LC_CTYPE, "jpn");
  wcstombs(ms, filename, 100);
  char* 拡張子 = strstr(ms, ".");

  if (拡張子 == NULL)
    return;

  if (strcmp(拡張子, ".tga") == 0 || strcmp(拡張子, ".TGA") == 0)
  {  
    GetMetadataFromTGAFile(filename, metadata);
  }
  else
  {
    GetMetadataFromWICFile(filename, 0, metadata);
  }
  return;
}

