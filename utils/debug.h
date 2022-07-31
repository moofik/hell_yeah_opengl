#ifndef OPENGL1_DEBUG_H
#define OPENGL1_DEBUG_H
#include <iostream>
#include <cstdio>
#include <cstdarg>
#include <cstring>
#include "default.h"

#define CONSOLE_LOG_FUNC(details) do { \
    std::cout << "Line: " << __LINE__ << "; File: " << __FILE__ << " :: " << details; } while(0)
/**
 * This macro helps you log arbitrary params number
 */
#define CONSOLE_LOG(args...) CONSOLE_LOG_FUNC(concat_nargs(N_ARGS(args), args))
#define TWO_VECTORS_DIFF(vec1, vec2) CONSOLE_LOG("Vec1 is : (", std::to_string(vec1.x).c_str(), std::to_string(vec1.y).c_str(), \
        std::to_string(vec1.z).c_str(), "); Vec2 is : (", \
        std::to_string(vec2.x).c_str(), std::to_string(vec2.y).c_str(), \
                std::to_string(vec2.z).c_str(), "\n" \
    )
#define PRINT_VECTOR(vec1) CONSOLE_LOG("Vec is : (", std::to_string(vec1.x).c_str(), std::to_string(vec1.y).c_str(), \
        std::to_string(vec1.z).c_str(), "\n" \
    )

static inline const char* concat_nargs(unsigned int n_args, ...)
{
    char* result = new char[512];
    const char* arg;
    unsigned int i;
    va_list ap;

    va_start(ap, n_args);

    for (i = 0; i < n_args; i++) {
        arg = va_arg(ap, const char*);
        strcat(result, arg);
        strcat(result, "; ");
    }

    va_end(ap);

    return (const char*) result;
}

#endif //OPENGL1_DEBUG_H
