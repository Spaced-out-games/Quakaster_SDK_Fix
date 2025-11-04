#pragma once
#include "../Core.h"
#include <chrono>
#include <string>
#include "kernel.h"
using namespace std::chrono;
namespace qk::kernel
{
	

	/// <summary>
	/// Represents a module you can attach to a kernel
	/// </summary>
	struct QK_API KModuleBase
	{
		std::string m_Name;
		time_point<steady_clock>		m_StartTime;
		SSID							m_ProcessID;

		// gets the uptime of this module
		std::chrono::milliseconds uptime() const;
		virtual bool mount(Kernel& kernel) = 0;
		virtual bool unmount(Kernel& kernel) = 0;
		KModuleBase(std::string name, SSID id);
		~KModuleBase() = default;
	};
}