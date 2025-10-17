#pragma once
#include <string>
#include <vector>
#include "kernel_token.h"
#include "../Core.h"


namespace qk::kernel
{
	struct QK_API TokenList
	{
		std::string source;
		std::vector<Token> tokens;
	};
}