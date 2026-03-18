#pragma once
#include "types.h"
#include <stdint.h>
#include "../core.h"

namespace qk::gfx {
	enum class ECommandType : uint32_t {
		NONE, // default constructor
		BIND_VERTEXARRAY,
		BIND_VERTEXBUFFER,
		BIND_INDEXBUFFER,
		BIND_TEXTURE,
		BIND_SHADER,

		DRAW_VERTEXARRAY
	};

	struct DrawCommand {
		ECommandType	type;
		Handle			handles[7];
	};

	void QK_API call(const DrawCommand& command);

}