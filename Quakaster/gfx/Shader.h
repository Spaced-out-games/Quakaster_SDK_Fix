#pragma once
#include <string>
#include "../core.h"
#include "types.h"

namespace gfx {

	using ShaderType = unsigned int;


	struct QK_API Shader {



		private:
			std::string m_Source;
			ShaderType	m_Type;


		public:

			Shader(const std::string& source, ShaderType type);

			Handle compile() const;


	};
}