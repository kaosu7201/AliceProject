#include "mcfallib.h"
#include <cstdarg>

void DrawPrintf(int x, int y, AlColor4 color, char* str, ...)
{
  char sz[0xffff];		// 配列数が[0xffff]なのは、これくらいあれば足りるだろう的サイズ。もし溢れたら問題が出る。
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
