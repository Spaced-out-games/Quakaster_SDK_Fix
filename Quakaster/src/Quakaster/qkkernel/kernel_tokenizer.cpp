#include "kernel_tokenizer.h"


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


	std::optional<Token> select_var(const std::string& source, size_t& current_index)
	{
		assert(source[current_index] == '$');
		current_index++; // skip '$'
		size_t start = current_index;

		while (current_index < source.size() && (is_alpha(source[current_index]) || source[current_index] == '_'))
			++current_index;

		if (start == current_index)
			return std::nullopt; // no valid identifier

		std::string_view var_name(source.data() + start, current_index - start);
		return Token{ var_name, ETokenType::VARIABLE_REFERENCE };
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
		return Token{ std::string_view(source.data() + old, offset - old), ETokenType::IDENTIFIER };

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
			return Token{ (float)atof(str.c_str()), ETokenType::FLOAT };
		}
		else
		{
			return Token{ atoi(str.c_str()), ETokenType::INT};
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
			++offset;

		if (offset >= source.size())
			return std::nullopt; // unterminated string

		Token t{ std::string_view(source.data() + current_index, offset - current_index + 1),
				 ETokenType::STRING_LITERAL_DQ };
		current_index = offset + 1;
		return t;
	}

	std::optional<Token> select_option(const std::string& source, size_t& current_index)
	{
		if (!is_option_char(source[current_index]))
			return std::nullopt;

		size_t offset = current_index;
		char first = source[offset];
		ETokenType type = ETokenType::SHORT_OPTION;
		offset++;

		if (offset < source.size() && source[offset] == first)
		{
			type = ETokenType::LONG_OPTION;
			offset++;
		}

		while (offset < source.size() && is_alphanumeric_(source[offset]))
			++offset;
		size_t ignored_chars = 0;
		if (type == ETokenType::SHORT_OPTION)
			ignored_chars = 1;
		else if (type == ETokenType::LONG_OPTION)
			ignored_chars = 2;

		Token t{ std::string_view(source.data() + current_index + ignored_chars, offset - current_index), type };
		current_index = offset;
		return t;
	}

	
	std::vector<Token> tokenize(const std::string& src)
	{

		// just an alias
		size_t index = 0;
		size_t length = src.length();
		std::vector<Token> result;
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
			}
			else if (src[index] == '\'')
			{
				if (auto t = select_string(src, index))
					result.push_back(*t);
			}
			else if (src[index] == '|')
			{
				result.emplace_back('|', ETokenType::PIPE);
				index++;
			}
			else if (src[index] == '>' || src[index] == '<')
			{
				result.emplace_back('>', ETokenType::REDIRECT);
				index++;
			}
			else if (src[index] == ';')
			{
				result.emplace_back(';', ETokenType::EOL);
				index++;
			}
			
			
			
			else
			{
				result.emplace_back(src[index], ETokenType::OPERATOR);
				index++;
			}
			//index++;
		}
		if(result.empty() || result[result.size() - 1].m_Type != ETokenType::EOL)
			result.push_back(Token{'\0', ETokenType::EOL});
		return result;
	}
	void replace_all(std::string& str, const std::string& from, const std::string& to) {
		size_t pos = 0;
		while ((pos = str.find(from, pos)) != std::string::npos) {
			str.replace(pos, from.length(), to);
			pos += to.length(); // Move past the replacement
		}
	}

	std::vector<Token> normalize_tokens(const std::vector<Token>& tokens)
	{
		return {};
	}



}