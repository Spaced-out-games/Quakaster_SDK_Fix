#pragma once


namespace qk::kernel
{
	enum class ETokenType
	{
		UNKNOWN,
		ERROR,
		IDENTIFIER,
		NUMBER,
		REDIRECT,
		PIPE,
		EOL,
		OPERATOR,
		SHORT_OPTION,
		LONG_OPTION,
		STRING_LITERAL_SQ,
		STRING_LITERAL_DQ,
		
	};
}