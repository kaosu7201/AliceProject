
#pragma once
#include	"AlPrototype.h"
class		AlColor4;
#include	"AlVector4.h"

// --------------------------------------------------------------------------
/// @brief êFèÓïÒä«óùÉNÉâÉX 
// --------------------------------------------------------------------------
class	AlColor4
{
public:
  union
  {
    AlVector4	m;
    struct
    {
      AlF32	r, g, b, a;
    };
  };
  void		Set(AlF32 x_, AlF32 y_, AlF32 z_, AlF32 w_);
  AlU32		GetRGBAU32() const;
  inline	AlF32	&operator [] (const AlU32 id) { return m[id]; }
  inline	AlF32	operator  [] (const AlU32 id) const { return m[id]; }
};