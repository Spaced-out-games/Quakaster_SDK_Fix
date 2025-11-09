#pragma once
#include <ostream>

namespace qk::gfx
{
	enum class Error_t : int
	{
		NONE,
		PLATFORM_INIT_ERROR,
		PLATFORM_WINDOW_CREATE_ERROR,
		GFX_API_LOADER_FAILURE,
		GFX_API_INIT_FAILURE,
	};

	// Helper function to convert Error_t to string
	inline const char* to_string(Error_t type) {
		switch (type) {
		case Error_t::NONE: return "NONE";
		case Error_t::PLATFORM_INIT_ERROR: return "PLATFORM_INIT_ERROR";
		case Error_t::PLATFORM_WINDOW_CREATE_ERROR:  return "PLATFORM_WINDOW_CREATE_ERROR";
		case Error_t::GFX_API_LOADER_FAILURE: return "GFX_API_LOADER_FAILURE";
			// add other cases as needed
		default: return "Unknown Error";
		}
	}

	// Shouldn't need to apply a QK_API to it since it's a basic struct
	struct Error
	{
		// Which type of error it is
		Error_t m_Type = Error_t::NONE;

		// Details for that error type (ie, SDL_GetError()
		const char* m_Details = nullptr;

		inline operator bool() const
		{
			return m_Type != Error_t::NONE && m_Details != nullptr;
		}
	};

	inline std::ostream& operator<<(std::ostream& os, const Error& err) {
		if (err.m_Type == Error_t::NONE) return os;
		os << "[" << to_string(err.m_Type) << "]";
		if (err.m_Details && err.m_Details[0] != '\0') {
			os << " " << err.m_Details;
		}
		return os;
	}


}