#pragma once

// Defines the DLL API

#ifdef QK_BUILD_DLL
	#define QK_API __declspec(dllexport)
#else
	#define QK_API __declspec(dllimport)
#endif

namespace qk {
	QK_API bool init();
}