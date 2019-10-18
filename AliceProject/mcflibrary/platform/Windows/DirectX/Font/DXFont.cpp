#include "DXFont.h"
#include <tchar.h>
#include "../Sprite/DXSprite.h"

map<string, DX11Texture> DXFont::FontTex;
HDC DXFont::hdc;
int DXFont::fontX;
int DXFont::fontY;

void DXFont::init()
{
  // �t�H���g�n���h���̐���
  int fontSize = 32;
  int fontWeight = 1000;
  LOGFONT lf =
  {
    fontSize, 0, 0, 0, 0, 0, 0, 0,
    SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS,
    PROOF_QUALITY, FIXED_PITCH | FF_MODERN,
    _T("�l�r P����")
  };
  HFONT hFont = CreateFontIndirect(&lf);

  // ���݂̃E�B���h�E�ɓK�p
  // �f�o�C�X�Ƀt�H���g���������Ȃ���GetGlyphOutline�֐��̓G���[�ƂȂ�
  hdc = GetDC(NULL);
  HFONT oldFont = (HFONT)SelectObject(hdc, hFont);
}

ID3D11ShaderResourceView* DXFont::GetFontTexture(const char *c)
{
  if (FontTex[c].Get()) return FontTex[c].Get();

  FontTex[c].Set(CreateFontTexture(c));
  return FontTex[c].Get();
}

ID3D11ShaderResourceView* DXFont::CreateFontTexture(const char *c)
{
  ID3D11ShaderResourceView* ShaderResView;
  ID3D11Texture2D *fontTexture;
  UINT code = 0;
#if _UNICODE
  // unicode�̏ꍇ�A�����R�[�h�͒P���Ƀ��C�h������UINT�ϊ��ł�
  code = (UINT)*c;
#else
  // �}���`�o�C�g�����̏ꍇ�A
  // 1�o�C�g�����̃R�[�h��1�o�C�g�ڂ�UINT�ϊ��A
  // 2�o�C�g�����̃R�[�h��[�擱�R�[�h]*256 + [�����R�[�h]�ł�
  if (IsDBCSLeadByte(*c))
    code = (BYTE)c[0] << 8 | (BYTE)c[1];
  else
    code = c[0];
#endif
  const int gradFlag = GGO_GRAY4_BITMAP;
  // �K���̍ő�l
  int grad = 0;
  switch (gradFlag)
  {
  case GGO_GRAY2_BITMAP:
    grad = 4;
    break;
  case GGO_GRAY4_BITMAP:
    grad = 16;
    break;
  case GGO_GRAY8_BITMAP:
    grad = 64;
    break;
  }

  TEXTMETRIC tm;
  GetTextMetrics(hdc, &tm);
  GLYPHMETRICS gm;
  CONST MAT2 mat = { {0,1},{0,0},{0,0},{0,1} };
  DWORD size = GetGlyphOutline(hdc, code, gradFlag, &gm, 0, NULL, &mat);
  BYTE *pMono = new BYTE[size];
  GetGlyphOutline(hdc, code, gradFlag, &gm, size, pMono, &mat);

  //�t�H���g�̕��ƍ���
  int fontWidth = gm.gmCellIncX;
  int fontHeight = tm.tmHeight;
  fontTexture = PlWindows::DXManager.CreateTexture2D(fontWidth, fontHeight, DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE, D3D11_USAGE_DYNAMIC);
  FontTex[c].blkW = fontWidth;
  FontTex[c].blkH = fontHeight;
  FontTex[c].index = 0;
  FontTex[c].blkNum = 1;
  auto deviceContext = PlWindows::DXManager.m_pImContext;
  // �t�H���g�����e�N�X�`���ɏ������ޕ���
  D3D11_MAPPED_SUBRESOURCE hMappedResource;
  deviceContext->Map(
    fontTexture,
    0,
    D3D11_MAP_WRITE_DISCARD,
    0,
    &hMappedResource);
  // �����ŏ�������
  BYTE* pBits = (BYTE*)hMappedResource.pData;
  // �t�H���g���̏�������
  // iOfs_x, iOfs_y : �����o���ʒu(����)
  // iBmp_w, iBmp_h : �t�H���g�r�b�g�}�b�v�̕���
  // Level : ���l�̒i�K (GGO_GRAY4_BITMAP�Ȃ̂�17�i�K)
  int iOfs_x = gm.gmptGlyphOrigin.x;
  int iOfs_y = tm.tmAscent - gm.gmptGlyphOrigin.y;
  int iBmp_w = gm.gmBlackBoxX + (4 - (gm.gmBlackBoxX % 4)) % 4;
  int iBmp_h = gm.gmBlackBoxY;
  int Level = 17;
  int x, y;
  DWORD Alpha, Color;
  memset(pBits, 0, hMappedResource.RowPitch * tm.tmHeight);
  for (y = iOfs_y; y < iOfs_y + iBmp_h; y++)
  {
    for (x = iOfs_x; x < iOfs_x + iBmp_w; x++)
    {
      Alpha =
        (255 * pMono[x - iOfs_x + iBmp_w * (y - iOfs_y)])
        / (Level - 1);
      Color = 0x00ffffff | (Alpha << 24);
      memcpy(
        (BYTE*)pBits
        + hMappedResource.RowPitch * y + 4 * x,
        &Color,
        sizeof(DWORD));
    }
  }
  deviceContext->Unmap(fontTexture, 0);
  //�s�v�Ȃ̂ō폜
  delete[] pMono;
  
  D3D11_TEXTURE2D_DESC fontTextureDesc;
  fontTexture->GetDesc(&fontTextureDesc);
  // ShaderResourceView�̏����쐬����
  D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
  ZeroMemory(&srvDesc, sizeof(srvDesc));
  srvDesc.Format = fontTextureDesc.Format;
  srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
  srvDesc.Texture2D.MostDetailedMip = 0;
  srvDesc.Texture2D.MipLevels = fontTextureDesc.MipLevels;

  PlWindows::DXManager.m_pDevice->CreateShaderResourceView(fontTexture, &srvDesc, &ShaderResView);
  return ShaderResView;
}

void DXFont::DrawFont(const char *c, int x, int y)
{
  auto texture = GetFontTexture(c);
  if (!texture) return;

  DXSprite sp(1280,720);
  sp.setTexture(&FontTex[c], true);
  sp.setPos(x + fontX, y + fontY);
  SetDrawBlendMode(BLENDMODE_ALPHA, 255);
  sp.draw(false);
  DXSprite::drawAll();
  DXSprite::clearDrawList();
  fontX += FontTex[c].blkW;
}

void PlWindows::DrawPrintf(int x, int y, string str)
{
  DXFont::SetfontXY(0, 0);
  while (!str.empty())
  {
    string c;
    if (IsDBCSLeadByte(str[0]) == 0)
    {
      c = str.substr(0, 1);
      str.erase(0, 1);
    }
    else
    {
      c = str.substr(0, 2);
      str.erase(0, 2);
    }
    DXFont::DrawFont(c.c_str(), x, y);
  }
    
}