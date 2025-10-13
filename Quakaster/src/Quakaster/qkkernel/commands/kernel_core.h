#pragma once
#include "../../Core.h"
#include "../Kernel.h"
#include "../ETokenType.h"
#include "../TokenView.h"
#include <fstream>
#include <sstream>



namespace qk::kernel
{

	int QK_API pwd(Kernel& kernel, const TokenView& args);
	int QK_API cd(Kernel& kernel, const TokenView& args);
	int QK_API echo(Kernel& kernel, const TokenView& args);
	int QK_API clear(Kernel& kernel, const TokenView& args);
	int QK_API wc(Kernel& kernel, const TokenView& args);
	int QK_API exit(Kernel& kernel, const TokenView& args);
	int QK_API wf(Kernel& kernel, const TokenView& args);
	int QK_API cat(Kernel& kernel, const TokenView& args);
	int QK_API set(Kernel& kernel, const TokenView& args);
	int QK_API run(Kernel& kernel, const TokenView& view);


}