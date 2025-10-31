#include "stdshell.h"

namespace qk::kernel
{
	void Shell::get_line()
	{
		std::getline(std::cin, m_Command);
	}
	void Shell::flush()
	{
		if (m_Output)
		{
			(*m_Output) << std::flush;
		}
	}
}