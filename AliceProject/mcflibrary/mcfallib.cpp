#include "mcfallib.h"
#include <cstdarg>

void DrawPrintf(int x, int y, AlColor4 color, char* str, ...)
{
  char sz[0xffff];		// �z�񐔂�[0xffff]�Ȃ̂́A���ꂭ�炢����Α���邾�낤�I�T�C�Y�B������ꂽ���肪�o��B
  va_list list;
  va_start(list, str);
  vsprintf(sz, str, list);
  va_end(list);

  Platform::GetInstance()->DrawPrintf(x, y, color, sz);
}

int TextureLoad(string filename)
{
  return Platform::GetInstance()->TextureLoad(filename);
}

int BlkTextureLoad(string filename, int blkW, int blkH, int blkNum)
{
  return Platform::GetInstance()->BlkTextureLoad(filename, blkW, blkH, blkNum);
}

int TextureLoad(const char * filename)
{
  return Platform::GetInstance()->TextureLoad(filename);
}

int BlkTextureLoad(const char * filename, int blkW, int blkH, int blkNum)
{
  return Platform::GetInstance()->BlkTextureLoad(filename, blkW, blkH, blkNum);
}
