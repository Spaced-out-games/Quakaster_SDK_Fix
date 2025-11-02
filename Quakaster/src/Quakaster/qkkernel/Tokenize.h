#pragma once
#include "../Core.h"
#include <optional>
#include <string>
#include <cassert>
#include "Token.h"


namespace qk::kernel
{

	bool is_alpha(char c);

	bool is_numeric(char c);

	bool is_alphanumeric(char c);

	bool is_terminator(char c);

	bool is_whitespace(char c);

	bool is_option_char(char c);

	QK_API void select_whitespace(const std::string& source, size_t& current_index);

	QK_API std::optional<Token> select_var(const std::string& source, size_t& current_index);

	QK_API std::optional<Token> select_identifier(const std::string& source, size_t& current_index);

	QK_API std::optional<Token> select_number(const std::string& source, size_t& current_index);

	QK_API std::optional<Token> select_string(const std::string& source, size_t& current_index);

	QK_API std::optional<Token> select_option(const std::string& source, size_t& current_index);

	QK_API Program tokenize(const std::string& src);

	QK_API void replace_all(std::string& str, const std::string& from, const std::string& to);
}