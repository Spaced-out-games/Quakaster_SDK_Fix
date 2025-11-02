#include "Token.h"
#include "kernel.h"

namespace qk::kernel
{


	
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

	// Prints the token, as evaluated
	std::string Token::eval_str(Kernel& kernel) const
	{
		
		if (is<CommandToken>())
			return std::format("command ( hash = {:X} )", as<CommandToken>().value());
		if (is<IdentifierToken>())
			return kernel.get_env(as<IdentifierToken>().value()).print_str();
		if (is<FloatToken>())
			return std::to_string(as<FloatToken>());
		if (is<IntToken>())
			return std::to_string(as<IntToken>());
		if (is<OptionToken>())
			return as<OptionToken>();
		if (is<StringToken>())
			return as<StringToken>();
		if (is<PipeToken>())
			return "";
		if (is<TerminatorToken>())
			return "";
		if (is<NullToken>())
			return "";
		if (is<FlagToken>())
			return ""; // invisible by design
		else if (is<Program>())
		{
			kernel.run_program(as<Program>());
			return kernel.m_stdout.print_str();
		}
		return "<?>"; // fallback for unexpected states
	}

	// Gets the printable representation of the Token. Basically, the literal contents
	std::string Token::print_str() const
	{
		if (is<CommandToken>())
			return std::format("command ( hash = {:X} )", as<CommandToken>().value());
		if (is<IdentifierToken>())
			return std::format("identifier ( hash = {:X} )", as<IdentifierToken>().value());
		if (is<FloatToken>())
			return std::to_string(as<FloatToken>());
		if (is<IntToken>())
			return std::to_string(as<IntToken>());
		if (is<OptionToken>())
			return as<OptionToken>();
		if (is<StringToken>())
			return as<StringToken>();
		if (is<PipeToken>())
			return "|";
		if (is<TerminatorToken>())
			return ";";
		if (is<FlagToken>())
			return ""; // invisible by design
		if (is<NullToken>())
			return "";
		if (is<Program>())
		{
			uintptr_t ptr = (uintptr_t)(as<Program>().data());
			return std::format("0x{:X}", ptr);
		}
		return "<?>"; // fallback for unexpected states
	}

	// gets the token type as a string
	std::string Token::type_str() const
	{
		if (is<NullToken>()) return "<null>";
		if (is<IntToken>()) return "<int>";
		if (is<FloatToken>()) return "<float>";
		if (is<CommandToken>()) return "<command>";
		if (is<OptionToken>()) return "<option>";
		if (is<FlagToken>()) return "<flag>";
		if (is<StringToken>()) return "<string>";
		if (is<IdentifierToken>()) return "<identifier>";
		if (is<TerminatorToken>()) return "<EOL>";
		if (is<PipeToken>()) return "<pipe>";
		if (is<Program>()) return "<script>";
		return "<?>";
	}




}