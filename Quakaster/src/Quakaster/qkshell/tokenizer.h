#pragma once
#include "../Core.h"
#include <regex>
#include <istream>
#include <string>

namespace qk::shell
{
	enum class ETokenType
	{
		UNKNOWN,
		COMMAND,
		INTEGER,
		FLOAT,
		SINGLE_QUOTE_STRING,
		DOUBLE_QUOTE_STRING,
		SHORT_OPTION,
		LONG_OPTION,
		PIPE,
		SEMICOLON,
		PATH,
	};

	struct QK_API Tokenizer
	{
		// Nearest to [0]
		char*			m_Front;

		// Nearest to [n-1]
		char*			m_Back;
		// At [n-1]
		char*			m_Final;

		// the string to work with
		std::string		m_Target;

		inline void set_source(std::string);

		inline void skip_whitespace();

		inline void read_double_quotes();

	};





	
}