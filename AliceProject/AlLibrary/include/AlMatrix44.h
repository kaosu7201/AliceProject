// --------------------------------------------------------------------------
/// @file 
/// @brief 
// 
// --------------------------------------------------------------------------
#pragma once
#include "AlPrototype.h"
#include "AlVector4.h"
class AlVector3;

// --------------------------------------------------------------------------
/// @brief ���������^�}�g���N�X�N���X 
// --------------------------------------------------------------------------
class AlMatrix44
{
public:
  union
  {
    float		m[16];
    struct
    {
      AlVector4	v[4];
    };
    struct
    {
      AlVector4	x, y, z, w;
    };
  };
};

/// �P�ʍs��̐ݒ� 
void	UnitMatrix(AlMatrix44 * fmOut);

/// �]�n�s��̍쐬 
void	TransposedMatrix(AlMatrix44 * fmOut, const AlMatrix44 * fmIn);

/// �t�s�񐶐� 
void	InverseMatrix(AlMatrix44 * fmOut, const AlMatrix44 * fmIn);

/// �}�g���N�X���m�̂����Z 
void	MulMatrix(AlMatrix44 * fmOut, const AlMatrix44 * fmLocal, const AlMatrix44 * fmWorld);

///�x�N�g���̕ϊ� 
void	ApplyMatrix(AlVector3 * fvOut, const AlMatrix44 * fmPose, const AlVector3 * fvIn);
///�x�N�g���̕ϊ� 
void	ApplyMatrixNrm(AlVector3 * fvOut, const AlMatrix44 * fmPose, const AlVector3 * fvIn);
///�x�N�g���̕ϊ� 
void	ApplyMatrix(AlVector4 * fvOut, const AlMatrix44 * fmPose, const AlVector3 * fvIn);
///�x�N�g���̕ϊ� 
void	ApplyMatrix(AlVector4 * fvOut, const AlMatrix44 * fmPose, const AlVector3 * fvIn);

/// �}�g���N�X�̉�] 
void	RotateMatrixX(AlMatrix44 * mOut, const AlF32 rad);
/// �}�g���N�X�̉�] 
void	RotateMatrixY(AlMatrix44 * mOut, const AlF32 rad);
/// �}�g���N�X�̉�] 
void	RotateMatrixZ(AlMatrix44 * mOut, const AlF32 rad);

/// �����}�g���N�X�̍쐬 
void	LookAtMatrix(AlMatrix44 * fmOut, const AlVector3 * vEye, const AlVector3 * vLook, const AlVector3 * vUp);

///Projection Matrix �쐬 
void	ProjectionMatrix(AlMatrix44 * mOut, const AlF32 fovy, const AlF32 aspect, const AlF32 znear, const AlF32 zfar);
///Projection Matrix �쐬 
void	OrthoMatrix(AlMatrix44 * fmOut, const AlF32 width, const AlF32 height, const AlF32 znear, const AlF32 zfar);