#pragma once
#include "ETokenType.h"
#include "kernel_token.h"
#include "kernel_token_view.h"
#include "kernel_token_list.h"
#include "../Core.h"


namespace qk::kernel
{
	struct QK_API Program
	{
		TokenList tokens;
		std::vector<TokenView> token_views;
		
	};
}