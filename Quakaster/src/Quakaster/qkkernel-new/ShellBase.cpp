#include "ShellBase.h"
#include "kernel.h"


namespace qk::kernel
{

	ShellBase::ShellBase()
	{

	}
	ShellBase::~ShellBase()
	{
		if (m_Kernel)
		{
			m_Kernel->m_Shell = nullptr;
		}
	}

	int ShellBase::execute()
	{
		
		if (m_Kernel)
		{
			auto tokens = tokenize(m_Command);
			return m_Kernel->run_program(tokens);
		}
		return 1;
	}

	// Headless mode doesn't get a line, it has to be fed in manually
	void ShellBase::get_line()
	{

	}

	// Headless mode's got nothing to flush.
	void ShellBase::flush()
	{

	}

	void ShellBase::print(const std::string& message)
	{
		if (m_Output)
		{
			(*m_Output) << message;
		}
	}


	int ShellBase::tick()
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

	inline void ShellBase::print_path()
	{
		if (m_Kernel)
		{
			print(m_Kernel->m_Cd + "> ");
		}
	}

	void bind(Kernel& kernel, ShellBase& shell, std::ostream& os)
	{
		// Tell the kernel where the shell is
		kernel.m_Shell = &shell;

		// Tell the shell where the kernel is
		shell.m_Kernel = &kernel;

		// tell the shell where the ostream is
		shell.m_Output = &os;
	}

	

}