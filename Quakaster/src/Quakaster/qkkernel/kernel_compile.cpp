#include "kernel_compile.h"


namespace qk::kernel
{
    std::unique_ptr<Program> compile(std::string&& source)
    {


        auto pgm = std::make_unique<Program>();
        if (source == "")
        {
            return pgm;
        }

        // Take ownership of source
        pgm->tokens.source = std::move(source);

        // Tokenize
        pgm->tokens.tokens = tokenize(pgm->tokens.source);

        size_t last = 0;
        Token* start = pgm->tokens.tokens.data();

        for (size_t i = 0; i < pgm->tokens.tokens.size(); ++i)
        {
            auto type = pgm->tokens.tokens[i].m_Type;
            if (type == ETokenType::EOL || type == ETokenType::PIPE || type == ETokenType::REDIRECT)
            {
                if (i > last)
                    pgm->token_views.emplace_back(start + last, start + i);

                last = i + 1; // next slice starts after the terminator
            }
        }

        // Optional: handle any remaining tokens after the last terminator
        if (last < pgm->tokens.tokens.size())
            pgm->token_views.emplace_back(start + last, start + pgm->tokens.tokens.size());

        return pgm;
    }

    std::unique_ptr<Program> compile(const std::string& source)
    {

        return compile(std::string(source));
    }
}