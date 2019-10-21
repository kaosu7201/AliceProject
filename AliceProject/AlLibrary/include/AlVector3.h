#pragma once
#include	"AlPrototype.h"
class		AlVector3;


/// ���Z 
void	AddVector(AlVector3 * fvOut, const AlVector3 * fvA, const AlVector3 * fvB);
/// ���Z 
void	SubVector(AlVector3 * fvOut, const AlVector3 * fvA, const AlVector3 * fvB);
/// �X�P�[�� 
void	ScaleVector(AlVector3 * fvOut, const AlVector3 * fvA, const float scale);
/// �O�� 
void	OuterProduct(AlVector3 * fvOut, const AlVector3 * fvA, const AlVector3 * fvB);
/// ���� 
float	InnerProduct(const AlVector3 * fvA, const AlVector3 * fvB);
/// ����
float	LengthProduct(const AlVector3 * fvA);
/// ����
float	LengthProduct(const AlVector3 * fvA, const AlVector3 * fvB);
/// ���K�� 
void	Normalize(AlVector3 * fvOut, const AlVector3 * fvA);
/// ���`���
void	LerpVector(AlVector3 * fvOut, const AlVector3 * fvA, const AlVector3 * fvB, const float time);
/// �ő�l�����߂� 
void	MaxVector(AlVector3 * fvOut, const AlVector3 * fvA, const AlVector3 * fvB);
/// �ŏ��l�����߂� 
void	MinVector(AlVector3 * fvOut, const AlVector3 * fvA, const AlVector3 * fvB);
/// �ő�l�����߂� 
void	MaxProduct(AlVector3 * x, const AlVector3 * y, const AlVector3 * z);
/// �ŏ��l�����߂� 
void	MinProduct(AlVector3 * x, const AlVector3 * y, const AlVector3 * z);
/// �G���~�[�g�X�v���C�� 
void	HermiteSpline(AlVector3 * vOut, const AlVector3 * v1, const AlVector3 * v2, const AlVector3 * v3, const AlVector3 * v4, AlF32 t);

// --------------------------------------------------------------------------
/// @brief ���������^�x�N�g���N���X 
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