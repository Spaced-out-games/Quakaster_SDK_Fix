#pragma once
#include "../Core.h"
#include "Tokenize.h"
#include <string>
#include <ostream>
#include <functional>



namespace qk::kernel
{
	struct Kernel;
	struct Token;
	
	/// <summary>
	/// Basic shell. Headless.
	/// </summary>
	struct QK_API KShellBase
	{
		KShellBase();
		~KShellBase();

		// Don't forget to bind the kernel to this!!!
		std::ostream* m_Output = nullptr;

		// The kernel youre running from
		Kernel* m_Kernel = nullptr;

		// the command you're running
		std::string m_Command;

		// Awaits a command, assigns m_Command
		virtual void get_line();

		// Flushes the buffer to your display of choice
		virtual void print(const std::string& content);

		virtual void flush();
		
		// Can be overridden by the console.
		virtual void clear();

		inline void print_path();

		// Calls m_Command through the kernel
		int execute();


		// Undergoes one REPL iteration
		inline int tick();


	};

	QK_API void bind(Kernel& kernel, KShellBase& shell, std::ostream& os);

}