#include "QKTL.h"


namespace qk
{
	entt::id_type hash(const std::string& string)
	{
		return entt::hashed_string{ string.c_str() }.value();
	}
	entt::id_type hash(const std::string_view& view)
	{
		return entt::hashed_string{ view.data(), view.size() }.value();
	}
}