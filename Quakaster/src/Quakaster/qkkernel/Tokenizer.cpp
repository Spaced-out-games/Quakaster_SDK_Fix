#include "Tokenizer.h"


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

	std::string_view select_whitespace(const std::string& source, size_t& current_index)
	{
		assert(is_whitespace(source[current_index]));

		size_t offset = current_index;
		while (offset < source.size() && is_whitespace(source.at(offset))) offset++;
		std::string_view result(source.data() + current_index, offset - current_index);
		current_index = offset;

		assert(is_whitespace(result.at(result.size() - 1)));
		if (current_index < source.size())
			assert(!is_whitespace(source[current_index]));

		return result;

	}

	std::string_view select_identifier(const std::string& source, size_t& current_index)
	{
		assert(is_alpha(source[current_index]) || source[current_index] == '_');
		size_t offset = current_index + 1;
		while (offset < source.size() && is_alphanumeric_(source[offset])) 
			offset++;
		std::string_view result(source.data() + current_index, offset - current_index);
		current_index = offset;
		assert(is_alphanumeric_(result[result.size() - 1]));
		if (current_index < source.size())
			assert(!is_alphanumeric_(source[current_index]));
		return result;

	}

	std::string_view select_number(const std::string& source, size_t& current_index)
	{
		size_t offset = current_index;
		assert(is_numeric(source[offset]));
		bool decimal = false;
		while (offset < source.size() && (is_numeric(source[offset]) || (!decimal && source[offset] == '.')))
		{
			if (source[offset] == '.')
				decimal = true;
			offset++;
		}
		std::string_view result(source.data() + current_index, offset - current_index);
		current_index = offset;
		assert(is_numeric(result[result.size() - 1]));
		assert(!is_numeric(source[current_index]));
		return result;


	}


	std::string_view select_path(const std::string& source, size_t& current_index)
	{
		return {};

	}

	Token select_option(const std::string& source, size_t& current_index)
	{
		size_t offset = current_index;
		char first = source[offset];
		assert(is_option_char(first));

		ETokenType type = ETokenType::SHORT_OPTION;
		offset++;

		if (offset < source.size() && source[offset] == first)
		{
			type = ETokenType::LONG_OPTION;
			offset++;
		}

		while (offset < source.size() && is_alphanumeric_(source[offset]))
			++offset;

		Token t{ std::string_view{source.data() + current_index, offset - current_index}, type };
		current_index = offset;
		return t;
	}

	std::vector<Token> tokenize(const std::string& src)
	{
		// just an alias
		std::vector<Token> result;
		size_t index = 0;
		size_t length = src.length();
		while (index < length)
		{
			if (is_whitespace(src[index]))
				select_whitespace(src, index);
			else if (is_numeric(src[index]))
				result.emplace_back(select_number(src, index), ETokenType::NUMBER);
			else if (is_alphanumeric_(src[index]))
				result.emplace_back(select_identifier(src, index), ETokenType::IDENTIFIER);
			else if (src[index] == '|')
			{
				result.emplace_back(std::string_view{ src.data() + index, 1 }, ETokenType::PIPE);
				index++;
			}
			else if (src[index] == '>' || src[index] == '<')
			{
				result.emplace_back(std::string_view{ src.data() + index, 1 }, ETokenType::REDIRECT);
				index++;
			}
			else if (src[index] == ';')
			{
				result.emplace_back(std::string_view{ src.data() + index, 1 }, ETokenType::EOL);
				index++;
			}
			else if (is_option_char(src[index]))
			{
				result.emplace_back(select_option(src, index));
				index++;
			}
			// else if src[index] == '$'...
			else
			{
				result.emplace_back(std::string_view{ src.data() + index, 1 }, ETokenType::OPERATOR);
				index++;
			}


			
		}
		if(result[result.size() - 1].m_Type != ETokenType::EOL) result.push_back(Token{ .m_Type = ETokenType::EOL });
		return result;
	}

	std::vector<Token> normalize_tokens(const std::vector<Token>& tokens)
	{
		return {};
	}



}