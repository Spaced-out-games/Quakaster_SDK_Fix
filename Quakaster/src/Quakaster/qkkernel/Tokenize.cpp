#include "Tokenize.h"

namespace qk::kernel
{
	bool is_alpha(char c)
	{
		return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
	}

	bool is_numeric(char c)
	{
		return (c >= '0' && c <= '9');

	}

	bool is_alphanumeric(char c)
	{
		return is_alpha(c) || is_numeric(c);
	}
	bool is_alphanumeric_(char c)
	{
		return is_alpha(c) || is_numeric(c) || c == '_';
	}

	bool is_terminator(char c)
	{
		switch (c)
		{
		case '\0':
		case ';':
		case '|':
		case '>':
			return 1;

		default:
			return 0;
		}
	}

	bool is_whitespace(char c)
	{
		return c == ' ' || c == '\t';
	}

	bool is_option_char(char c)
	{
		return c == '-' || c == '+';
	}

	void select_whitespace(const std::string& source, size_t& current_index)
	{
		assert(is_whitespace(source[current_index]));
		size_t offset = current_index;
		while (offset < source.size() && is_whitespace(source.at(offset))) offset++;
		current_index = offset;
		assert(!is_whitespace(source[current_index]));
	}
	std::optional<Token> select_var(const std::string& source, size_t& current_index)
	{
		assert(source[current_index] == '$');
		current_index++; // skip '$'
		size_t start = current_index;

		while (current_index < source.size() && (is_alpha(source[current_index]) || source[current_index] == '_'))
			++current_index;
		std::string var_name(source.data() + start, current_index - start);

		if (start == current_index)
			return std::nullopt; // no valid identifier
		id::add(var_name);
		return IdentifierToken(entt::hashed_string(var_name.c_str()));
	}

	std::optional<Token> select_identifier(const std::string& source, size_t& current_index)
	{
		if (!(is_alpha(source[current_index]) || source[current_index] == '_'))
			return std::nullopt;

		size_t offset = current_index + 1;
		while (offset < source.size() && is_alphanumeric_(source[offset]))
			++offset;
		size_t old = current_index;
		current_index = offset;
		std::string id_name(source.data() + old, offset - old);

		return CommandToken( entt::hashed_string(id_name.c_str()) );
	}

	std::optional<Token> select_number(const std::string& source, size_t& current_index)
	{
		if (!is_numeric(source[current_index]))
			return std::nullopt;

		size_t offset = current_index;
		bool decimal = false;

		while (offset < source.size() && (is_numeric(source[offset]) || (!decimal && source[offset] == '.')))
		{
			if (source[offset] == '.')
				decimal = true;
			offset++;
		}
		std::string str(source.data() + current_index, offset - current_index);




		current_index = offset;

		if (decimal)
		{
			return FloatToken{ (float)atof(str.c_str()) };
		}
		else
		{
			return IntToken{ atoi(str.c_str()) };
		}
	}

	std::optional<Token> select_string(const std::string& source, size_t& current_index)
	{
		if (current_index >= source.size())
			return std::nullopt;

		char closing_char = source[current_index];
		if (closing_char != '"' && closing_char != '\'')
			return std::nullopt;

		size_t offset = current_index + 1;
		while (offset < source.size() && source[offset] != closing_char)
			offset++;

		if (offset >= source.size())
			return std::nullopt; // unterminated string

		std::string string_src(source.data() + current_index + 1, offset - current_index - 1);

		// no need to copy
		StringToken string(std::move(string_src));
		current_index = offset + 1;
		return string;
	}

	std::optional<Token> select_option(const std::string& source, size_t& current_index)
	{
		bool flag = true;
		if (!is_option_char(source[current_index]))
			return std::nullopt;
		current_index++;
		if (is_option_char(source[current_index]))
		{
			flag = false;
			current_index++;
		}
		size_t offset = current_index;
		
		while (is_alpha(source[current_index])) current_index++;

		std::string selected(source.data() + offset, current_index - offset);
		
		if (flag)
			return FlagToken( std::move(selected) );
		else
			return OptionToken( std::move(selected) );
	}

	Program tokenize(const std::string& src)
	{

		// just an alias
		size_t index = 0;
		size_t length = src.length();
		Program result;
		while (index < length)
		{
			if (is_whitespace(src[index]))
				select_whitespace(src, index);

			else if (is_alpha(src[index]))
			{
				if (auto t = select_identifier(src, index))
					result.push_back(*t);

			}
			else if (src[index] == '$')
			{
				if (auto t = select_var(src, index))
					result.push_back(*t);
			}
			else if (is_numeric(src[index]))
			{
				if (auto t = select_number(src, index))
					result.push_back(*t);
			}
			else if (is_option_char(src[index]))
			{
				if (auto t = select_option(src, index))
					result.push_back(*t);
			}
			else if (src[index] == '"')
			{
				if (auto t = select_string(src, index))
					result.push_back(*t);
				else
				{
					// an error has occured, so throw an error token (not implemented) and advance
					index++;
				}
			}
			else if (src[index] == '\'')
			{
				if (auto t = select_string(src, index))
					result.push_back(*t);
			}
			else if (src[index] == '|')
			{
				result.emplace_back('|');
				index++;
			}
			else if (src[index] == '>' || src[index] == '<')
			{
				result.emplace_back(src[index]);
				index++;
			}
			else if (src[index] == ';')
			{
				result.emplace_back(src[index]);
				index++;
			}



			else
			{
				result.emplace_back(src[index]);
				index++;
			}
			//index++;
		}
		if (result.empty() || !result[result.size() - 1].is<TerminatorToken>())
			result.push_back(TerminatorToken{});
		return result;
	}
}