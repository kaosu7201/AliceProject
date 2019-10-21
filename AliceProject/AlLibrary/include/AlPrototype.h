#pragma once
#include <stdio.h>
// --------------------------------------------------------------------------
// 型定義 
// --------------------------------------------------------------------------
typedef		int				AlBool;		///< 成否判定 

typedef		signed char		AlS8;		///< 符号付き 1Byte 
typedef		short			AlS16;		///< 符号付き 2Byte 
typedef		int				AlS32;		///< 符号付き 4Byte 

typedef		unsigned char	AlU8;		///< 符号無し 1Byte 
typedef		unsigned short	AlU16;		///< 符号無し 1Byte 
typedef		unsigned int	AlU32;		///< 符号無し 1Byte 

typedef		long			AlSLong;	///< 可変長なので構造体に入れないで 
typedef		unsigned long	AlULong;	///< 可変長なので構造体に入れないで 

typedef		float			AlF32;		///< 浮動小数 4Byte 
typedef		double			AlF64;		///< 浮動小数 8Byte 

#define		AL_TRUE			( 1 )
#define		AL_FALSE		( 0 )