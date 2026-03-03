#pragma once
#include <variant>
#include "../core.h"
#include <string>

namespace qk::console {


	using convar_t = std::variant<int, std::string, float, bool>;
	using convar_validate_pfn_t = bool(*)(const convar_t&);

	class QK_API Convar {

		convar_t m_Value;
		convar_validate_pfn_t m_Validator = nullptr;
		std::string m_Description;

		public:

		Convar(convar_t value = 0, const std::string& description = "No Description Provided", convar_validate_pfn_t validator = nullptr);


		const std::string& description();


		template <class T>
		T* try_get() {
			return std::get_if<T>(&m_Value);
		}
		
		template <class T>
		const T* try_get() const {
			return std::get_if<T>(&m_Value);
		}


		bool set(convar_t new_value);

		const convar_t& value();



	};
}