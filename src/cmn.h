#pragma once

#include <iostream>

#define CMN_ASSERT(x)                                                                                                  \
    if (!(x))                                                                                                          \
    {                                                                                                                  \
        CMN_ASSERT_MSG(#x, __FILE__, __LINE__);                                                                        \
    }

#define CMN_ASSERT_MSG(x, file, line)                                                                                  \
    {                                                                                                                  \
        std::cerr << "Assertion failed: " << x << " at " << file << ":" << line << std::endl;                          \
        abort();                                                                                                       \
    }
