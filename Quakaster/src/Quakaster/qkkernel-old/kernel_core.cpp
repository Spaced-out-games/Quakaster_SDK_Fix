#include "kernel_core.h"



namespace qk::kernel::core
{
	int pwd(Kernel& kernel, const TokenView& view)
	{
		kernel.m_stdout += kernel.m_Cwd;
		return 0;
	}
	int cd(Kernel& kernel, const TokenView& view)
	{
		
		return 0;
	}

	int echo(Kernel& kernel, const TokenView& view)
	{
		for (const auto& token: view)
		{
			if (token.is<int>())
			{
				kernel.print(token.as<int>());
			}
			else if (token.is<std::string_view>() && token.m_Type == ETokenType::STRING_LITERAL_DQ)
			{
				kernel.print(token.strip_quotes());
			}
			else if (token.is<std::string_view>() && token.m_Type == ETokenType::VARIABLE_REFERENCE)
			{
				kernel.print(kernel.getenv(std::string( token.as<std::string_view>() ) ));
			}
		}
		return 0;
	}
	int clear(Kernel& kernel, const TokenView& view)
	{
		std::cout << "\033[2J\033[1;1H";
		return 0;
	}

	int wc(Kernel& kernel, const TokenView& view)
	{
		bool show_chars = false;
		bool show_words = false;
		bool show_lines = false;

		// If no flags, show all
		if (view.size() <= 1) {
			show_chars = show_words = show_lines = true;
		}

		// Parse options
		for (const auto& token : view) {
			if (token.m_Type == ETokenType::SHORT_OPTION) {
				std::string_view opt = token.as<std::string_view>();
				if (opt.find('c') != std::string_view::npos) show_chars = true;
				if (opt.find('w') != std::string_view::npos) show_words = true;
				if (opt.find('l') != std::string_view::npos) show_lines = true;
			}
		}

		size_t lines = 0;
		size_t words = 0;
		size_t bytes = 0;

		std::stringstream stream(kernel.m_stdin);
		std::string line;

		while (std::getline(stream, line)) {
			lines++;
			bytes += line.size() + 1; // +1 for newline

			bool in_word = false;
			for (char c : line) {
				if (is_whitespace(c)) {
					in_word = false;
				}
				else {
					if (!in_word) ++words;
					in_word = true;
				}
			}
		}

		// adjust byte count if last line has no newline
		if (!kernel.m_stdin.empty() && kernel.m_stdin.back() != '\n')
			bytes -= 1;

		// build formatted output
		std::string output;
		if (show_lines) output += std::to_string(lines) + " ";
		if (show_words) output += std::to_string(words) + " ";
		if (show_chars) output += std::to_string(bytes);
		if (!output.empty() && output.back() == ' ') output.pop_back();

		kernel.print(output + "\n");
		return 0;
	}
	int exit(Kernel& kernel, const TokenView& view)
	{
		if (view.size()>=2 && view[1].m_Type == ETokenType::INT)
		{
			kernel.m_Status = view[1].as<int>();
		}
		else
		{
			// generic error code.
			kernel.m_Status = 1;
		}
		return 0;
	}
	int wf(Kernel& kernel, const TokenView& view)
	{
		return 0;
	}

	
	
	int cat(Kernel& kernel, const TokenView& view)
	{
		return 0;
	}

	int set(Kernel& kernel, const TokenView& view)
	{
		std::string target;
		std::string new_value = kernel.m_stdin;
		for (const auto& token : view)
		{
			if (token.is<int>())
			{
				new_value = std::to_string(token.as<int>());
			}
			else if (token.is<std::string_view>() && token.m_Type == ETokenType::STRING_LITERAL_DQ)
			{
				new_value = token.strip_quotes();
			}
			else if (token.is<std::string_view>() && token.m_Type == ETokenType::IDENTIFIER)
			{
				target = token.as<std::string_view>();
			}
		}
		kernel.setenv(target, new_value);

		return 0;
	}
	int run(Kernel& kernel, const TokenView& view)
	{

		std::string source;
		if (view.size() > 1)
		{


			if (view[1].m_Type == ETokenType::STRING_LITERAL_DQ)
			{
				source = view[1].strip_quotes();
			}
			else if (view[1].m_Type == ETokenType::VARIABLE_REFERENCE)
			{
				source = kernel.getenv(std::string(view[1].as<std::string_view>()));
			}
			else
			{

			}
		}

		if(source.empty())
			source = kernel.m_stdin;
		
		auto a = compile(std::move(source));
		return kernel.run(a.get());
	}

	int ps(Kernel& kernel, const TokenView& args)
	{
		kernel.print("PID\tName\tUptime\tCurrent Task\n");

		for (auto& [name, subsystem_ptr] : kernel.m_Subsystems)
		{
			kernel.print(std::to_string(subsystem_ptr->pid) + "\t");
			kernel.print(name + "\t");

			auto up = std::chrono::duration_cast<std::chrono::seconds>(subsystem_ptr->uptime()).count();
			kernel.print(std::to_string(up) + "s\t");

			kernel.print(subsystem_ptr->current_task() + "\n");
		}

		return 0;
	}


}