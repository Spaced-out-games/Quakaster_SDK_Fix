#pragma once
// Defines the DLL API

#if defined(QK_STATIC)
#define QK_API
#elif defined(QK_BUILD_DLL)
#define QK_API __declspec(dllexport)
#else
#define QK_API __declspec(dllimport)
#endif

namespace qk {

	QK_API bool init(int major = 3, int minor = 3);
	QK_API void close();

}