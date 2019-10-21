#include "AlLibrary.h"
#include "AlVector3.h"
#include "AlMath.h"
#include <math.h>

void AddVector(AlVector3 * fvOut, const AlVector3 * fvA, const AlVector3 * fvB)
{
  fvOut->x = fvA->x + fvB->x;
  fvOut->y = fvA->y + fvB->y;
  fvOut->z = fvA->z + fvB->z;
}

void SubVector(AlVector3 * fvOut, const AlVector3 * fvA, const AlVector3 * fvB)
{
  fvOut->x = fvA->x - fvB->x;
  fvOut->y = fvA->y - fvB->y;
  fvOut->z = fvA->z - fvB->z;
}

void ScaleVector(AlVector3 * fvOut, const AlVector3 * fvA, const float scale)
{
  fvOut->x = fvA->x * scale;
  fvOut->y = fvA->y * scale;
  fvOut->z = fvA->z * scale;
}

void OuterProduct(AlVector3 * fvOut, const AlVector3 * fvA, const AlVector3 * fvB)
{
  fvOut->x = fvA->y * fvB->z - fvA->z * fvB->y;
  fvOut->y = fvA->z * fvB->x - fvA->x * fvB->z;
  fvOut->z = fvA->x * fvB->y - fvA->y * fvB->x;
}

float InnerProduct(const AlVector3 * fvA, const AlVector3 * fvB)
{
  // NEON ‚Ì•û‚ª’x‚­‚È‚é 
  return ((fvA->x * fvB->x) + (fvA->y * fvB->y) + (fvA->z * fvB->z));
}

float LengthProduct(const AlVector3 * fvA)
{
  return sqrt(InnerProduct(fvA, fvA));
}

float LengthProduct(const AlVector3 * fvA, const AlVector3 * fvB)
{
  AlVector3	vDistance = *fvB - *fvA;
  return	LengthProduct(&vDistance);
}

void Normalize(AlVector3 * fvOut, const AlVector3 * fvA)
{
  const	AlF32	division = (AlF32)sqrt(InnerProduct(fvA, fvA));
  ScaleVector(fvOut, fvA, 1.0f / division);
}

void LerpVector(AlVector3 * fvOut, const AlVector3 * fvA, const AlVector3 * fvB, const float time)
{
  const float invTime = 1.0f - time;
  // •âŠÔ 
  fvOut->x = fvA->x * invTime + fvB->x * time;
  fvOut->y = fvA->y * invTime + fvB->y * time;
  fvOut->z = fvA->z * invTime + fvB->z * time;
}

void MaxVector(AlVector3 * fvOut, const AlVector3 * fvA, const AlVector3 * fvB)
{
  fvOut->x = (fvA->x < fvB->x) ? fvB->x : fvA->x;
  fvOut->y = (fvA->y < fvB->y) ? fvB->y : fvA->y;
  fvOut->z = (fvA->z < fvB->z) ? fvB->z : fvA->z;
}

void MinVector(AlVector3 * fvOut, const AlVector3 * fvA, const AlVector3 * fvB)
{
  fvOut->x = (fvA->x > fvB->x) ? fvB->x : fvA->x;
  fvOut->y = (fvA->y > fvB->y) ? fvB->y : fvA->y;
  fvOut->z = (fvA->z > fvB->z) ? fvB->z : fvA->z;
}

void MaxProduct(AlVector3 * x, const AlVector3 * y, const AlVector3 * z)
{
  MaxVector(x, y, z);
}

void MinProduct(AlVector3 * x, const AlVector3 * y, const AlVector3 * z)
{
  MinVector(x, y, z);
}

void HermiteSpline(AlVector3 * vOut, const AlVector3 * v1, const AlVector3 * v2, const AlVector3 * v3, const AlVector3 * v4, AlF32 t)
{
  const AlF32 t2 = t * t;
  const AlF32 t3 = t2 * t;
  const AlF32 contfAlpha = 0.0f;
  const AlF32 alpha = ((1 - contfAlpha) * 0.5f);
  AlVector3	m0, m1;
  AlVector3	vWork, vSub;

  vWork = (*v2) - (*v1);
  vSub = (*v3) - (*v2);
  m0 = vWork + vSub;
  m1 = (*v4) - (*v3);
  m1 = vSub + m1;
  m0 = m0 * alpha;
  m1 = m1 * alpha;

  vWork = (*v2) * ((2.0f * t3) - (3.0f * t2) + 1.0f);
  m0 = m0 * ((t3 - (2.0f * t2) + t));
  m1 = m1 * (t3 - t2);

  m0 = vWork + m0;
  m0 = m0 + m1;
  vWork = (*v3) * (((-2.0f*t3) + (3.0f*t2)));
  (*vOut) = vWork + m0;
}

void AlVector3::Set(AlF32 x_, AlF32 y_, AlF32 z_)
{
  x = x_;
  y = y_;
  z = z_;
}

AlBool AlVector3::operator==(const AlVector3 & vParam) const
{
  if ((vParam.x == x) &&
    (vParam.y == y) &&
    (vParam.z == z))
  {
    return AL_TRUE;
  }
  return AL_FALSE;
}

AlVector3 AlVector3::operator+(const AlVector3 & vAdd) const
{
  AlVector3	vResult;
  AddVector(&vResult, this, &vAdd);
  return vResult;
}

AlVector3 AlVector3::operator-(const AlVector3 & vSub) const
{
  AlVector3	vResult;
  SubVector(&vResult, this, &vSub);
  return vResult;
}

AlVector3 AlVector3::operator*(const AlF32 param) const
{
  AlVector3	vResult;
  ScaleVector(&vResult, this, param);
  return vResult;
}

AlVector3 AlVector3::operator/(const AlF32 param) const
{
  AlVector3	vResult;
  ScaleVector(&vResult, this, 1.0f / param);
  return vResult;
}

void AlVector3::operator+=(const AlVector3 & vAdd)
{
  AddVector(this, this, &vAdd);
}

void AlVector3::operator-=(const AlVector3 & vSub)
{
  SubVector(this, this, &vSub);
}

void AlVector3::operator*=(const AlF32 param)
{
  ScaleVector(this, this, param);
}

void AlVector3::operator*=(const AlVector3 & vMul)
{
  this->x *= vMul.x;
  this->y *= vMul.y;
  this->z *= vMul.z;
}

void AlVector3::operator/=(const AlF32 param)
{
  ScaleVector(this, this, 1.0f / param);
}
