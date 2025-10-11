#pragma once
#include "ETokenType.h"
#include "Token.h"
#include "TokenView.h"
#include "TokenList.h"
#include "Program.h"
#include "../Core.h"
#include <string>
#include <string_view>
#include <cassert>

namespace qk::kernel
{

	QK_API bool is_alpha(char c);

	QK_API bool is_numeric(char c);

	QK_API bool is_alphanumeric(char c);

	QK_API bool is_terminator(char c);

	QK_API bool is_whitespace(char c);

	QK_API bool is_option_char(char c);

	QK_API std::string_view select_whitespace(const std::string& source, size_t& current_index);

	QK_API std::string_view select_identifier(const std::string& source, size_t& current_index);

	QK_API std::string_view select_number(const std::string& source, size_t& current_index);

	QK_API std::string_view select_path(const std::string& source, size_t& current_index);

	QK_API Token select_option(const std::string& source, size_t& current_index);

	QK_API std::vector<Token> tokenize(const std::string& src);

	QK_API std::vector<Token> normalize_tokens(const std::vector<Token>& tokens);

}