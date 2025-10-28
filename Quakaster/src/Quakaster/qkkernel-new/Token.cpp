#include "Token.h"
#include "kernel.h"

namespace qk::kernel
{
	Token::operator std::string() const
	{
		if (is<NullToken>()) return "<null>";
		if (is<CommandToken>()) return as<CommandToken>().data();
		if (is<IdentifierToken>()) return as<IdentifierToken>().data();
		if (is<FloatToken>()) return std::to_string(as<FloatToken>());
		if (is<IntToken>()) return std::to_string(as<IntToken>());
		if (is<OptionToken>()) return as<OptionToken>();
		if (is<StringToken>()) return as<StringToken>();
		if (is<PipeToken>()) return "|";
		if (is<TerminatorToken>()) return ";";
		if (is<FlagToken>()) return ""; // invisible by design
		else if (is<Program>())
		{
			uintptr_t ptr = (uintptr_t)(as<Program>().data());
			return std::format("0x{:X}", ptr);
		}
		return "<?>"; // fallback for unexpected states
	}
	bool Token::empty() const
	{
		return is<NullToken>();
	}
	Token::Token(char c)
	{
		if (c == '|')
		{
			*this = PipeToken{};
		}
		else if (c == ';')
		{
			*this = TerminatorToken{};
		}
	}
	const Token& Token::resolve(const Kernel& kernel) const
	{
		static StringToken empty{ "empty" };
		if (is<IdentifierToken>())
		{
			entt::id_type hash = as<IdentifierToken>().value();

			if (kernel.m_Env.find(hash) != kernel.m_Env.end())
				return kernel.m_Env.at(hash);
			else
			{
				return empty;
			}

		}
		return *this;
	}

	




}