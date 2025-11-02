#include "KShell.h"

namespace qk::kernel
{
	void KShell::get_line()
	{
		std::getline(std::cin, m_Command);
	}
	void KShell::flush()
	{
		if (m_Output)
		{
			(*m_Output) << std::flush;
		}
	}
}