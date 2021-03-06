#pragma once

#ifdef SAZ_PLATFORM_WINDOWS
	#if SAZ_DYNAMIC_LINK
		#ifdef SAZ_BUILD_DLL
			#define SAZ_API __declspec(dllexport)
		#else
			#define SAZ_API __declspec(dllimport)
	#endif
#else
	#define SAZ_API
#endif
#else
	#error Saz only supports Windows!
#endif

#ifdef SAZ_DEBUG
	#ifndef SAZ_ENABLE_ASSERTS
		#define SAZ_ENABLE_ASSERTS
	#endif
#endif

#ifdef SAZ_ENABLE_ASSERTS
	#define SAZ_ASSERT(x, ...) { if(!(x)) { SAZ_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define SAZ_CORE_ASSERT(x, ...) { if(!(x)) { SAZ_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define SAZ_ASSERT(x, ...)
	#define SAZ_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)