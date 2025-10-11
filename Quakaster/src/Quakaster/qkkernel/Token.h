#pragma once
#include <string_view>
#include "ETokenType.h"
#include "../Core.h"
#include <entt/core/hashed_string.hpp>


namespace qk::kernel
{
	struct QK_API Token
	{
		std::string_view m_View;
		ETokenType		 m_Type;

		std::string to_string() const;

	};
}

namespace qk
{
	entt::id_type QK_API hash(const qk::kernel::Token&);
}