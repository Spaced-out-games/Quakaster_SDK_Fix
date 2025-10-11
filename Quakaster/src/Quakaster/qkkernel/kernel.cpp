#include "Kernel.h"


namespace qk::kernel
{

    Kernel::Kernel()
    {
        ready();
    }

    void Kernel::ready()
    {
        std::cout << m_Cwd;
        std::cout << "> ";
    }

	void Kernel::register_fn(std::string name, Kernel_pfn kernel_fn)
	{
		entt::id_type hash = qk::hash(name);
		m_KernelFunctable[hash] = kernel_fn;
	}

    int Kernel::run(const TokenView& command)
    {
        entt::id_type hash = qk::hash(*command.command());

        auto it = m_KernelFunctable.find(hash);
        if (it == m_KernelFunctable.end())
        {
            m_stdout += "Unknown command: ";
            m_stdout += command.command()->m_View;
            m_stdout +='\n';
            return -1;
        }


        return it->second(*this, command);
    }

    int Kernel::run(Program* program)
    {
        int status = 0;
        for (const auto& view : program->token_views)
        {
            status = run(view);

            if (view.terminator()->m_Type == ETokenType::PIPE)
            {
                m_stdin = "";
                std::swap(m_stdin, m_stdout);
                
            }
            if (m_stdout.size())
            {
                std::cout << m_stdout;
                m_stdout = "";
            }



            if (status)
            {
                m_stdout += view.command()->m_View;
                m_stdout += " failed with code ";
                m_stdout += status;
                return status;
            }
        }
        ready();
    }

    std::string Kernel::getenv(std::string name)
    {
        entt::id_type hash = qk::hash(name);
        auto it = m_Env.find(hash);
        if (it == m_Env.end())
        {
            return "";
        }
        return m_Env[hash];
    }

    void Kernel::setenv(std::string name, std::string contents)
    {
        entt::id_type hash = qk::hash(name);
        m_Env[hash] = contents;
    }

}