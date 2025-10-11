#pragma once
#include "../../Core.h"
#include "../Kernel.h"
#include "../ETokenType.h"
#include "../TokenView.h"



namespace qk::kernel
{

	int QK_API pwd(Kernel& kernel, const TokenView& view);
	int QK_API cd(Kernel& kernel, const TokenView& view);
	int QK_API echo(Kernel& kernel, const TokenView& view);
	int QK_API clear(Kernel& kernel, const TokenView& view);
	int QK_API wc(Kernel& kernel, const TokenView& view);

}