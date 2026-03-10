#include "ILayer.h"

namespace qk {
	void ILayer::subscribe(EEventCategory category) {
		filter |= category;
	}
	void ILayer::unsubscribe(EEventCategory category) {
		filter &= ~category;
	}
}