// --------------------------------------------------------------------------
/// @file 
/// @brief 
// 
// --------------------------------------------------------------------------
#include	"AlLibrary.h"
#include	"AlMatrix44.h"
#include	"AlVector3.h"
#include	"AlMath.h"
#include	<math.h>
#include	<float.h>

// --------------------------------------------------------------------------
/// @brief Projection Matrix 作成 
// --------------------------------------------------------------------------
/// @note D3DXMatrixPerspectiveFovLH と同じ物です 
void	ProjectionMatrix( AlMatrix44 * mOut , const AlF32 fovy , const AlF32 aspect , const AlF32 znear , const AlF32 zfar   )
{
	const AlF32	hscale =    1.0f / tanf(fovy*0.5f);
	const AlF32	wscale = -hscale /  aspect;
#if		defined( AL_DX_MATRIX )
	// DirectX 系 
	// z/w = 0.0 - 1.0
	const AlF32	qscale =  zfar   / (zfar-znear);
	const AlF32	dscale = -znear  *  qscale;
#else
	// OpenGL 系 
	// z/w = -1.0 - 1.0
	const AlF32	qscale = ( zfar + znear ) / (zfar-znear);
	const AlF32	dscale =  -2.0f * ( zfar * znear ) / (zfar-znear);
#endif

	mOut->v[0].x = wscale;
	mOut->v[0].y = 0.0f;
	mOut->v[0].z = 0.0f;
	mOut->v[0].w = 0.0f;

	mOut->v[1].x = 0.0f;
	mOut->v[1].y = hscale;
	mOut->v[1].z = 0.0f;
	mOut->v[1].w = 0.0f;

	mOut->v[2].x = 0.0f;
	mOut->v[2].y = 0.0f;
	mOut->v[2].z = qscale;
	mOut->v[2].w = 1.0f;

	mOut->v[3].x = 0.0f;
	mOut->v[3].y = 0.0f;
	mOut->v[3].z = dscale;
	mOut->v[3].w = 0.0f;
}

// --------------------------------------------------------------------------
/// @brief Projection Matrix 作成 
// --------------------------------------------------------------------------
/// @note D3DXMatrixOrthoLH と同じ物です 
void	OrthoMatrix( AlMatrix44 * mOut , const AlF32 width , const AlF32 height ,const AlF32 znear , const AlF32 zfar   )
{
	const AlF32	hscale =  2.0f  / height;
	const AlF32	wscale =  2.0f  / width;
#if		defined( AL_DX_MATRIX )
	// DirectX 系 
	// z/w = 0.0 - 1.0
	const AlF32	qscale =  1.0f  / (zfar - znear);
	const AlF32	dscale = -znear / (zfar - znear);
#else
	// OpenGL 系 
	// z/w = -1.0 - 1.0
//	const AlF32	qscale =  1.0f  / (zfar - znear);
//	const AlF32	dscale = -znear / (zfar - znear);
	const AlF32	qscale =  2.0f             / (zfar - znear);
	const AlF32	dscale = -( zfar + znear ) / (zfar - znear);
#endif
	mOut->v[0].x = wscale;
	mOut->v[0].y = 0.0f;
	mOut->v[0].z = 0.0f;
	mOut->v[0].w = 0.0f;

	mOut->v[1].x = 0.0f;
	mOut->v[1].y = hscale;
	mOut->v[1].z = 0.0f;
	mOut->v[1].w = 0.0f;

	mOut->v[2].x = 0.0f;
	mOut->v[2].y = 0.0f;
	mOut->v[2].z = qscale;
	mOut->v[2].w = 0.0f;

	mOut->v[3].x = 0.0f;
	mOut->v[3].y = 0.0f;
	mOut->v[3].z = dscale;
	mOut->v[3].w = 1.0f;
}

// --------------------------------------------------------------------------
/// @brief マトリクス同士のかけ算 
// --------------------------------------------------------------------------
void	MulMatrix( AlMatrix44 * fmOut , const AlMatrix44 * fmLocal , const AlMatrix44 * fmWorld )
{
	AlMatrix44 fmResult;

	fmResult.v[0].x = fmLocal->v[0].x * fmWorld->v[0].x + fmLocal->v[0].y * fmWorld->v[1].x + fmLocal->v[0].z * fmWorld->v[2].x + fmLocal->v[0].w * fmWorld->v[3].x;
	fmResult.v[1].x = fmLocal->v[1].x * fmWorld->v[0].x + fmLocal->v[1].y * fmWorld->v[1].x + fmLocal->v[1].z * fmWorld->v[2].x + fmLocal->v[1].w * fmWorld->v[3].x;
	fmResult.v[2].x = fmLocal->v[2].x * fmWorld->v[0].x + fmLocal->v[2].y * fmWorld->v[1].x + fmLocal->v[2].z * fmWorld->v[2].x + fmLocal->v[2].w * fmWorld->v[3].x;
	fmResult.v[3].x = fmLocal->v[3].x * fmWorld->v[0].x + fmLocal->v[3].y * fmWorld->v[1].x + fmLocal->v[3].z * fmWorld->v[2].x + fmLocal->v[3].w * fmWorld->v[3].x;

	fmResult.v[0].y = fmLocal->v[0].x * fmWorld->v[0].y + fmLocal->v[0].y * fmWorld->v[1].y + fmLocal->v[0].z * fmWorld->v[2].y + fmLocal->v[0].w * fmWorld->v[3].y;
	fmResult.v[1].y = fmLocal->v[1].x * fmWorld->v[0].y + fmLocal->v[1].y * fmWorld->v[1].y + fmLocal->v[1].z * fmWorld->v[2].y + fmLocal->v[1].w * fmWorld->v[3].y;
	fmResult.v[2].y = fmLocal->v[2].x * fmWorld->v[0].y + fmLocal->v[2].y * fmWorld->v[1].y + fmLocal->v[2].z * fmWorld->v[2].y + fmLocal->v[2].w * fmWorld->v[3].y;
	fmResult.v[3].y = fmLocal->v[3].x * fmWorld->v[0].y + fmLocal->v[3].y * fmWorld->v[1].y + fmLocal->v[3].z * fmWorld->v[2].y + fmLocal->v[3].w * fmWorld->v[3].y;

	fmResult.v[0].z = fmLocal->v[0].x * fmWorld->v[0].z + fmLocal->v[0].y * fmWorld->v[1].z + fmLocal->v[0].z * fmWorld->v[2].z + fmLocal->v[0].w * fmWorld->v[3].z;
	fmResult.v[1].z = fmLocal->v[1].x * fmWorld->v[0].z + fmLocal->v[1].y * fmWorld->v[1].z + fmLocal->v[1].z * fmWorld->v[2].z + fmLocal->v[1].w * fmWorld->v[3].z;
	fmResult.v[2].z = fmLocal->v[2].x * fmWorld->v[0].z + fmLocal->v[2].y * fmWorld->v[1].z + fmLocal->v[2].z * fmWorld->v[2].z + fmLocal->v[2].w * fmWorld->v[3].z;
	fmResult.v[3].z = fmLocal->v[3].x * fmWorld->v[0].z + fmLocal->v[3].y * fmWorld->v[1].z + fmLocal->v[3].z * fmWorld->v[2].z + fmLocal->v[3].w * fmWorld->v[3].z;

	fmResult.v[0].w = fmLocal->v[0].x * fmWorld->v[0].w + fmLocal->v[0].y * fmWorld->v[1].w + fmLocal->v[0].z * fmWorld->v[2].w + fmLocal->v[0].w * fmWorld->v[3].w;
	fmResult.v[1].w = fmLocal->v[1].x * fmWorld->v[0].w + fmLocal->v[1].y * fmWorld->v[1].w + fmLocal->v[1].z * fmWorld->v[2].w + fmLocal->v[1].w * fmWorld->v[3].w;
	fmResult.v[2].w = fmLocal->v[2].x * fmWorld->v[0].w + fmLocal->v[2].y * fmWorld->v[1].w + fmLocal->v[2].z * fmWorld->v[2].w + fmLocal->v[2].w * fmWorld->v[3].w;
	fmResult.v[3].w = fmLocal->v[3].x * fmWorld->v[0].w + fmLocal->v[3].y * fmWorld->v[1].w + fmLocal->v[3].z * fmWorld->v[2].w + fmLocal->v[3].w * fmWorld->v[3].w;

	*fmOut = fmResult;
}

// --------------------------------------------------------------------------
/// @brief 単位行列の設定 
// --------------------------------------------------------------------------
void	UnitMatrix( AlMatrix44 * fmOut )
{
	fmOut->v[0].x = 1.0f;fmOut->v[0].y = 0.0f;fmOut->v[0].z = 0.0f;fmOut->v[0].w = 0.0f;
	fmOut->v[1].x = 0.0f;fmOut->v[1].y = 1.0f;fmOut->v[1].z = 0.0f;fmOut->v[1].w = 0.0f;
	fmOut->v[2].x = 0.0f;fmOut->v[2].y = 0.0f;fmOut->v[2].z = 1.0f;fmOut->v[2].w = 0.0f;
	fmOut->v[3].x = 0.0f;fmOut->v[3].y = 0.0f;fmOut->v[3].z = 0.0f;fmOut->v[3].w = 1.0f;
}

// --------------------------------------------------------------------------
/// @brief マトリクスのルックアット 
// --------------------------------------------------------------------------
/// @note 左手系に修正。 
void	LookAtMatrix( AlMatrix44 * mOut , const AlVector3 * vEye , const AlVector3 * vLook , const AlVector3 * vUp )
{
	AlVector3	vView = {0,0,0} , vUP = {0,0,0} , vRight = {0,0,0};
	
	SubVector( &vView , vLook , vEye );
	if( InnerProduct( &vView , &vView ) == 0.0f )
	{
		// 移動マトリクスを返します 
		UnitMatrix( mOut );
		*(AlVector3*)&mOut->v[3] = *vEye;
		return;
	}
	AL_MATH_ASSERT( ( LengthProduct( &vView  ) != 0.0f ) , "LookAtMatrix vView  is Zero\n" );
	Normalize( &vView , &vView );
	OuterProduct( &vRight , vUp , &vView );
	AL_MATH_ASSERT( ( LengthProduct( &vRight ) != 0.0f ) , "LookAtMatrix vRight is Zero\n" );
	Normalize( &vRight , &vRight );
	OuterProduct( &vUP    , &vView , &vRight );
	AL_MATH_ASSERT( ( LengthProduct( &vUP    ) != 0.0f ) , "LookAtMatrix vUP    is Zero\n" );
	Normalize( &vUP    , &vUP );

	UnitMatrix( mOut );
	*(AlVector3*)&mOut->v[0] = vRight;
	*(AlVector3*)&mOut->v[1] = vUP;
	*(AlVector3*)&mOut->v[2] = vView;
	*(AlVector3*)&mOut->v[3] = *vEye;
}

// --------------------------------------------------------------------------
/// @brief 転地行列の作成 
// --------------------------------------------------------------------------
void	TransposedMatrix( AlMatrix44 * fmOut , const AlMatrix44 * fmIn )
{
	AlMatrix44 fmResult;

	// 転地 
	for( int i = 0 ; i < 4 ; ++ i )
	{
		fmResult.v[i].x = fmIn->v[0].m[i];
		fmResult.v[i].y = fmIn->v[1].m[i];
		fmResult.v[i].z = fmIn->v[2].m[i];
		fmResult.v[i].w = fmIn->v[3].m[i];
	}
	*fmOut = fmResult;
}

// --------------------------------------------------------------------------
// 普通の（単位直交じゃない）３次元行列の逆行列
// --------------------------------------------------------------------------
// In  : const fMatrix fmIn : 変換前
// Out :                    : アウト 
void InverseMatrix( AlMatrix44 * mOut , const AlMatrix44 * mMat )
{
	AlMatrix44 mResult;
#if 1
	const	AlF32	* m = mMat->m;

	AlF32	calc =	 m[ 0]*m[ 5]*m[10]*m[15] + m[ 0]*m[ 6]*m[11]*m[13] + m[ 0]*m[ 7]*m[ 9]*m[14]
					+m[ 1]*m[ 4]*m[11]*m[14] + m[ 1]*m[ 6]*m[ 8]*m[15] + m[ 1]*m[ 7]*m[10]*m[12]
					+m[ 2]*m[ 4]*m[ 9]*m[15] + m[ 2]*m[ 5]*m[11]*m[12] + m[ 2]*m[ 7]*m[ 8]*m[13]
					+m[ 3]*m[ 4]*m[10]*m[13] + m[ 3]*m[ 5]*m[ 8]*m[14] + m[ 3]*m[ 6]*m[ 9]*m[12]
					-m[ 0]*m[ 5]*m[11]*m[14] - m[ 0]*m[ 6]*m[ 9]*m[15] - m[ 0]*m[ 7]*m[10]*m[13]
					-m[ 1]*m[ 4]*m[10]*m[15] - m[ 1]*m[ 6]*m[11]*m[12] - m[ 1]*m[ 7]*m[ 8]*m[14]
					-m[ 2]*m[ 4]*m[11]*m[13] - m[ 2]*m[ 5]*m[ 8]*m[15] - m[ 2]*m[ 7]*m[ 9]*m[12]
					-m[ 3]*m[ 4]*m[ 9]*m[14] - m[ 3]*m[ 5]*m[10]*m[12] - m[ 3]*m[ 6]*m[ 8]*m[13];

	// 0 割が発生する 
	if( calc == 0.0f )
	{
		// 対処をする 
		calc = (AlF32)AL_EPSILON;
	}
	const AlF32 inv_det = (AlF32)1.0f / calc;

	mResult.m[ 0] = inv_det*(m[5]*m[10]*m[15]+m[6]*m[11]*m[13]+m[7]*m[ 9]*m[14]-m[5]*m[11]*m[14]-m[6]*m[ 9]*m[15]-m[7]*m[10]*m[13]);
	mResult.m[ 1] = inv_det*(m[1]*m[11]*m[14]+m[2]*m[ 9]*m[15]+m[3]*m[10]*m[13]-m[1]*m[10]*m[15]-m[2]*m[11]*m[13]-m[3]*m[ 9]*m[14]);
	mResult.m[ 2] = inv_det*(m[1]*m[ 6]*m[15]+m[2]*m[ 7]*m[13]+m[3]*m[ 5]*m[14]-m[1]*m[ 7]*m[14]-m[2]*m[ 5]*m[15]-m[3]*m[ 6]*m[13]);
	mResult.m[ 3] = inv_det*(m[1]*m[ 7]*m[10]+m[2]*m[ 5]*m[11]+m[3]*m[ 6]*m[ 9]-m[1]*m[ 6]*m[11]-m[2]*m[ 7]*m[ 9]-m[3]*m[ 5]*m[10]);
                                                                                                                           
	mResult.m[ 4] = inv_det*(m[4]*m[11]*m[14]+m[6]*m[ 8]*m[15]+m[7]*m[10]*m[12]-m[4]*m[10]*m[15]-m[6]*m[11]*m[12]-m[7]*m[ 8]*m[14]);
	mResult.m[ 5] = inv_det*(m[0]*m[10]*m[15]+m[2]*m[11]*m[12]+m[3]*m[ 8]*m[14]-m[0]*m[11]*m[14]-m[2]*m[ 8]*m[15]-m[3]*m[10]*m[12]);
	mResult.m[ 6] = inv_det*(m[0]*m[ 7]*m[14]+m[2]*m[ 4]*m[15]+m[3]*m[ 6]*m[12]-m[0]*m[ 6]*m[15]-m[2]*m[ 7]*m[12]-m[3]*m[ 4]*m[14]);
	mResult.m[ 7] = inv_det*(m[0]*m[ 6]*m[11]+m[2]*m[ 7]*m[ 8]+m[3]*m[ 4]*m[10]-m[0]*m[ 7]*m[10]-m[2]*m[ 4]*m[11]-m[3]*m[ 6]*m[ 8]);
                                                                                                                           
	mResult.m[ 8] = inv_det*(m[4]*m[ 9]*m[15]+m[5]*m[11]*m[12]+m[7]*m[ 8]*m[13]-m[4]*m[11]*m[13]-m[5]*m[ 8]*m[15]-m[7]*m[ 9]*m[12]);
	mResult.m[ 9] = inv_det*(m[0]*m[11]*m[13]+m[1]*m[ 8]*m[15]+m[3]*m[ 9]*m[12]-m[0]*m[ 9]*m[15]-m[1]*m[11]*m[12]-m[3]*m[ 8]*m[13]);
	mResult.m[10] = inv_det*(m[0]*m[ 5]*m[15]+m[1]*m[ 7]*m[12]+m[3]*m[ 4]*m[13]-m[0]*m[ 7]*m[13]-m[1]*m[ 4]*m[15]-m[3]*m[ 5]*m[12]);
	mResult.m[11] = inv_det*(m[0]*m[ 7]*m[ 9]+m[1]*m[ 4]*m[11]+m[3]*m[ 5]*m[ 8]-m[0]*m[ 5]*m[11]-m[1]*m[ 7]*m[ 8]-m[3]*m[ 4]*m[ 9]);
                                                                                                                           
	mResult.m[12] = inv_det*(m[4]*m[10]*m[13]+m[5]*m[ 8]*m[14]+m[6]*m[ 9]*m[12]-m[4]*m[ 9]*m[14]-m[5]*m[10]*m[12]-m[6]*m[ 8]*m[13]);
	mResult.m[13] = inv_det*(m[0]*m[ 9]*m[14]+m[1]*m[10]*m[12]+m[2]*m[ 8]*m[13]-m[0]*m[10]*m[13]-m[1]*m[ 8]*m[14]-m[2]*m[ 9]*m[12]);
	mResult.m[14] = inv_det*(m[0]*m[ 6]*m[13]+m[1]*m[ 4]*m[14]+m[2]*m[ 5]*m[12]-m[0]*m[ 5]*m[14]-m[1]*m[ 6]*m[12]-m[2]*m[ 4]*m[13]);
	mResult.m[15] = inv_det*(m[0]*m[ 5]*m[10]+m[1]*m[ 6]*m[ 8]+m[2]*m[ 4]*m[ 9]-m[0]*m[ 6]*m[ 9]-m[1]*m[ 4]*m[10]-m[2]*m[ 5]*m[ 8]);


#else
	float	calc = 1.0f / (						// 行列式の逆数
		mMat->v[0][0] * mMat->v[1][1] * mMat->v[2][2] + 
		mMat->v[0][1] * mMat->v[1][2] * mMat->v[2][0] + 
		mMat->v[0][2] * mMat->v[1][0] * mMat->v[2][1] - 
		mMat->v[0][0] * mMat->v[1][2] * mMat->v[2][1] - 
		mMat->v[0][1] * mMat->v[1][0] * mMat->v[2][2] - 
		mMat->v[0][2] * mMat->v[1][1] * mMat->v[2][0] );

	mResult.v[0][0] = ( mMat->v[1][1] * mMat->v[2][2] - mMat->v[1][2] * mMat->v[2][1] ) * calc;
	mResult.v[0][1] = ( mMat->v[0][2] * mMat->v[2][1] - mMat->v[0][1] * mMat->v[2][2] ) * calc;
	mResult.v[0][2] = ( mMat->v[0][1] * mMat->v[1][2] - mMat->v[0][2] * mMat->v[1][1] ) * calc;
	mResult.v[0][3] = 0.0f;

	mResult.v[1][0] = ( mMat->v[1][2] * mMat->v[2][0] - mMat->v[1][0] * mMat->v[2][2] ) * calc;
	mResult.v[1][1] = ( mMat->v[0][0] * mMat->v[2][2] - mMat->v[0][2] * mMat->v[2][0] ) * calc;
	mResult.v[1][2] = ( mMat->v[0][2] * mMat->v[1][0] - mMat->v[0][0] * mMat->v[1][2] ) * calc;
	mResult.v[1][3] = 0.0f;

	mResult.v[2][0] = ( mMat->v[1][0] * mMat->v[2][1] - mMat->v[1][1] * mMat->v[2][0] ) * calc;
	mResult.v[2][1] = ( mMat->v[0][1] * mMat->v[2][0] - mMat->v[0][0] * mMat->v[2][1] ) * calc;
	mResult.v[2][2] = ( mMat->v[0][0] * mMat->v[1][1] - mMat->v[0][1] * mMat->v[1][0] ) * calc;
	mResult.v[2][3] = 0.0f;

	// 移動値の作成 
	mResult.v[3][0] = -mResult.v[0][0]*mMat->v[3][0] - mResult.v[1][0]*mMat->v[3][1] - mResult.v[2][0]*mMat->v[3][2];
	mResult.v[3][1] = -mResult.v[0][1]*mMat->v[3][0] - mResult.v[1][1]*mMat->v[3][1] - mResult.v[2][1]*mMat->v[3][2];
	mResult.v[3][2] = -mResult.v[0][2]*mMat->v[3][0] - mResult.v[1][2]*mMat->v[3][1] - mResult.v[2][2]*mMat->v[3][2];
	mResult.v[3][3] =  mMat->v[3][3];

#endif 
	*mOut = mResult;

}

// --------------------------------------------------------------------------
/// @brief ベクトルの変換 
// --------------------------------------------------------------------------
void	ApplyMatrix( AlVector3 * fvOut , const AlMatrix44 * fmPose , const AlVector3 * fvIn )
{
	AlVector3	fvResult;

	fvResult.x = fmPose->v[0].x * fvIn->x + fmPose->v[1].x * fvIn->y + fmPose->v[2].x * fvIn->z + fmPose->v[3].x;
	fvResult.y = fmPose->v[0].y * fvIn->x + fmPose->v[1].y * fvIn->y + fmPose->v[2].y * fvIn->z + fmPose->v[3].y;
	fvResult.z = fmPose->v[0].z * fvIn->x + fmPose->v[1].z * fvIn->y + fmPose->v[2].z * fvIn->z + fmPose->v[3].z;

	*fvOut = fvResult;
}

// --------------------------------------------------------------------------
/// @brief ベクトルの変換 
// --------------------------------------------------------------------------
void	ApplyMatrixNrm( AlVector3 * fvOut , const AlMatrix44 * fmPose , const AlVector3 * fvIn )
{
	AlVector3	fvResult;

	fvResult.x = fmPose->v[0].x * fvIn->x + fmPose->v[1].x * fvIn->y + fmPose->v[2].x * fvIn->z;
	fvResult.y = fmPose->v[0].y * fvIn->x + fmPose->v[1].y * fvIn->y + fmPose->v[2].y * fvIn->z;
	fvResult.z = fmPose->v[0].z * fvIn->x + fmPose->v[1].z * fvIn->y + fmPose->v[2].z * fvIn->z;

	*fvOut = fvResult;
}

// --------------------------------------------------------------------------
/// @brief ベクトルの変換 
// --------------------------------------------------------------------------
void	ApplyMatrix( AlVector4 * fvOut , const AlMatrix44 * fmPose , const AlVector4 * fvIn )
{
	AlVector4	fvResult;

	fvResult.x = fmPose->v[0].x * fvIn->x + fmPose->v[1].x * fvIn->y + fmPose->v[2].x * fvIn->z + fmPose->v[3].x * fvIn->w;
	fvResult.y = fmPose->v[0].y * fvIn->x + fmPose->v[1].y * fvIn->y + fmPose->v[2].y * fvIn->z + fmPose->v[3].y * fvIn->w;
	fvResult.z = fmPose->v[0].z * fvIn->x + fmPose->v[1].z * fvIn->y + fmPose->v[2].z * fvIn->z + fmPose->v[3].z * fvIn->w;
	fvResult.w = fmPose->v[0].w * fvIn->x + fmPose->v[1].w * fvIn->y + fmPose->v[2].w * fvIn->z + fmPose->v[3].w * fvIn->w;

	*fvOut = fvResult;
}


// --------------------------------------------------------------------------
/// @brief ベクトルの変換 
// --------------------------------------------------------------------------
void	ApplyMatrix( AlVector4 * fvOut , const AlMatrix44 * fmPose , const AlVector3 * fvIn )
{
	AlVector4	fvResult;

	fvResult.x = fmPose->v[0].x * fvIn->x + fmPose->v[1].x * fvIn->y + fmPose->v[2].x * fvIn->z + fmPose->v[3].x;
	fvResult.y = fmPose->v[0].y * fvIn->x + fmPose->v[1].y * fvIn->y + fmPose->v[2].y * fvIn->z + fmPose->v[3].y;
	fvResult.z = fmPose->v[0].z * fvIn->x + fmPose->v[1].z * fvIn->y + fmPose->v[2].z * fvIn->z + fmPose->v[3].z;
	fvResult.w = fmPose->v[0].w * fvIn->x + fmPose->v[1].w * fvIn->y + fmPose->v[2].w * fvIn->z + fmPose->v[3].w;

	*fvOut = fvResult;
}


// --------------------------------------------------------------------------
/// @brief マトリクスの回転 
// --------------------------------------------------------------------------
void	RotateMatrixX( AlMatrix44 * fmOut , const AlF32 rad )
{
	fmOut->v[0].x =      1.0f;fmOut->v[0].y =      0.0f;fmOut->v[0].z =     0.0f;fmOut->v[0].w = 0.0f;
	fmOut->v[1].x =      0.0f;fmOut->v[1].y =  cos(rad);fmOut->v[1].z = sin(rad);fmOut->v[1].w = 0.0f;
	fmOut->v[2].x =      0.0f;fmOut->v[2].y = -sin(rad);fmOut->v[2].z = cos(rad);fmOut->v[2].w = 0.0f;
	fmOut->v[3].x =      0.0f;fmOut->v[3].y =      0.0f;fmOut->v[3].z =     0.0f;fmOut->v[3].w = 1.0f;
}

// --------------------------------------------------------------------------
/// @brief マトリクスの回転 
// --------------------------------------------------------------------------
void	RotateMatrixY( AlMatrix44 * fmOut , const AlF32 rad )
{
	fmOut->v[0].x =  cos(rad);fmOut->v[0].y =      0.0f;fmOut->v[0].z =-sin(rad);fmOut->v[0].w = 0.0f;
	fmOut->v[1].x =      0.0f;fmOut->v[1].y =      1.0f;fmOut->v[1].z =     0.0f;fmOut->v[1].w = 0.0f;
	fmOut->v[2].x =  sin(rad);fmOut->v[2].y =      0.0f;fmOut->v[2].z = cos(rad);fmOut->v[2].w = 0.0f;
	fmOut->v[3].x =      0.0f;fmOut->v[3].y =      0.0f;fmOut->v[3].z =     0.0f;fmOut->v[3].w = 1.0f;
}

// --------------------------------------------------------------------------
/// @brief マトリクスの回転 
// --------------------------------------------------------------------------
void	RotateMatrixZ( AlMatrix44 * fmOut , const AlF32 rad )
{
	fmOut->v[0].x =  cos(rad);fmOut->v[0].y =  sin(rad);fmOut->v[0].z =     0.0f;fmOut->v[0].w = 0.0f;
	fmOut->v[1].x = -sin(rad);fmOut->v[1].y =  cos(rad);fmOut->v[1].z =     0.0f;fmOut->v[1].w = 0.0f;
	fmOut->v[2].x =      0.0f;fmOut->v[2].y =      0.0f;fmOut->v[2].z =     1.0f;fmOut->v[2].w = 0.0f;
	fmOut->v[3].x =      0.0f;fmOut->v[3].y =      0.0f;fmOut->v[3].z =     0.0f;fmOut->v[3].w = 1.0f;
}