#include "tokenizer.h"


namespace qk::shell
{
	void Tokenizer::set_source(std::string target)
	{
		m_Target = target;
		m_Front = m_Target.data();
		m_Back	= m_Front;
		m_Final = m_Back + m_Target.size() - 1;
	}
	void Tokenizer::skip_whitespace()
	{
		while (m_Back <= m_Final && std::isspace(*m_Back)) {
			++m_Back;
		}
		m_Front = m_Back;
	}


	
	void Tokenizer::read_double_quotes() {
    bool escape = false;
    ++m_Back; // skip opening quote (m_Front points to opening ")

    while (m_Back <= m_Final) {
        if (escape) {
            escape = false;
            ++m_Back; // skip escaped character
            continue;
        }

        if (*m_Back == '\\') {
            escape = true;
        } 
        else if (*m_Back == '"') {
            // stop here, *m_Back == closing quote
            break;
        }
        ++m_Back;
    }

    // Invariant now holds:
    // *m_Front == '"' (opening quote)
    // *m_Back  == '"' (closing quote)
}
	

}