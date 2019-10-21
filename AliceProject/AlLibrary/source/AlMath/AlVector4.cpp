#include "AlLibrary.h"
#include "AlVector4.h"
#include "AlMath.h"
#include <math.h>

void AddVector(AlVector4 * fvOut, const AlVector4 * fvA, const AlVector4 * fvB)
{
  fvOut->x = fvA->x + fvB->x;
  fvOut->y = fvA->y + fvB->y;
  fvOut->z = fvA->z + fvB->z;
  fvOut->w = fvA->w + fvB->w;
}

void SubVector(AlVector4 * fvOut, const AlVector4 * fvA, const AlVector4 * fvB)
{
  fvOut->x = fvA->x - fvB->x;
  fvOut->y = fvA->y - fvB->y;
  fvOut->z = fvA->z - fvB->z;
  fvOut->w = fvA->w - fvB->w;
}

void ScaleVector(AlVector4 * fvOut, const AlVector4 * fvA, const AlF32 scale)
{
  fvOut->x = fvA->x * scale;
  fvOut->y = fvA->y * scale;
  fvOut->z = fvA->z * scale;
  fvOut->w = fvA->w * scale;
}

void OuterProduct(AlVector4 * fvOut, const AlVector4 * fvA, const AlVector4 * fvB)
{
  fvOut->x = fvA->y * fvB->z - fvA->z * fvB->y;
  fvOut->y = fvA->z * fvB->x - fvA->x * fvB->z;
  fvOut->z = fvA->x * fvB->y - fvA->y * fvB->x;
  fvOut->w = fvA->w;
}

float InnerProduct(const AlVector4 * fvA, const AlVector4 * fvB)
{
  return ((fvA->x * fvB->x) + (fvA->y * fvB->y) + (fvA->z * fvB->z) + (fvA->w * fvB->w));
}

float LengthProduct(const AlVector4 * fvA)
{
  return sqrt(InnerProduct(fvA, fvA));
}

void Normalize(AlVector4 * fvOut, const AlVector4 * fvA)
{
  const	AlF32	division = (AlF32)sqrt(InnerProduct(fvA, fvA));
  ScaleVector(fvOut, fvA, 1.0f / division);
}

void LerpVector(AlVector4 * fvOut, const AlVector4 * fvA, const AlVector4 * fvB, const AlF32 time)
{
  const AlF32 invTime = 1.0f - time;
  // •âŠÔ 
  fvOut->x = fvA->x * invTime + fvB->x * time;
  fvOut->y = fvA->y * invTime + fvB->y * time;
  fvOut->z = fvA->z * invTime + fvB->z * time;
  fvOut->w = fvA->w * invTime + fvB->w * time;
}

void MaxVector(AlVector4 * fvOut, const AlVector4 * fvA, const AlVector4 * fvB)
{
  fvOut->x = (fvA->x < fvB->x) ? fvB->x : fvA->x;
  fvOut->y = (fvA->y < fvB->y) ? fvB->y : fvA->y;
  fvOut->z = (fvA->z < fvB->z) ? fvB->z : fvA->z;
  fvOut->w = (fvA->w < fvB->w) ? fvB->w : fvA->w;
}

void MinVector(AlVector4 * fvOut, const AlVector4 * fvA, const AlVector4 * fvB)
{
  fvOut->x = (fvA->x > fvB->x) ? fvB->x : fvA->x;
  fvOut->y = (fvA->y > fvB->y) ? fvB->y : fvA->y;
  fvOut->z = (fvA->z > fvB->z) ? fvB->z : fvA->z;
  fvOut->w = (fvA->w > fvB->w) ? fvB->w : fvA->w;
}

void MaxProduct(AlVector4 * x, const AlVector4 * y, const AlVector4 * z)
{
  MaxVector(x, y, z);
}

void MinProduct(AlVector4 * x, const AlVector4 * y, const AlVector4 * z)
{
  MinVector(x, y, z);
}

void AlVector4::Set(AlF32 x_, AlF32 y_, AlF32 z_, AlF32 w_)
{
  x = x_;
  y = y_;
  z = z_;
  w = w_;
}

AlVector4 AlVector4::operator+(const AlVector4 & vAdd) const
{
  AlVector4	vResult;
  AddVector(&vResult, this, &vAdd);
  return vResult;
}

AlVector4 AlVector4::operator-(const AlVector4 & vSub) const
{
  AlVector4	vResult;
  SubVector(&vResult, this, &vSub);
  return vResult;
}

AlVector4 AlVector4::operator+(const AlVector3 & vAdd) const
{
  AlVector4	vResult;
  vResult.x = x + vAdd.x;
  vResult.y = y + vAdd.y;
  vResult.z = z + vAdd.z;
  vResult.w = w;
  return vResult;
}

AlVector4 AlVector4::operator-(const AlVector3 & vSub) const
{
  AlVector4	vResult;
  vResult.x = x - vSub.x;
  vResult.y = y - vSub.y;
  vResult.z = z - vSub.z;
  vResult.w = w;
  return vResult;
}

AlVector4 AlVector4::operator*(const AlF32 param) const
{
  AlVector4	vResult;
  ScaleVector(&vResult, this, param);
  return vResult;
}

AlVector4 AlVector4::operator/(const AlF32 param) const
{
  AlVector4	vResult;
  ScaleVector(&vResult, this, 1.0f / param);
  return vResult;
}

void AlVector4::operator+=(const AlVector4 & vAdd)
{
  AddVector(this, this, &vAdd);
}

void AlVector4::operator-=(const AlVector4 & vSub)
{
  SubVector(this, this, &vSub);
}

void AlVector4::operator*=(const AlF32 param)
{
  ScaleVector(this, this, param);
}

void AlVector4::operator/=(const AlF32 param)
{
  ScaleVector(this, this, 1.0f / param);
}
