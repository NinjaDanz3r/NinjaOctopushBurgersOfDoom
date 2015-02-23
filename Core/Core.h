#ifndef __CORE_H__
#define __CORE_H__

#if defined(_WIN32) || defined(__WIN32__)
#	if defined(CORE_EXPORTS)
#		define  CORE_EXPORT __declspec(dllexport)
#	else
#		define  CORE_EXPORT __declspec(dllimport)
#	endif
#else
#	define CORE_EXPORT
#endif

#endif