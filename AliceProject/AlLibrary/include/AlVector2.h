#pragma once
#include "AlPrototype.h"
class AlVector2;

/// ���Z 
void	AddVector(AlVector2 * fvOut, const AlVector2 * fvA, const AlVector2 * fvB);
/// ���Z 
void	SubVector(AlVector2 * fvOut, const AlVector2 * fvA, const AlVector2 * fvB);
/// �X�P�[�� 
void	ScaleVector(AlVector2 * fvOut, const AlVector2 * fvA, const AlF32 scale);
/// �O�� 
//void	OuterProduct( AlVector2 * fvOut , const AlVector2 * fvA , const AlVector2 * fvB );
/// ���� 
AlF32	InnerProduct(const AlVector2 * fvA, const AlVector2 * fvB);
/// ����
AlF32	LengthProduct(const AlVector2 * fvA);
/// ���K�� 
void	Normalize(AlVector2 * fvOut, const AlVector2 * fvA);
/// ���`���
void	LerpVector(AlVector2 * fvOut, const AlVector2 * fvA, const AlVector2 * fvB, const AlF32 time);
/// �ő�l�����߂� 
void	MaxVector(AlVector2 * fvOut, const AlVector2 * fvA, const AlVector2 * fvB);
/// �ŏ��l�����߂� 
void	MinVector(AlVector2 * fvOut, const AlVector2 * fvA, const AlVector2 * fvB);
/// �ő�l�����߂� 
void	MaxProduct(AlVector2 * x, const AlVector2 * y, const AlVector2 * z);
/// �ŏ��l�����߂� 
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