#pragma once
#include <string_view>
#include "ETokenType.h"
#include "../Core.h"
#include <entt/core/hashed_string.hpp>
#include <variant>
#include <iostream>

namespace qk::kernel
{

	using Arg_t = std::variant<float, int, std::string_view, char>;

	struct QK_API Token
	{
		Arg_t m_Value;
		ETokenType m_Type;

		

		const std::string_view view() const;

		std::string to_string() const;

		std::string_view strip_quotes() const;

		Token();

		template<typename T>
		Token(T value) : m_Value(value), m_Type(ETokenType::UNKNOWN)
		{
			bool is_in_variant = std::disjunction_v < std::is_same<T, float>, std::is_same<T, int>, std::is_same<T, std::string_view>, std::is_same<T, char> >;

			if (!is_in_variant)
				std::cout << typeid(T).name();

			assert(is_in_variant);
		}
		
		template<typename T>
		Token(T value, ETokenType type) : m_Value(value), m_Type(type)
		{

			constexpr bool is_in_variant = std::disjunction_v < std::is_same<T, float>, std::is_same<T, int>, std::is_same<T, std::string_view>, std::is_same<T, char> >;

			if(!is_in_variant)
				std::cout << typeid(T).name();

			static_assert(is_in_variant);

		}

		template <class T>
		bool is() const
		{
			return std::holds_alternative<T>(m_Value);
		}

		template <class T>
		const T& as() const
		{
			assert(is<T>());
			return std::get<T>(m_Value);
		}


	};
}

namespace qk
{
	// NOT IMPLEMENTED-DO NOT USE!
	entt::id_type QK_API hash(const qk::kernel::Token&);
}