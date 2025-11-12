#pragma once
#include "../qk/QKTL.h"
#include <ostream>
#include <variant>
#include <GL/glew.h>
#include <format>

namespace qk::gfx
{
	enum class Error_t : int
	{
		NONE,
		PLATFORM_INIT_ERROR,
		PLATFORM_WINDOW_CREATE_ERROR,
		GFX_API_LOADER_FAILURE,
		GFX_API_INIT_FAILURE,
		GFX_SHADER_COMPILE_ERROR,
		GFX_VERTEX_BUFFER_INIT_ERROR,
		GFX_VERTEX_BUFFER_DESTROY_ERROR,

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


	// gfx error code
	struct Error 
	{
		// Shouldn't need to apply a QK_API to it since it's a basic struct
		


		// Which type of error it is
		Error_t m_Type = Error_t::NONE;

		Error(Error_t type, const char* details) :
			m_Type(type),
			m_Details(details)
		{}
		Error():
			m_Type(Error_t::NONE),
			m_Details(nullptr)
		{
			// Just make it explicit
		}

		// Details for that error type (ie, SDL_GetError()
		const char* m_Details = nullptr;

		inline operator bool() const
		{
			return m_Type != Error_t::NONE && m_Details != nullptr;
		}
	};

	inline std::string to_string(const Error& err) {
		return std::format("[{}, {}]", to_string(err.m_Type), err.m_Details);
	}

	



	inline std::ostream& operator<<(std::ostream& os, const Error& err) {
		if (err.m_Type == Error_t::NONE) return os; // draw nothing
		os << to_string(err);
		return os;
	}


	/// <summary>
	/// Result gotten from a successful gfx call. Stores a GLuint on success, Error on failure, and Error{NONE, nullptr} for null result
	/// </summary>
	struct Result: qk::Result<GLuint, Error>
	{
		using Base = qk::Result<GLuint, Error>;

		using Base::Base;

		operator bool() const
		{
			// If it's not a GLuint, it must be an Error, so this should be safe, if it short-circuits.
			return this->is<GLuint>() || this->as<Error>().m_Details == nullptr;
		}
	};

	inline std::string to_string(const Result& result) {
		if (result) return std::format("[{}, {}]", to_string(result.as<Error>().m_Type), result.as<Error>().m_Details);
		return "";
	}

}