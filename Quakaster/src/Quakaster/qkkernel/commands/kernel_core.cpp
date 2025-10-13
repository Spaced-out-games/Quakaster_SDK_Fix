#include "kernel_core.h"



namespace qk::kernel
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
		
		return 0;
	}
	int exit(Kernel& kernel, const TokenView& view)
	{
		return 0;
	}
	int wf(Kernel& kernel, const TokenView& view)
	{
		return 0;
	}

	
	
	int QK_API cat(Kernel& kernel, const TokenView& view)
	{
		return 0;
	}

	int QK_API set(Kernel& kernel, const TokenView& view)
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
	int QK_API run(Kernel& kernel, const TokenView& view)
	{
		std::string source = kernel.m_stdin;
		auto a = compile(std::move(source));
		return kernel.run(a.get());
	}


}