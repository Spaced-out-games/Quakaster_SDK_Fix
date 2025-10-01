#pragma once
#include "../Core.h"


namespace qk::io
{
	enum class EEventType : uint16_t
	{


	};

	inline EEventType operator|(EEventCategory lhs, EEventCategory rhs)
	{
		return (EEventType)((uint8_t)lhs | (uint8_t)rhs);
	}

	inline bool operator&(EEventType lhs, EEventCategory rhs)
	{
		return (uint8_t)lhs & (uint8_t)rhs;
	}

	inline EEventType& operator|=(EEventCategory& lhs, EEventCategory rhs)
	{
		lhs = lhs | rhs;
		return lhs;
	}
	inline EEventType operator~(EEventType rhs)
	{
		return static_cast<EEventType>(~static_cast<uint8_t>(rhs));
	}



}