#pragma once
#include "../Core.h"
#include "Token.h"
#include <initializer_list>
#include <unordered_map>
#include <span>
#include <sstream>


namespace qk::kernel
{

	struct ShellBase;
	struct Kernel;

	using Kernel_pfn = int (*)(Kernel& k, std::span<const Token> args);

	class QK_API Kernel_fn
	{
			// The pointer to the implementation
			Kernel_pfn	m_Func = nullptr;

			// The name of the function
			std::string m_Name = "";

		public:
			// Constructor
			Kernel_fn(std::string name, Kernel_pfn func);
			Kernel_fn();

			const std::string& name() const;


			// helper function
			int operator()(Kernel& k, std::span<const Token> args);



	};


	/// <summary>
	/// Defines a kernel - like interface by which to manipulate the engine
	/// Comes with tools and infrustructure to tokenize, parse, as well as run
	/// </summary>
	struct QK_API Kernel
	{

		// console output buffer
		//std::stringstream* m_Output = nullptr;
		
		ShellBase* m_Shell = nullptr;

		// kernel status code
		int m_Status = 0;

		std::string m_Cd;

		// whether or not the last consumed token was  pipe
		bool last_anchor_was_pipe = false;

		// input token
		Token m_stdin;

		// output token
		Token m_stdout;

		// environment variables
		std::unordered_map<entt::id_type, Token> m_Env;

		// function table
		std::unordered_map<entt::id_type, Kernel_fn> m_FuncTable;


		Kernel() = default;
		~Kernel();

		// register a function
		void register_fn(std::string name, Kernel_pfn kernel_fn);

		// Runs a program built from the commandline
		int run_program(std::span<const Token> program);
		int run_program(const Program& program);

		// Runs a program built manually in-source
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


	};
}