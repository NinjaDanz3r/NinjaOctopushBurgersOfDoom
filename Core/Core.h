#ifndef __CORE_H__
#define __CORE_H__

/// Core functionality that's shared between \ref editor and \ref game.
/** @defgroup core Core
 * @{
 */

#if defined(_WIN32) || defined(__WIN32__)
#	if defined(CORE_EXPORTS)
#		define  CORE_EXPORT __declspec(dllexport)
#	else
#		define  CORE_EXPORT __declspec(dllimport)
#	endif
#else
#	define CORE_EXPORT
#endif

/** @} */

#endif