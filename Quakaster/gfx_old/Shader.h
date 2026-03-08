#pragma once
#include <string>
#include "../core.h"


namespace gfx {




	class QK_API Shader {


		using Type = unsigned int;
		using Source = std::string;

		Source	m_Source;
		Type	m_Type;

		public:

			Shader(const Source& source, Type type);

			unsigned int compile() const;


	};
}