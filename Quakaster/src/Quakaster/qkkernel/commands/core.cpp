#include "core.h"



namespace qk::kernel
{
	int pwd(Kernel& kernel, const TokenView& view)
	{
		kernel.m_stdout += kernel.m_Cwd;
		kernel.m_stdout += '\n';
		return 0;
	}
	int cd(Kernel& kernel, const TokenView& view)
	{
		if (view.size() > 1)
		{
			if (view[1].m_Type == ETokenType::IDENTIFIER)
			{
				kernel.m_Cwd += view[1].m_View;
				kernel.m_Cwd += '/';
			}
		}
		return 0;
	}

	int echo(Kernel& kernel, const TokenView& view)
	{
		for (const Token& token : view)
		{
			if (token.m_Type == ETokenType::SHORT_OPTION)
			{
				if (token.m_View.find('t'))
				{
					kernel.m_stdout += "test flag set";
					kernel.m_stdout += '\n';
				}
			}

			if (token.m_Type == ETokenType::IDENTIFIER)
			{
				kernel.m_stdout += token.m_View;
				kernel.m_stdout += '\n';
			}
		}
		return 0;
	}
	int clear(Kernel& kernel, const TokenView& view)
	{
		kernel.m_stdout += "\033[2J\033[1;1H";
		return 0;
	}

	int wc(Kernel& kernel, const TokenView& view)
	{

		bool plc = true;
		bool pwc = true;
		bool pcc = true;
		bool resetted = false;

		for (const Token& token: view)
		{
			if (token.m_Type == ETokenType::SHORT_OPTION)
			{
				if (!resetted)
				{
					plc = false;
					pwc = false;
					pcc = false;
					resetted = true;
				}
				bool type = token.m_View[0] == '+';
				
				if (token.m_View.find('l') != std::string::npos)
					plc = type;
				if (token.m_View.find('w') != std::string::npos)
					pwc = type;
				if (token.m_View.find('c') != std::string::npos)
					pcc = type;
			}
		}
		if (pcc)
		{
			size_t cc = kernel.m_stdin.size();
			kernel.m_stdout += ' ';
			kernel.m_stdout += std::to_string(cc);
		}
		if (pwc)
		{
			kernel.m_stdout += " <noimpl>";
		}
		if (plc)
		{
			kernel.m_stdout += " <noimpl>";
		}
		kernel.m_stdout += '\n';

		return 0;

	}
}