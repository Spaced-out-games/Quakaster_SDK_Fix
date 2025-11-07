#pragma once
#include "../Core.h"
#include "KModuleBase.h"

namespace qk::kernel
{
	int clear_cmd(Kernel& kernel, std::span<const Token> args);
	int echo_cmd(Kernel& kernel, std::span<const Token> args);
	int printenv_cmd(Kernel& kernel, std::span<const Token> args);
	int typeof_cmd(Kernel& kernel, std::span<const Token> args);
	int wc_cmd(Kernel& kernel, std::span<const Token> args);
	int compile_cmd(Kernel& kernel, std::span<const Token> args);
	int cd_cmd(Kernel& kernel, std::span<const Token> args);
	int exit_cmd(Kernel& kernel, std::span<const Token> args);

	struct QK_API KBuiltinModule: KModuleBase
	{
		bool mount(Kernel& kernel) override;
		bool unmount(Kernel& kernel) override;
		KBuiltinModule(std::string name, SSID id);
	};
}