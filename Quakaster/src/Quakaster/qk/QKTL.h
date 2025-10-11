#pragma once
#include "../Core.h"
#include <cstdint>
#include <cstring>
#include <iostream>
#include <type_traits>
#include <cassert>
#include <entt/core/hashed_string.hpp>


// generic C-style function pointer in C++ syntax
template <typename return_t, typename... arg_Ts>
using func_ptr_t = return_t(*)(arg_Ts...);

class FloatPtrUnion
{
	union
	{

		uintptr_t m_Raw;
		float m_Inline[2];
		float* m_Ptr;
	};

	public:

	inline bool is_inline() const;

	inline const float& get() const;

	inline void set(float new_value);

	// defaults to 0.0f inline
	inline FloatPtrUnion();

	// defaults to whatever, inline
	inline FloatPtrUnion(float default_value);

	// Points to a float instead of being one
	inline FloatPtrUnion(float* value_ptr);

	inline FloatPtrUnion& operator=(float value);
	inline operator float() const;


};

FloatPtrUnion::FloatPtrUnion()
{
	// set the inline value to zero
	m_Inline[1] = 0.0f;

	// set the flag
	m_Raw |= 1;


}

FloatPtrUnion::FloatPtrUnion(float default_value)
{
	// set the inline value to zero
	m_Inline[1] = default_value;

	// set the flag
	m_Raw |= 1;


}

FloatPtrUnion::FloatPtrUnion(float* value_ptr) {
	m_Ptr = value_ptr;
	// Make sure LSB is zero (alignment of float* ensures this)
	assert(((uintptr_t)value_ptr & 1) == 0);
}

bool FloatPtrUnion::is_inline() const
{
	return (m_Raw & 1) != 0;
}

const float& FloatPtrUnion::get() const
{
	if (is_inline())
	{
		return m_Inline[1];
	}

	return *m_Ptr;
}

void FloatPtrUnion::set(float new_value)
{
	if (is_inline())
	{
		m_Inline[1] = new_value;
		return;
	}

	*m_Ptr = new_value;
}

inline FloatPtrUnion& FloatPtrUnion::operator=(float value) {
	if (is_inline()) {
		m_Inline[1] = value;
	}
	else {
		*m_Ptr = value;
	}
	return *this;
}

inline FloatPtrUnion::operator float() const {
	return get();
}

namespace qk
{
	entt::id_type QK_API hash(const std::string& string);
	entt::id_type QK_API hash(const std::string_view& view);
}