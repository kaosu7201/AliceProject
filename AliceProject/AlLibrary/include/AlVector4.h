#pragma once
#include	"AlPrototype.h"
class		AlVector4;
#include	"AlVector3.h"

/// 加算 
void	AddVector(AlVector4 * fvOut, const AlVector4 * fvA, const AlVector4 * fvB);
/// 減算 
void	SubVector(AlVector4 * fvOut, const AlVector4 * fvA, const AlVector4 * fvB);
/// スケール 
void	ScaleVector(AlVector4 * fvOut, const AlVector4 * fvA, const AlF32 scale);
/// 外積 
void	OuterProduct(AlVector4 * fvOut, const AlVector4 * fvA, const AlVector4 * fvB);
/// 内積 
AlF32	InnerProduct(const AlVector4 * fvA, const AlVector4 * fvB);
/// 距離
AlF32	LengthProduct(const AlVector4 * fvA);
/// 正規化 
void	Normalize(AlVector4 * fvOut, const AlVector4 * fvA);
/// 線形補間
void	LerpVector(AlVector4 * fvOut, const AlVector4 * fvA, const AlVector4 * fvB, const AlF32 time);
/// 最大値を求める 
void	MaxVector(AlVector4 * fvOut, const AlVector4 * fvA, const AlVector4 * fvB);
/// 最小値を求める 
void	MinVector(AlVector4 * fvOut, const AlVector4 * fvA, const AlVector4 * fvB);
/// 最大値を求める 
void	MaxProduct(AlVector4 * x, const AlVector4 * y, const AlVector4 * z);
/// 最小値を求める 
void	MinProduct(AlVector4 * x, const AlVector4 * y, const AlVector4 * z);

// --------------------------------------------------------------------------
/// @brief 浮動小数型ベクトルクラス 
// --------------------------------------------------------------------------
class AlVector4
{
public:
  union
  {
    AlF32		m[4];
    struct
    {
      AlF32	x, y, z, w;
    };
  };
  void		Set(AlF32 x_, AlF32 y_, AlF32 z_, AlF32 w_);
  AlVector4	operator +  (const AlVector4 & vAdd) const;
  AlVector4	operator -  (const AlVector4 & vSub) const;
  AlVector4	operator +  (const AlVector3 & vAdd) const;
  AlVector4	operator -  (const AlVector3 & vSub) const;
  AlVector4	operator *  (const AlF32       param) const;
  AlVector4	operator /  (const AlF32       param) const;
  void		operator += (const AlVector4 & vAdd);
  void		operator -= (const AlVector4 & vSub);
  void		operator *= (const AlF32       param);
  void		operator /= (const AlF32       param);


  inline	AlF32	&operator [] (const AlU32 id) { return m[id]; }
  inline	AlF32	operator  [] (const AlU32 id) const { return m[id]; }

};