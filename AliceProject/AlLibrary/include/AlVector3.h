#pragma once
#include	"AlPrototype.h"
class		AlVector3;


/// 加算 
void	AddVector(AlVector3 * fvOut, const AlVector3 * fvA, const AlVector3 * fvB);
/// 減算 
void	SubVector(AlVector3 * fvOut, const AlVector3 * fvA, const AlVector3 * fvB);
/// スケール 
void	ScaleVector(AlVector3 * fvOut, const AlVector3 * fvA, const float scale);
/// 外積 
void	OuterProduct(AlVector3 * fvOut, const AlVector3 * fvA, const AlVector3 * fvB);
/// 内積 
float	InnerProduct(const AlVector3 * fvA, const AlVector3 * fvB);
/// 距離
float	LengthProduct(const AlVector3 * fvA);
/// 距離
float	LengthProduct(const AlVector3 * fvA, const AlVector3 * fvB);
/// 正規化 
void	Normalize(AlVector3 * fvOut, const AlVector3 * fvA);
/// 線形補間
void	LerpVector(AlVector3 * fvOut, const AlVector3 * fvA, const AlVector3 * fvB, const float time);
/// 最大値を求める 
void	MaxVector(AlVector3 * fvOut, const AlVector3 * fvA, const AlVector3 * fvB);
/// 最小値を求める 
void	MinVector(AlVector3 * fvOut, const AlVector3 * fvA, const AlVector3 * fvB);
/// 最大値を求める 
void	MaxProduct(AlVector3 * x, const AlVector3 * y, const AlVector3 * z);
/// 最小値を求める 
void	MinProduct(AlVector3 * x, const AlVector3 * y, const AlVector3 * z);
/// エルミートスプライン 
void	HermiteSpline(AlVector3 * vOut, const AlVector3 * v1, const AlVector3 * v2, const AlVector3 * v3, const AlVector3 * v4, AlF32 t);

// --------------------------------------------------------------------------
/// @brief 浮動小数型ベクトルクラス 
// --------------------------------------------------------------------------
class AlVector3
{
public:
  union
  {
    AlF32		m[3];
    struct
    {
      AlF32	x, y, z;
    };
  };
  void		Set(AlF32 x_, AlF32 y_, AlF32 z_);
  AlBool		operator == (const AlVector3 & vParam) const;
  AlVector3	operator +  (const AlVector3 & vAdd) const;
  AlVector3	operator -  (const AlVector3 & vSub) const;
  AlVector3	operator *  (const AlF32       param) const;
  AlVector3	operator /  (const AlF32       param) const;
  void		operator += (const AlVector3 & vAdd);
  void		operator -= (const AlVector3 & vSub);
  void		operator *= (const AlF32       param);
  void		operator *= (const AlVector3 & vMul);
  void		operator /= (const AlF32       param);

  inline	AlF32	&operator [] (const AlU32 id) { return m[id]; }
  inline	AlF32	operator  [] (const AlU32 id) const { return m[id]; }
};