#include "PlWindows.h"
#include "DirectX/Font/DXFont.h"
#include "DirectX/DirectX11Manager.h"

DirectX11Manager PlWindows::DXManager;
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

void PlWindows::DrawFbxMesh(AlFbxMesh *mesh)
{

}