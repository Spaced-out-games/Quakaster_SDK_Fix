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


// Loads the core types
#include "qk/Application.h"
#include "qk/Layer.h"
#include "qk/QKTL.h"

#include "qknet/Convar.h"


namespace qk {
	extern QK_API int status;
}