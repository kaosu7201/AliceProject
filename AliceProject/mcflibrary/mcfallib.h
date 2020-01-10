#pragma once
#include "platform/Platform.h"
#include "AlColor.h"
#include <cstdio>
void DrawPrintf(int x, int y, AlColor4 color, char* str, ...);

int TextureLoad(string filename);
int BlkTextureLoad(string filename, int blkW, int blkH, int blkNum);
int TextureLoad(const char* filename);
int BlkTextureLoad(const char* filename, int blkW, int blkH, int blkNum);