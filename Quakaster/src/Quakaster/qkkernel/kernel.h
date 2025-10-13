#pragma once
#include "../Core.h"
#include "../qk/QKTL.h"
#include "ETokenType.h"
#include "Token.h"
#include "TokenList.h"
#include "TokenView.h"
#include "Tokenizer.h"
#include "Compile.h"
#include <unordered_map>
#include <entt/core/hashed_string.hpp>



namespace qk::kernel
{
	struct Kernel;

	using Kernel_pfn = int (*)(Kernel& k, const TokenView& args);


	struct QK_API Kernel
	{
		int m_Status = 0;

		//TODO: Make it secure, add hidden environment variables, etc
		std::unordered_map<entt::id_type, std::string> m_Env;
		std::unordered_map<entt::id_type, Kernel_pfn> m_KernelFunctable;
		std::string m_Cwd = "~/";
		std::string m_stdin = "";
		std::string m_stdout = "";
		Kernel();
		void ready();
		void register_fn(std::string name, Kernel_pfn kernel_fn);
		template <class T>
		void print(const T& item)
		{
			m_stdout += item;
		}

		template <>
		void print<int>(const int& item)
		{
			m_stdout += std::to_string(item);
		}


		int run(const TokenView& command);

		int run(Program* program);

		std::string getenv(std::string name);
		void setenv(std::string name, std::string contents);

	};

	
}