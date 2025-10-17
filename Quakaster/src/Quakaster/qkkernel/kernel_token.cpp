#include "kernel_token.h"



namespace qk::kernel
{
    Token::Token():
        m_Value("")
    {

    }

    std::string_view Token::strip_quotes() const
    {
        assert(m_Type != ETokenType::INT);

        if (auto ptr = std::get_if<std::string_view>(&m_Value))
        {
            // remove first and last character (quotes)
            return ptr->substr(1, ptr->size() - 2);
        }

        // optionally handle error if m_Value is not a string_view
        return {}; // or throw std::runtime_error("Token is not a string");
    }
    const std::string_view Token::view() const
    {
        if (is<std::string_view>()) {
            return as<std::string_view>();
        }

        return {};
    }



    std::string Token::to_string() const
    {
        // Map token type to string
        auto type_to_string = [](ETokenType type) -> const char* {
            switch (type) {
            case ETokenType::UNKNOWN:            return "UNKNOWN";
            case ETokenType::ERROR:              return "ERROR";
            case ETokenType::IDENTIFIER:         return "IDENTIFIER";
            case ETokenType::INT:                return "INT";
            case ETokenType::FLOAT:              return "FLOAT";
            case ETokenType::REDIRECT:           return "REDIRECT";
            case ETokenType::PIPE:               return "PIPE";
            case ETokenType::EOL:                return "EOL";
            case ETokenType::OPERATOR:           return "OPERATOR";
            case ETokenType::SHORT_OPTION:       return "SHORT_OPTION";
            case ETokenType::LONG_OPTION:        return "LONG_OPTION";
            case ETokenType::STRING_LITERAL_SQ:  return "STRING_LITERAL_SQ";
            case ETokenType::STRING_LITERAL_DQ:  return "STRING_LITERAL_DQ";
            default:                             return "UNKNOWN";
            }
        };

        return std::string{ "\"" } + std::string{ view() } + "\", " + type_to_string(m_Type);
    }
}

namespace qk
{
    entt::id_type hash(const qk::kernel::Token& tk)
    {
        
        return 0;
    }
}