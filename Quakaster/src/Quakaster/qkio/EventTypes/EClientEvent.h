#pragma once
#include <stdint.h>


namespace qk::io
{
	enum class EClientEvent : uint8_t
	{
		CL_CONNECT,
		CL_DISCONNECT,
		CL_TIMEOUT,
		CL_KICKED,
		CL_CRASHED,
	};
}