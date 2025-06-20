#pragma once
#include "../Core.h"
#include <cstdint>
#include <cstring>
#include <iostream>
#include <type_traits>

// generic C-style function pointer in C++ syntax
template <typename return_t, typename... arg_Ts>
using func_ptr_t = return_t(*)(arg_Ts...);

//Stores a float, float* union and uses the LSB as the polymorphic control bit. Cannot hot-swap type bit.
class QK_API tagged_float {
	static_assert(sizeof(float*) == sizeof(uintptr_t), "Pointer size must match uintptr_t.");
	static_assert(alignof(float) >= 2, "Float must be at least 2-byte aligned.");

	union {
		uintptr_t m_Raw;
		float     m_Floats[2]; // We'll use m_Floats[1] for inline storage
	};

	// these should be hidden from public view. Also, by inlining them, it makes it a *tad* harder to exploit

	inline void set_inline(float val);
	inline void set_pointer(float* ptr);

	// Move and copy semantics? Off with your head!
	tagged_float(const tagged_float&) = delete;
	tagged_float& operator=(const tagged_float&) = delete;
	tagged_float(tagged_float&&) = default;
	tagged_float& operator=(tagged_float&&) = default;

public:
	tagged_float();



	tagged_float(float value);

	tagged_float(float* ptr);



	bool is_pointer() const;

	// figures out whether the float is inline or not, returns the correct one regardless
	float& get();
};