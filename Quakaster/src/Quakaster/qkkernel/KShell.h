#pragma once
#include "../Core.h"
#include "KShellBase.h"
#include <iostream>

namespace qk::kernel
{
	struct QK_API KShell : KShellBase
	{
		void get_line() override;
		void flush() override;
	};
}