#pragma once
#include "AlLibrary.h"
#include "AlDraw.h"
class AlDrawImage :
  public AlDraw
{
  typedef AlDraw base;
public:
  AlDrawImage();
  virtual ~AlDrawImage();

  void Draw();

  int handle;
  int index;
  string name;
private:
  float priority;
  float x;
  float y;
};

