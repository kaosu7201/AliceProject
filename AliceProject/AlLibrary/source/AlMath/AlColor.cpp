#include	"AlLibrary.h"
#include	"AlColor.h"
#include	"AlMath.h"

void AlColor4::Set(AlF32 x_, AlF32 y_, AlF32 z_, AlF32 w_)
{
  m.x = x_;
  m.y = y_;
  m.z = z_;
  m.w = w_;
}

AlU32 AlColor4::GetRGBAU32() const
{
  AlU32	r_ = (AlU32)AL_CLAMP(r * 255.0f, 0.0f, 255.0f);
  AlU32	g_ = (AlU32)AL_CLAMP(g * 255.0f, 0.0f, 255.0f);
  AlU32	b_ = (AlU32)AL_CLAMP(b * 255.0f, 0.0f, 255.0f);
  AlU32	a_ = (AlU32)AL_CLAMP(a * 255.0f, 0.0f, 255.0f);
  return	AL_RGBA(r_, g_, b_, a_);
}
