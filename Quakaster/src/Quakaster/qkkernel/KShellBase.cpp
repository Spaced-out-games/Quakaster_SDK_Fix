#include "KShellBase.h"
#include "kernel.h"


namespace qk::kernel
{

	KShellBase::KShellBase()
	{

	}
	KShellBase::~KShellBase()
	{
		if (m_Kernel)
		{
			m_Kernel->m_Shell = nullptr;
		}
	}

	int KShellBase::execute()
	{
		
		if (m_Kernel)
		{
			auto tokens = tokenize(m_Command);
			return m_Kernel->run_program(tokens);
		}
		return 1;
	}

	// Headless mode doesn't get a line, it has to be fed in manually
	void KShellBase::get_line()
	{

	}

	// Headless mode's got nothing to flush.
	void KShellBase::flush()
	{

	}

	void KShellBase::print(const std::string& message)
	{
		if (m_Output)
		{
			(*m_Output) << message;
		}
	}


	int KShellBase::tick()
	{

		print_path();
		// first, get the string
		get_line();

		// execute it
		int status = execute();
		m_Command = "";
		// show it
		flush();

		// return status
		return status;
	}

	inline void KShellBase::print_path()
	{
		if (m_Kernel)
		{
			print(m_Kernel->m_Cd + "> ");
		}
	}

	void bind(Kernel& kernel, KShellBase& shell, std::ostream& os)
	{
		// Tell the kernel where the shell is
		kernel.m_Shell = &shell;

		// Tell the shell where the kernel is
		shell.m_Kernel = &kernel;

		// tell the shell where the ostream is
		shell.m_Output = &os;
	}

	

}