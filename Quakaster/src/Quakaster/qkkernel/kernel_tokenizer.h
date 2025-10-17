#pragma once
#include "ETokenType.h"
#include "kernel_token.h"
#include "kernel_token_view.h"
#include "kernel_token_list.h"
#include "kernel_program.h"
#include "../Core.h"
#include <string>
#include <string_view>
#include <cassert>
#include <optional>

namespace qk::kernel
{

	QK_API bool is_alpha(char c);

	QK_API bool is_numeric(char c);

	QK_API bool is_alphanumeric(char c);

	QK_API bool is_terminator(char c);

	QK_API bool is_whitespace(char c);

	QK_API bool is_option_char(char c);

	QK_API std::string_view select_whitespace(const std::string& source, size_t& current_index);

	QK_API std::optional<Token> select_var(const std::string& source, size_t& current_index);

	QK_API std::optional<Token> select_identifier(const std::string& source, size_t& current_index);

	QK_API std::optional<Token> select_number(const std::string& source, size_t& current_index);

	QK_API std::optional<Token> select_string(const std::string& source, size_t& current_index);

	QK_API std::optional<Token> select_option(const std::string& source, size_t& current_index);

	QK_API std::vector<Token> tokenize(const std::string& src);

	QK_API std::vector<Token> normalize_tokens(const std::vector<Token>& tokens);

	QK_API void replace_all(std::string& str, const std::string& from, const std::string& to);

}