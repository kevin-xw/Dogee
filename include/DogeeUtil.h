#ifndef __DOGEE_UTIL_H_
#define __DOGEE_UTIL_H_
#include <string.h>
namespace Dogee
{

#ifdef _MSC_VER

#ifndef _WIN64
#define _BreakPoint __asm int 3
#else
	typedef void(__stdcall *ptDbgBreakPoint)(void);
extern ptDbgBreakPoint _DbgBreakPoint;
#define _BreakPoint _DbgBreakPoint();
#endif
#else
#define _BreakPoint __asm__("int $3");
#endif

	template <class Dest, class Source>
	inline Dest trunc_cast(const Source source) {
		static_assert(sizeof(Dest) <= sizeof(Source), "Error: sizeof(Dest) > sizeof(Source)");
		//Dest dest;
		//memcpy(&dest, &source, sizeof(dest));
		return *reinterpret_cast<const Dest*>(&source);
	}

	template <class Dest, class Source>
	inline Dest bit_cast(const Source source) {
		static_assert(sizeof(Dest) >= sizeof(Source), "Error: sizeof(Dest) < sizeof(Source)");
		Dest dest;
		if (sizeof(Dest) > sizeof(Source)) //this is a static branch
			dest = 0;
		Source src=source;
		memcpy(&dest, &src, sizeof(dest));
		return dest;
	}

}

#endif