#ifndef __SHIPS__HPP__
#define __SHIPS__HPP__

#include <map>

namespace Ship
{
    enum class Type
    {
        NONE = -1
    };

    std::map<Ship::Type, const char *> Descriptions = {};
}

#endif
