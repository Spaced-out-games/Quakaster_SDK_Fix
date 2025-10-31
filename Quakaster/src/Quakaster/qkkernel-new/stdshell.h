#pragma once
#include "../Core.h"
#include "ShellBase.h"
#include <iostream>

namespace qk::kernel
{
	struct QK_API Shell : ShellBase
	{
		void get_line() override;
		void flush() override;
	};
}