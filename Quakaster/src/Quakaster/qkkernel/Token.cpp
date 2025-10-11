#include "Token.h"



namespace qk::kernel
{
    std::string Token::to_string() const
    {
        // Map token type to string
        auto type_to_string = [](ETokenType type) -> const char* {
            switch (type) {
            case ETokenType::UNKNOWN:            return "UNKNOWN";
            case ETokenType::ERROR:              return "ERROR";
            case ETokenType::IDENTIFIER:         return "IDENTIFIER";
            case ETokenType::NUMBER:             return "NUMBER";
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

        return std::string{ "\"" } + std::string{ m_View } + "\", " + type_to_string(m_Type);
    }
}

namespace qk
{
    entt::id_type hash(const qk::kernel::Token& tk)
    {
        
        return entt::hashed_string{ tk.m_View.data(), tk.m_View.size() }.value();
    }
}