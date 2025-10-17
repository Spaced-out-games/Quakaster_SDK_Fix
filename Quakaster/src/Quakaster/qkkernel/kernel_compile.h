#pragma once
#include "../Core.h"
#include "kernel_program.h"
#include "kernel_tokenizer.h"
#include <memory>



namespace qk::kernel
{
	QK_API std::unique_ptr<Program> compile(std::string& source);
	QK_API std::unique_ptr<Program> compile(std::string&& source);

}