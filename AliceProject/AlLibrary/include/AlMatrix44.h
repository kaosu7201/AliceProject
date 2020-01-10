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
/// @brief 浮動小数型マトリクスクラス 
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

/// 単位行列の設定 
void	UnitMatrix(AlMatrix44 * fmOut);

/// 転地行列の作成 
void	TransposedMatrix(AlMatrix44 * fmOut, const AlMatrix44 * fmIn);

/// 逆行列生成 
void	InverseMatrix(AlMatrix44 * fmOut, const AlMatrix44 * fmIn);

/// マトリクス同士のかけ算 
void	MulMatrix(AlMatrix44 * fmOut, const AlMatrix44 * fmLocal, const AlMatrix44 * fmWorld);

///ベクトルの変換 
void	ApplyMatrix(AlVector3 * fvOut, const AlMatrix44 * fmPose, const AlVector3 * fvIn);
///ベクトルの変換 
void	ApplyMatrixNrm(AlVector3 * fvOut, const AlMatrix44 * fmPose, const AlVector3 * fvIn);
///ベクトルの変換 
void	ApplyMatrix(AlVector4 * fvOut, const AlMatrix44 * fmPose, const AlVector3 * fvIn);
///ベクトルの変換 
void	ApplyMatrix(AlVector4 * fvOut, const AlMatrix44 * fmPose, const AlVector3 * fvIn);

/// マトリクスの回転 
void	RotateMatrixX(AlMatrix44 * mOut, const AlF32 rad);
/// マトリクスの回転 
void	RotateMatrixY(AlMatrix44 * mOut, const AlF32 rad);
/// マトリクスの回転 
void	RotateMatrixZ(AlMatrix44 * mOut, const AlF32 rad);

/// 注視マトリクスの作成 
void	LookAtMatrix(AlMatrix44 * fmOut, const AlVector3 * vEye, const AlVector3 * vLook, const AlVector3 * vUp);

///Projection Matrix 作成 
void	ProjectionMatrix(AlMatrix44 * mOut, const AlF32 fovy, const AlF32 aspect, const AlF32 znear, const AlF32 zfar);
///Projection Matrix 作成 
void	OrthoMatrix(AlMatrix44 * fmOut, const AlF32 width, const AlF32 height, const AlF32 znear, const AlF32 zfar);