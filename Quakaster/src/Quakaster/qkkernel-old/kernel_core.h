#pragma once
#include "../Core.h"
#include "Kernel.h"
#include "ETokenType.h"
#include "kernel_token_view.h"
#include <fstream>
#include <sstream>



namespace qk::kernel::core
{

	int pwd(Kernel& kernel, const TokenView& args);
	int cd(Kernel& kernel, const TokenView& args);
	int echo(Kernel& kernel, const TokenView& args);
	int clear(Kernel& kernel, const TokenView& args);
	int wc(Kernel& kernel, const TokenView& args);
	int exit(Kernel& kernel, const TokenView& args);
	int wf(Kernel& kernel, const TokenView& args);
	int cat(Kernel& kernel, const TokenView& args);
	int set(Kernel& kernel, const TokenView& args);
	int run(Kernel& kernel, const TokenView& view);
	int ps(Kernel& kernel, const TokenView& args);


}