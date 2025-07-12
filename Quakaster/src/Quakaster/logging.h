#pragma once
#include <iostream>
#include <string>
#include "Core.h"



namespace qk {


	// Log message severity
	enum Severity : uint16_t {
		LOG = 0x00,
		LOG_INFO = 0x01,
		LOG_PERFORMANCE = 0x02,
		LOG_DEBUG = 0x03,
		LOG_WARNING = 0x04,
		LOG_ERROR_SEVERE = 0x05,
		LOG_ERROR_CRITICAL = 0x06
	};

	// log message category
	enum Category : uint16_t {
		CAT_NONE		= 0 << 0,
		CAT_GRAPHICS	= 1 << 0,
		CAT_AUDIO		= 1 << 1,
		CAT_PHYSICS		= 1 << 2,
		CAT_NETWORK		= 1 << 3,
		CAT_GAME		= 1 << 4,
		CAT_SCRIPT		= 1 << 5,

	};


	struct QK_API LogMessage {
		LogMessage(std::string message, Severity severity = LOG, Category category = CAT_NONE);
		Severity severity;
		Category category;
		std::string text;
	};

	// Converts a log message to a string
	std::string to_string(const LogMessage& message);


	// Prints to std::cout for now. Will use the integrated console. 
	inline void QK_API log(LogMessage message);
	inline void QK_API log(std::string text, Severity severity = LOG, Category category = CAT_NONE);
	// Logs to the integrated console
}