#ifndef __USER_DEFINE_H__
#define __USER_DEFINE_H__

#include <string>

namespace Chat::Base
{
    struct User
    {
        std::string name{};
        std::string password{};
    };
}

#endif
