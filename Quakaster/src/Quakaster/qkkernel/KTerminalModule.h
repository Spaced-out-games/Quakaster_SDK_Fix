#pragma once
#include "../Core.h"
#include "KModuleBase.h"

namespace qk::kernel
{
	int clear_cmd(Kernel& kernel, std::span<const Token> args);
	int echo_cmd(Kernel& kernel, std::span<const Token> args);

	struct QK_API KTerminalModule: KModuleBase
	{
		bool mount(Kernel& kernel) override;
		bool unmount(Kernel& kernel) override;
		KTerminalModule(std::string name, SSID id);
	};
}