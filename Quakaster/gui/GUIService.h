#pragma once
#include "../core.h"


namespace gui {

	// in a real implementation, just use qk::Window&
	void QK_API init(void* window);

	void QK_API demo();

	void QK_API shutdown();

}