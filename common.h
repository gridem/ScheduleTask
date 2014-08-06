// Copyright (c) 2013 Grigory Demchenko

#pragma once

#include <iostream>
#include <stdexcept>

// Release log
#define RLOG(D_msg)                 std::cerr << D_msg << std::endl

// Null log
#define NLOG(D_msg)

#ifdef flagLOG_DEBUG
#   define LOG                      RLOG
#else
#   define LOG                      NLOG
#endif
#define DUMP(D_value)               LOG(#D_value " = " << D_value)
#define RAISE(D_str)                throw std::runtime_error(D_str)
#define VERIFY(D_cond, D_str)       if (!(D_cond)) RAISE("Verification failed: " #D_cond ": " D_str)


