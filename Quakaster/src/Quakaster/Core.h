#pragma once
// 
// PURPOSE: Defines the Quakaster API and includes the QK_Core module.



#include <unordered_map>
#include <typeinfo>


// defines Quakaster API and convar macros
#ifdef QK_BUILD_DLL
	#define QK_API __declspec(dllexport)
	#define QK_DECLARE_CONVAR(name) extern QK_API qk::Convar name
	#define QK_DEFINE_CONVAR(name, id, T_ref) QK_API qk::Convar name(id, T_ref)
#else
	#define QK_API __declspec(dllimport)
	#define QK_DECLARE_CONVAR(name) extern QK_API qk::Convar name
	#define QK_DEFINE_CONVAR(name, id, T_ref) qk::Convar name(id, T_ref)
#endif

/*
namespace qk
{
	// Quakaster error codes. Might remove.
	enum class Error : int {
		OKAY,
		SDL_INIT_FAILURE,
		GLEW_INIT_FAILURE,
		WINDOW_CREATE_FAILURE,
		IMGUI_INIT_FAILURE,
		OUT_OF_MEMORY,
		OUT_OF_BOUNDS,


	};
}*/

#define BIT(x) (1 << x)

