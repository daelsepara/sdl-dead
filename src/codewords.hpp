#ifndef __CODEWORDS__HPP__
#define __CODEWORDS__HPP__

#include <map>

namespace Codeword
{
    enum class Type
    {
        NONE = -1,
        AUGUST,
        CHANCERY,
        DETRUDE,
        FETISH,
        HORAL,
        ICARUS,
        MALEFIC,
        MAMMON,
        MARATHON,
        PECCANT,
        PROSPERO,
        RAVEN,
        SCRIP,
        FLOAT
    };

    std::map<Codeword::Type, const char *> Descriptions = {
        {Codeword::Type::AUGUST, "AUGUST"},
        {Codeword::Type::CHANCERY, "CHANCERY"},
        {Codeword::Type::DETRUDE, "DETRUDE"},
        {Codeword::Type::FETISH, "FETISH"},
        {Codeword::Type::HORAL, "HORAL"},
        {Codeword::Type::ICARUS, "ICARUS"},
        {Codeword::Type::MALEFIC, "MALEFIC"},
        {Codeword::Type::MAMMON, "MAMMON"},
        {Codeword::Type::MARATHON, "MARATHON"},
        {Codeword::Type::PECCANT, "PECCANT"},
        {Codeword::Type::PROSPERO, "PROSPERO"},
        {Codeword::Type::RAVEN, "RAVEN"},
        {Codeword::Type::SCRIP, "SCRIP"},
        {Codeword::Type::FLOAT, "FLOAT"}};

} // namespace Codeword
#endif
