// --------------------------------------------------------------------------
/// @file 
/// @brief éZèpånÉâÉCÉuÉâÉäÅ[ 
// 
// --------------------------------------------------------------------------
#pragma once 

#define		AL_ABS( x )				(( (x) < 0 )?(-(x)):(x))
#define		AL_MIN( x , y )			(( x < y )?(x):(y))
#define		AL_MAX( x , y )			(( x > y )?(x):(y))
#define		AL_CLAMP( x , y , z )	(AL_MIN( AL_MAX(x,y) , z ))

#define		AL_PI					( 3.1415926535897932386f )
#define		AL_PI_MUL_2				( 6.28318530718f )
#define		AL_EPSILON				( 1.192092896e-07F )

#define		AL_MILI2NUMERIC(x)		( (x) / 1000 )
#define		AL_MICRO2MILI(x)		( (x) / 1000 )
#define		AL_MILI2MICRO(x)		( (x) * 1000 )
#define		AL_NUMERIC2MILI(x)		( (x) * 1000 )
#define		AL_NUMERIC2MICRO(x)		( (x) * 1000000 )

#define		AL_DEG2RAD(x)			( ((x) / 180.0f ) * AL_PI )
#define		AL_RAD2DEG(x)			( ((x) * 180.0f ) / AL_PI )


#include	"AlVector2.h"
AlF32		AlSin(AlF32 x);
AlF32		AlASin(AlF32 x);
AlF32		AlCos(AlF32 x);
AlF32		AlACos(AlF32 x);
AlF32		AlSqrt(AlF32 x);
AlF32		AlRand(AlF32 scale);
AlF32		AlRand(AlF32 scale_min, AlF32 scale_max);
AlF32		AlLog(AlF32 x);
AlF32		AlLog(AlF32 x, AlF32 y);
AlF32		AlExp(AlF32 x);