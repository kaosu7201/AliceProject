// --------------------------------------------------------------------------
/// @file 
/// @brief 
// 
// --------------------------------------------------------------------------
#include "AlLibrary.h"
#include "AlVector2.h"
#include "AlMath.h"
#include <math.h>

// --------------------------------------------------------------------------
/// @brief â¡éZ 
// --------------------------------------------------------------------------
void	AddVector(AlVector2 * fvOut, const AlVector2 * fvA, const AlVector2 * fvB)
{
  fvOut->x = fvA->x + fvB->x;
  fvOut->y = fvA->y + fvB->y;
}
// --------------------------------------------------------------------------
/// @brief å∏éZ 
// --------------------------------------------------------------------------
void	SubVector(AlVector2 * fvOut, const AlVector2 * fvA, const AlVector2 * fvB)
{
  fvOut->x = fvA->x - fvB->x;
  fvOut->y = fvA->y - fvB->y;
}
// --------------------------------------------------------------------------
/// @brief ÉXÉPÅ[Éã 
// --------------------------------------------------------------------------
void	ScaleVector(AlVector2 * fvOut, const AlVector2 * fvA, const AlF32 scale)
{
  fvOut->x = fvA->x * scale;
  fvOut->y = fvA->y * scale;
}
// --------------------------------------------------------------------------
/// @brief ì‡êœ 
// --------------------------------------------------------------------------
AlF32	InnerProduct(const AlVector2 * fvA, const AlVector2 * fvB)
{
  return	((fvA->x * fvB->x) + (fvA->y * fvB->y));
}
// --------------------------------------------------------------------------
/// @brief ãóó£
// --------------------------------------------------------------------------
AlF32	LengthProduct(const AlVector2 * fvA)
{
  return sqrt(InnerProduct(fvA, fvA));
}
// --------------------------------------------------------------------------
/// @brief ê≥ãKâª 
// --------------------------------------------------------------------------
void	Normalize(AlVector2 * fvOut, const AlVector2 * fvA)
{
  const	AlF32	division = (AlF32)sqrt(InnerProduct(fvA, fvA));
  //SI_MATH_ASSERT((division != 0.0f), "Normalize SiVector2 Division by Zero\n");
  ScaleVector(fvOut, fvA, 1.0f / division);
}
// --------------------------------------------------------------------------
/// @brief ê¸å`ï‚ä‘
// --------------------------------------------------------------------------
void	LerpVector(AlVector2 * fvOut, const AlVector2 * fvA, const AlVector2 * fvB, const AlF32 time)
{
  const AlF32 invTime = 1.0f - time;
  // ï‚ä‘ 
  fvOut->x = fvA->x * invTime + fvB->x * time;
  fvOut->y = fvA->y * invTime + fvB->y * time;
}
// --------------------------------------------------------------------------
/// @brief ç≈ëÂílÇãÅÇﬂÇÈ 
// --------------------------------------------------------------------------
void	MaxVector(AlVector2 * fvOut, const AlVector2 * fvA, const AlVector2 * fvB)
{
  fvOut->x = (fvA->x < fvB->x) ? fvB->x : fvA->x;
  fvOut->y = (fvA->y < fvB->y) ? fvB->y : fvA->y;
}
// --------------------------------------------------------------------------
/// @brief ç≈è¨ílÇãÅÇﬂÇÈ 
// --------------------------------------------------------------------------
void	MinVector(AlVector2 * fvOut, const AlVector2 * fvA, const AlVector2 * fvB)
{
  fvOut->x = (fvA->x > fvB->x) ? fvB->x : fvA->x;
  fvOut->y = (fvA->y > fvB->y) ? fvB->y : fvA->y;
}
// --------------------------------------------------------------------------
/// @brief ç≈ëÂílÇãÅÇﬂÇÈ 
// --------------------------------------------------------------------------
void	MaxProduct(AlVector2 * x, const AlVector2 * y, const AlVector2 * z)
{
  MaxVector(x, y, z);
}
// --------------------------------------------------------------------------
/// @brief ç≈è¨ílÇãÅÇﬂÇÈ 
// --------------------------------------------------------------------------
void	MinProduct(AlVector2 * x, const AlVector2 * y, const AlVector2 * z)
{
  MinVector(x, y, z);
}

// --------------------------------------------------------------------------
/// @brief êîílÇÃê›íË 
// --------------------------------------------------------------------------
void AlVector2::Set(float _x, float _y)
{
  x = _x;
  y = _y;
}


// --------------------------------------------------------------------------
/// @brief î‰är 
// --------------------------------------------------------------------------
AlBool AlVector2::operator==(const AlVector2 & vParam) const
{
  if ((x == vParam.x) && (y == vParam.y))
  {
    return AL_TRUE;
  }
  return AL_FALSE;
}

// --------------------------------------------------------------------------
/// @brief â¡éZ 
// --------------------------------------------------------------------------
AlVector2 AlVector2::operator+(const AlVector2 & vParam) const
{
  AlVector2 vResult = { x + vParam.x, y + vParam.y };
  return vResult;
}

// --------------------------------------------------------------------------
/// @brief å∏éZ 
// --------------------------------------------------------------------------
AlVector2 AlVector2::operator-(const AlVector2 & vParam) const
{
  AlVector2 vResult = { x - vParam.x, y - vParam.y };
  return vResult;
}

// --------------------------------------------------------------------------
/// @brief èÊéZ 
// --------------------------------------------------------------------------
AlVector2 AlVector2::operator*(float param) const
{
  AlVector2 vResult = { x * param, y * param };
  return vResult;
}

// --------------------------------------------------------------------------
/// @brief èúéZ 
// --------------------------------------------------------------------------
AlVector2 AlVector2::operator/(float param) const
{
  AlVector2	vResult;
  ScaleVector(&vResult, this, 1.0f / param);
  return vResult;
}

// --------------------------------------------------------------------------
/// @brief â¡éZ 
// --------------------------------------------------------------------------
void AlVector2::operator+=(const AlVector2 & vParam)
{
  x += vParam.x;
  y += vParam.y;
}

// --------------------------------------------------------------------------
/// @brief å∏éZ 
// --------------------------------------------------------------------------
void AlVector2::operator-=(const AlVector2 & vParam)
{
  x -= vParam.x;
  y -= vParam.y;
}

// --------------------------------------------------------------------------
/// @brief èÊéZ 
// --------------------------------------------------------------------------
void AlVector2::operator*=(float param)
{
  x *= param;
  y *= param;
}

// --------------------------------------------------------------------------
/// @brief èúéZ 
// --------------------------------------------------------------------------
void AlVector2::operator/=(float param)
{
  AlF32		scale = 1.0f / param;
  x *= scale;
  y *= scale;
}
