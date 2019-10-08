#pragma once
#include "AlPrototype.h"
class AlVector2;

/// 加算 
void	AddVector(AlVector2 * fvOut, const AlVector2 * fvA, const AlVector2 * fvB);
/// 減算 
void	SubVector(AlVector2 * fvOut, const AlVector2 * fvA, const AlVector2 * fvB);
/// スケール 
void	ScaleVector(AlVector2 * fvOut, const AlVector2 * fvA, const AlF32 scale);
/// 外積 
//void	OuterProduct( AlVector2 * fvOut , const AlVector2 * fvA , const AlVector2 * fvB );
/// 内積 
AlF32	InnerProduct(const AlVector2 * fvA, const AlVector2 * fvB);
/// 距離
AlF32	LengthProduct(const AlVector2 * fvA);
/// 正規化 
void	Normalize(AlVector2 * fvOut, const AlVector2 * fvA);
/// 線形補間
void	LerpVector(AlVector2 * fvOut, const AlVector2 * fvA, const AlVector2 * fvB, const AlF32 time);
/// 最大値を求める 
void	MaxVector(AlVector2 * fvOut, const AlVector2 * fvA, const AlVector2 * fvB);
/// 最小値を求める 
void	MinVector(AlVector2 * fvOut, const AlVector2 * fvA, const AlVector2 * fvB);
/// 最大値を求める 
void	MaxProduct(AlVector2 * x, const AlVector2 * y, const AlVector2 * z);
/// 最小値を求める 
void	MinProduct(AlVector2 * x, const AlVector2 * y, const AlVector2 * z);

class AlVector2
{
public:
  union
  {
    float m[2];
    struct
    {
      float x, y;
    };
  };
  void Set(float _x, float _y);
  AlBool		operator == (const AlVector2 & vParam) const;
  AlVector2	operator +  (const AlVector2 & vParam) const;
  AlVector2	operator -  (const AlVector2 & vParam) const;
  AlVector2	operator *  (float        param) const;
  AlVector2	operator /  (float        param) const;
  void		operator += (const AlVector2 & vParam);
  void		operator -= (const AlVector2 & vParam);
  void		operator *= (float        param);
  void		operator /= (float        param);

  inline	float	&operator [] (const AlU32 id) { return m[id]; }
  inline	float	operator  [] (const AlU32 id) const { return m[id]; }
};