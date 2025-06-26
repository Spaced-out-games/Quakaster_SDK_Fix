#pragma once
#include "../Core.h"
#include <cstdint>
#include <cstring>
#include <iostream>
#include <type_traits>

// generic C-style function pointer in C++ syntax
template <typename return_t, typename... arg_Ts>
using func_ptr_t = return_t(*)(arg_Ts...);

