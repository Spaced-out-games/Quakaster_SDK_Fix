#include "KBuiltinModule.h"
#include "KernelIdentifierTable.h"
#include "Tokenize.h"

namespace qk::kernel
{


	bool KBuiltinModule::mount(Kernel& kernel)
	{
		kernel.register_fn("clear", &clear_cmd, "Terminal");
		kernel.register_fn("echo", &echo_cmd, "Terminal");
		kernel.register_fn("printenv", &printenv_cmd, "Terminal");
		kernel.register_fn("compile", &compile_cmd);
		kernel.register_fn("typeof", &typeof_cmd);
		kernel.register_fn("wc", &wc_cmd);
		kernel.register_fn("cd", &cd_cmd);
		kernel.register_fn("exit", &exit_cmd);

		return true;
	}
	bool KBuiltinModule::unmount(Kernel& kernel)
	{
		return true;
	}
	KBuiltinModule::KBuiltinModule(std::string name, SSID id) : KModuleBase(std::move(name), id) {}




	int clear_cmd(Kernel& kernel, std::span<const Token> args)
	{
		kernel.print("\033[2J\033[1;1H");
		return 0;
	}


	int echo_cmd(Kernel& kernel, std::span<const Token> args)
	{
		for (auto& token : args)
		{
			kernel.m_stdout = token;
		}

		return 0;
	}
	int printenv_cmd(Kernel& kernel, std::span<const Token> args)
	{
		StringToken result;
		for (auto& hash_name : id::lut())
		{
			result += '$';
			result += hash_name.second;
			result += ": ";
			result += kernel.m_Env[hash_name.first].print_str();
			result += '\n';
		}
		kernel.m_stdout = result;
		return 0;
	}

	int typeof_cmd(Kernel& kernel, std::span<const Token> args)
	{
		const Token& input = !kernel.m_stdin.empty() ? kernel.m_stdin : (args.empty() ? NullToken{} : args[0]);
		std::string out;

		if (input.is<IntToken>()) out = "<int>";
		else if (input.is<FloatToken>()) out = "<float>";
		else if (input.is<StringToken>()) out = "<string>";
		//else if (input.is<ProgramToken>()) out = "<exec>";
		else if (input.is<IdentifierToken>()) out = input.resolve(kernel).type_str();
		else if (input.is<NullToken>()) out = "<null>";
		else if (input.is<Program>()) out = "<script>";
		else out = "<?>";

		kernel.m_stdout = StringToken{ out };
		kernel.m_stdin = NullToken{};  // clear stdin after use
		return 0;
	}

	int wc_cmd(Kernel& kernel, std::span<const Token> args)
	{
		// early exit
		if (kernel.m_stdin.empty())
		{
			kernel.m_stdout = StringToken{ "0" };
			return 0;
		}


		bool print_cc = false;
		bool print_wc = false;
		bool print_lc = false;
		for (auto& arg : args)
		{
			if (arg.is<FlagToken>())
			{
				if (arg.as<FlagToken>().has('c'))
					print_cc = true;
				if (arg.as<FlagToken>().has('w'))
					print_wc = true;
				if (arg.as<FlagToken>().has('l'))
					print_lc = true;
			}
		}

		// no mutation occured
		if (!print_cc && !print_wc && !print_lc)
		{
			print_cc = 1;
			print_wc = 1;
			print_lc = 1;
		}


		std::string repr = kernel.m_stdin.print_str();

		size_t cc = repr.size();
		size_t wc = 0;
		size_t lc = 1;
		bool in_word = false;

		for (char c : repr)
		{
			if (c == '\n') lc++;
			if (c == ' ' || c == '\t')
				in_word = false;
			else
			{
				if (!in_word)
					wc++;
				in_word = true;
			}
		}

		StringToken out{ "" };

		if (print_cc)
			out += std::to_string(cc) + " ";
		if (print_wc)
			out += std::to_string(wc) + " ";
		if (print_lc)
			out += std::to_string(lc) + " ";
		kernel.m_stdout = out;
		return 0;
	}

	int compile_cmd(Kernel& kernel, std::span<const Token> args)
	{
		if (args.size() == 0)
		{
			kernel.m_stdout = StringToken{ "No arguments provided!" };
		}
		else if (args.size() == 1)
		{
			if (args[0].is<StringToken>())
			{
				// make a string_view; make tokenizer use a string_view
				kernel.m_stdout = qk::kernel::tokenize(args[0].as<StringToken>());
			}
			else
				kernel.m_stdout = StringToken{ "Expected a source string" };

		}
		else
		{
			kernel.m_stdout = StringToken{ "Too many arguments in command 'compile'" };


		}
		return 0;
	}
	int cd_cmd(Kernel& kernel, std::span<const Token> args)
	{
		if (args.size() == 0) return 0;
		if (args.size() == 1)
		{
			if (args[0].is<StringToken>()) kernel.m_Cd += args[0].as<StringToken>();
			if (args[0].is<IdentifierToken>()) kernel.m_Cd += args[0].as<IdentifierToken>().data();

		}
		else if (args.size() > 1)
		{
			kernel.m_stdout = StringToken{ "Too many arguments in command 'echo'" };
		}
		return 0;
	}
	int exit_cmd(Kernel& kernel, std::span<const Token> args)
	{
		exit(1);
	}

	
}