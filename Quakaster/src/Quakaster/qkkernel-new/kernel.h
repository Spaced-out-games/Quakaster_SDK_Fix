#pragma once
#include "../Core.h"
#include "Token.h"
#include <initializer_list>
#include <unordered_map>
#include <span>
#include <sstream>


namespace qk::kernel
{

	struct Kernel;

	using Kernel_pfn = int (*)(Kernel& k, std::span<const Token> args);

	struct QK_API Kernel
	{

		// console output buffer
		std::stringstream m_Console;


		// kernel status code
		int m_Status = 0;

		bool last_anchor_was_pipe = false;

		// input token
		Token m_stdin;

		// output token
		Token m_stdout;

		// environment variables
		std::unordered_map<entt::id_type, Token> m_Env;

		// function table
		std::unordered_map<entt::id_type, Kernel_pfn> m_FuncTable;
		Kernel() = default;

		// register a function
		void register_fn(entt::hashed_string name, Kernel_pfn kernel_fn);
		int run_program(std::span<const Token> program);
		int run_program(const Program& program);

		template<typename... Ts>
		int run_inline(Ts&&... args) {
			Token arr[] = { std::forward<Ts>(args)... };
			return run_program(std::span<const Token>(arr));
		}

		// Actually commit a token to the console output
		void print(const Token& token);
		// stdprint
		void print(const std::string& content);


		// Swaps stdin and stdout, clears stdout
		void pipe();

		// Gets an environment variable, safely.
		const Token& get_env(entt::id_type hash_key) const;


		inline operator std::stringbuf* () const;

	};
}