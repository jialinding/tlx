/*******************************************************************************
 * tlx/port/setenv.cpp
 *
 * Part of tlx - http://panthema.net/tlx
 *
 * Copyright (C) 2016-2018 Timo Bingmann <tb@panthema.net>
 *
 * All rights reserved. Published under the Boost Software License, Version 1.0
 ******************************************************************************/

#include <tlx/port/setenv.hpp>

#include <cstdlib>

namespace tlx {

// Windows porting madness because setenv() is apparently dangerous
#if defined(_MSC_VER)

int setenv(const char* name, const char* value, int overwrite) {
    if (!overwrite) {
        size_t envsize = 0;
        int errcode = getenv_s(&envsize, nullptr, 0, name);
        if (errcode || envsize) return errcode;
    }
    return _putenv_s(name, value);
}

#else

int setenv(const char* name, const char* value, int overwrite) {
    return ::setenv(name, value, overwrite);
}

#endif

} // namespace tlx

/******************************************************************************/
