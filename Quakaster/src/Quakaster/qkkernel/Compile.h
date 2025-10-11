#pragma once
#include "../Core.h"
#include "Program.h"
#include "Tokenizer.h"
#include <memory>



namespace qk::kernel
{
	QK_API std::unique_ptr<Program> compile(std::string&& source);
}