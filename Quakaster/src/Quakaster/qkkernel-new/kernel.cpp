#include "kernel.h"
#include "ShellBase.h"


namespace qk::kernel
{
	void Kernel::register_fn(entt::hashed_string name, Kernel_pfn kernel_fn)
	{
		m_FuncTable[name] = kernel_fn;
	}
    
    int Kernel::run_program(std::span<const Token> program)
    {
        size_t ip = 0;

        // iterate over the tokens
        while (ip < program.size())
        {

            // grab the anchor
            const Token& anchor = program[ip];

            // resolve and run, selecting the following tokens, up through, but not including the terminating token
            if (anchor.is<CommandToken>())
            {
                const auto& cmd_id = anchor.as<CommandToken>();
                auto it = m_FuncTable.find(cmd_id);
                if (it != m_FuncTable.end())
                {
                    size_t start = ip + 1;
                    size_t end = start;
                    while (end < program.size() &&
                        !program[end].is<PipeToken>() &&
                        !program[end].is<TerminatorToken>())
                        ++end;

                    std::span<const Token> args(program.data() + start, end - start);
                    it->second(*this, args);

                    ip = end;
                    last_anchor_was_pipe = false;
                    continue;
                }
            }
            else if (anchor.is<PipeToken>())
            {
                pipe();
                last_anchor_was_pipe = true;
                ++ip;
                continue;
            }
            else if (anchor.is<TerminatorToken>())
            {
                if (!std::holds_alternative<NullToken>(m_stdout))
                    print(m_stdout);
                m_stdin = NullToken{};
                m_stdout = NullToken{};
                last_anchor_was_pipe = false;
                ++ip;
                continue;
            }
            else if (anchor.is<IdentifierToken>())
            {
                entt::id_type hash = anchor.as<IdentifierToken>().value();

                if (last_anchor_was_pipe)
                {
                    m_Env[hash] = std::move(m_stdin);
                    m_stdin = NullToken{};
                    last_anchor_was_pipe = false;
                }
                else
                {
                    auto it = m_Env.find(hash);
                    
                    if (it->second.is<Program>())
                    {

                        run_program(it->second.as<Program>());
                    }
                    else
                    {
                        m_stdout = (it != m_Env.end()) ? it->second : NullToken{};
                    }
                }
            }
            else if (anchor.is<Program>())
            {
                run_program(program);
            }

            else
            {
                std::visit([this](auto&& val)
                {
                    m_stdout = std::forward<decltype(val)>(val);
                }, anchor);

                last_anchor_was_pipe = false;
            }

            ++ip;
        }

        return 0;
    }


    int Kernel::run_program(const Program& program)
    {
        return run_program(std::span<const Token>(program));
    }
    Kernel::~Kernel()
    {
        if (m_Shell)
        {
            m_Shell->m_Kernel = nullptr;
        }
    }
    void Kernel::print(const Token& token)
    {
        if (m_Shell)
        {
            m_Shell->print(token.print_str());
        }
    }
    void Kernel::print(const std::string& content)
    {
        if (m_Shell)
        {
            m_Shell->print(content);
        }
    }
    void Kernel::pipe()
    {
        std::swap(m_stdin, m_stdout);

        // clears the token
        m_stdout = NullToken{};
        last_anchor_was_pipe = true;
    }


    
    const Token& Kernel::get_env(entt::id_type id) const {
        static Token null = NullToken{};
        if (auto it = m_Env.find(id); it != m_Env.end())
            return it->second;
        return null;
    }

}