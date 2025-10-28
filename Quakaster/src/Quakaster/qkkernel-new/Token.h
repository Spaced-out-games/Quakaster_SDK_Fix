#pragma once
#include "../Core.h"
#include <entt/core/hashed_string.hpp>
#include <variant>
#include <string>
#include <bitset>
#include <ostream>
#include <vector>

namespace qk::kernel
{
	struct QK_API Kernel;

	// Stores nothing
	struct NullToken : std::monostate {};


	// Stores a float
	using FloatToken = float;


	// Stores an int
	using IntToken = int;

	// Stores a command hash
	struct CommandToken : entt::hashed_string {};

	// Stores a command-line option string
	struct OptionToken : std::string {};

	// Stores a string literal
	struct StringToken : std::string {};

	// stores bit flags as a bitset
	struct FlagToken : std::string {};


	struct PipeToken { bool _; };


	struct TerminatorToken { bool _; };
	
	struct Token;

	using Program = std::vector<Token>;
	

	// Stores an identifier hash
	struct IdentifierToken : entt::hashed_string {};

	using Token_variant_t = std::variant<NullToken, IntToken, FloatToken, CommandToken, OptionToken, FlagToken, StringToken, IdentifierToken, TerminatorToken, PipeToken, Program>;

	


	struct QK_API Token : public Token_variant_t
	{
		using Token_variant_t::variant; // inherit all std::variant constructors

		template <class T>
		bool is() const
		{
			return std::holds_alternative<T>(*this);
		}

		template <class T>
		T& as()
		{
			return std::get<T>(*this);
		}

		template <class T>
		const T& as() const
		{
			return std::get<T>(*this);
		}

		operator std::string() const;

		Token(char c);

		const Token& resolve(const Kernel& kernel) const;

		inline bool empty() const;

	};



	inline std::ostream& operator<<(std::ostream& os, const Token& t)
	{
		os << static_cast<std::string>(t);
		return os;
	}

	inline IdentifierToken operator"" _id(const char* str, size_t)
	{
		return IdentifierToken{ entt::hashed_string{str} };
	}

	inline CommandToken operator"" _cmd(const char* str, size_t)
	{
		return CommandToken{ entt::hashed_string{str} };
	}


}