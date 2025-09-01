#pragma once
#include <stdint.h>


namespace qk::io
{
	enum class EServerEvent : uint8_t
	{
		SV_CONNECT,
		SV_DISCONNECT,
		SV_TIMEOUT,
		SV_CRASHED,
	};
}