#pragma once
#include	"AlPrototype.h"
class		AlVector4;
#include	"AlVector3.h"

/// ���Z 
void	AddVector(AlVector4 * fvOut, const AlVector4 * fvA, const AlVector4 * fvB);
/// ���Z 
void	SubVector(AlVector4 * fvOut, const AlVector4 * fvA, const AlVector4 * fvB);
/// �X�P�[�� 
void	ScaleVector(AlVector4 * fvOut, const AlVector4 * fvA, const AlF32 scale);
/// �O�� 
void	OuterProduct(AlVector4 * fvOut, const AlVector4 * fvA, const AlVector4 * fvB);
/// ���� 
AlF32	InnerProduct(const AlVector4 * fvA, const AlVector4 * fvB);
/// ����
AlF32	LengthProduct(const AlVector4 * fvA);
/// ���K�� 
void	Normalize(AlVector4 * fvOut, const AlVector4 * fvA);
/// ���`���
void	LerpVector(AlVector4 * fvOut, const AlVector4 * fvA, const AlVector4 * fvB, const AlF32 time);
/// �ő�l�����߂� 
void	MaxVector(AlVector4 * fvOut, const AlVector4 * fvA, const AlVector4 * fvB);
/// �ŏ��l�����߂� 
void	MinVector(AlVector4 * fvOut, const AlVector4 * fvA, const AlVector4 * fvB);
/// �ő�l�����߂� 
void	MaxProduct(AlVector4 * x, const AlVector4 * y, const AlVector4 * z);
/// �ŏ��l�����߂� 
void	MinProduct(AlVector4 * x, const AlVector4 * y, const AlVector4 * z);

// --------------------------------------------------------------------------
/// @brief ���������^�x�N�g���N���X 
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