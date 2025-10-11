#pragma once
#include "ETokenType.h"
#include "Token.h"
#include "TokenView.h"
#include "TokenList.h"
#include "../Core.h"


namespace qk::kernel
{
	struct QK_API Program
	{
		TokenList tokens;
		std::vector<TokenView> token_views;
		
	};
}