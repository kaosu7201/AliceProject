#include "../../PlWindows.h"


// DrawBlendMode
int g_pal;
void BlendNoBlend();
void BlendAlpha();

void BlendPmaAlpha();
void SetDrawBlendMode(int BlendMode, int pal)
{
  if (BlendMode == 0)
  {
    PlWindows::DXManager.m_pImContext->OMSetRenderTargets(
      1,                                    // ターゲット
      PlWindows::DXManager.m_pRTView.GetAddressOf(),    // ビュー
      NULL            // 深度バッファなし
    );
  }
  else
  {
    PlWindows::DXManager.m_pImContext->OMSetRenderTargets(
      1,                                    // ターゲット
      PlWindows::DXManager.m_pRTView.GetAddressOf(),    // ビュー
      PlWindows::DXManager.m_pDepthStencilView.Get()           // 深度バッファなし
    );  
  }
  g_pal = pal;
  switch (BlendMode)
  {
  case BLENDMODE_NOBLEND:
    BlendNoBlend();
    break;
  case BLENDMODE_ALPHA:
    BlendAlpha();
    break;
  case BLENDMODE_ADD:
    break;
  case BLENDMODE_SUB:
    break;
  case BLENDMODE_MULA:
    break;
  case BLENDMODE_INVSRC:
    break;
  case BLENDMODE_PMA_ALPHA:
    BlendPmaAlpha();
    break;
  case BLENDMODE_PMA_ADD:
    break;
  case BLENDMODE_PMA_SUB:
    break;
  case BLENDMODE_PMA_INVSRC:
    break;
  default:
    break;
  }
}

static void BlendNoBlend()
{
  ID3D11BlendState* pBlendState = NULL;
  D3D11_BLEND_DESC BlendDesc;
  ZeroMemory(&BlendDesc, sizeof(BlendDesc));
  BlendDesc.AlphaToCoverageEnable = FALSE;
  BlendDesc.IndependentBlendEnable = FALSE;
  BlendDesc.RenderTarget[0].BlendEnable = FALSE;
  BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
  BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_DEST_COLOR;
  BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
  BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
  BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
  BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
  BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

  float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
  PlWindows::DXManager.m_pDevice->CreateBlendState(&BlendDesc, &pBlendState);
  PlWindows::DXManager.m_pImContext->OMSetBlendState(pBlendState, blendFactor, 0xffffffff);
}

static void BlendAlpha()
{
  ID3D11BlendState* pBlendState = NULL;
  D3D11_BLEND_DESC BlendDesc;
  ZeroMemory(&BlendDesc, sizeof(BlendDesc));
  BlendDesc.AlphaToCoverageEnable = FALSE;
  BlendDesc.IndependentBlendEnable = FALSE;
  BlendDesc.RenderTarget[0].BlendEnable = TRUE;
  BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
  BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
  BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
  BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
  BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
  BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
  BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
  float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
  PlWindows::DXManager.m_pDevice->CreateBlendState(&BlendDesc, &pBlendState);
  PlWindows::DXManager.m_pImContext->OMSetBlendState(pBlendState, blendFactor, 0xffffffff);
}

static void BlendPmaAlpha()
{
  ID3D11BlendState* pBlendState = NULL;
  D3D11_BLEND_DESC BlendDesc;
  ZeroMemory(&BlendDesc, sizeof(BlendDesc));
  BlendDesc.AlphaToCoverageEnable = FALSE;
  BlendDesc.IndependentBlendEnable = FALSE;
  BlendDesc.RenderTarget[0].BlendEnable = TRUE;
  BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
  BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
  BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
  BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
  BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
  BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
  BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
  float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
  PlWindows::DXManager.m_pDevice->CreateBlendState(&BlendDesc, &pBlendState);
  PlWindows::DXManager.m_pImContext->OMSetBlendState(pBlendState, blendFactor, 0xffffffff);
}