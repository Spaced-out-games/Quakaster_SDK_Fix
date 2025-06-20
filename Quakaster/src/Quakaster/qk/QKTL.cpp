#include "QKTL.h"


tagged_float::tagged_float() {
	set_inline(0.0f);
}

tagged_float::tagged_float(float value) {
	set_inline(value);
}

tagged_float::tagged_float(float* ptr) {
	set_pointer(ptr);
}

// might make private
inline void tagged_float::set_inline(float val) {
	m_Floats[1] = val;
	m_Raw |= 1;  // set LSB to mark as inline
}
// might make private
inline void tagged_float::set_pointer(float* ptr) {
	m_Raw = reinterpret_cast<uintptr_t>(ptr); // control bit = 0
}

bool tagged_float::is_pointer() const {
	return (m_Raw & 1) == 0;
}

float& tagged_float::get() {
	if (is_pointer())
		return *reinterpret_cast<float*>(m_Raw);
	else
		return m_Floats[1]; // Inline value lives in upper 4 bytes
}
