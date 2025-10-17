#pragma once
#include "../Core.h"
#include "../qk/QKTL.h"
#include "ETokenType.h"
#include "kernel_token.h"
#include "kernel_token_list.h"
#include "kernel_token_view.h"
#include "kernel_tokenizer.h"
#include "kernel_compile.h"
#include <unordered_map>
#include <entt/core/hashed_string.hpp>
#include "kernel_subsystem.h"



namespace qk::kernel
{
	struct Kernel;

	using Kernel_pfn = int (*)(Kernel& k, const TokenView& args);

	struct QK_API Kernel
	{
		int m_Status = 0;
		int m_Current_pid = 0;
		//TODO: Make it secure, add hidden environment variables, etc
		std::unordered_map<entt::id_type, std::string> m_Env;
		std::unordered_map<entt::id_type, Kernel_pfn> m_KernelFunctable;
		std::unordered_map<std::string, Subsystem*> m_Subsystems;
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

		template <class T, class ...Args>
		void mount(std::string name, Args&&... args)
		{
			static_assert(std::is_base_of_v<Subsystem, T>, "T is not derivative of Subsystem");
			m_Subsystems[name] = new T(m_Current_pid++, std::forward<Args>(args)...);
			m_Subsystems[name]->mount(*this);
		}

	};

	
}