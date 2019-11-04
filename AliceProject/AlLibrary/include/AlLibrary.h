// --------------------------------------------------------------------------
/// @file 
/// @brief AlLibrary 用 Include 
// 
// --------------------------------------------------------------------------
#pragma once 
#include	<stdio.h>
#include	<stdlib.h>
#include	<vector>
#include	<list>
#include	<map>
#include	<string>
#include	<algorithm>

using namespace std;

/// 色指定マクロ 
#define		AL_RGB(  x,y,z )			(( (x) & 0x0ff ) | (( (y) & 0x0ff )<<8) | (( (z) & 0x0ff )<<16) | 0x0ff000000 )
#define		AL_RGBA( x,y,z,w )			(( (x) & 0x0ff ) | (( (y) & 0x0ff )<<8) | (( (z) & 0x0ff )<<16) | (( (w) & 0x0ff )<<24) )