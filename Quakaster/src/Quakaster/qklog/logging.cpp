#include "logging.h"
#include <string>
#include <iostream>
#include <sstream>

namespace qk
{
	// note: Might be a good idea to create an enum for error codes

	enum class Error : int {
		OKAY,
		SDL_INIT_FAILURE,
		GLEW_INIT_FAILURE,
		WINDOW_CREATE_FAILURE,
		IMGUI_INIT_FAILURE,
		OUT_OF_MEMORY,
		OUT_OF_BOUNDS,

		
	};


	LogMessage::LogMessage(std::string message, Severity severity, Category category) : text(message), severity(severity), category(category)
	{

	}

	std::string to_string(const LogMessage& message)
	{

		std::ostringstream os;

		os << "[";

		switch (message.category)
		{
		case CAT_AUDIO:		os << "AUDIO";	break;
		case CAT_GRAPHICS:	os << "GRAPHICS"; break;
		case CAT_NETWORK:	os << "NET"; break;
		case CAT_PHYSICS:	os << "PHYSICS"; break;
		case CAT_GAME:		os << "GAME"; break;
		case CAT_SCRIPT:    os << "SCRIPT"; break;
		case CAT_NONE:		break;
		default:			os << "?"; break;
		}


		switch (message.severity)
		{
		case LOG_INFO:			os << " INFO"; break;
		case LOG_DEBUG:			os << " DEBUG"; break;
		case LOG_PERFORMANCE:	os << " PERF"; break;
		case LOG_WARNING:		os << " WARNING"; break;
		case LOG_ERROR_SEVERE:	os << " SEVERE"; break;
		case LOG_ERROR_CRITICAL:os << " CRITICAL"; break;
		case LOG:			break;
		default:				os << "?"; break;
		}

		os << "]: " << message.text;
		return os.str();
	}

	void log(const LogMessage message)
	{
		std::cout << to_string(message) << '\n';
	}

	void log(std::string text, Severity severity, Category category)
	{
		std::cout << to_string(LogMessage{ text, severity, category }) << '\n';
	}

}