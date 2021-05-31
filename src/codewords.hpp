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
        {Codeword::Type::AUGUST, "August"},
        {Codeword::Type::CHANCERY, "Chancery"},
        {Codeword::Type::DETRUDE, "Detrude"},
        {Codeword::Type::FETISH, "Fetish"},
        {Codeword::Type::HORAL, "Horal"},
        {Codeword::Type::ICARUS, "Icarus"},
        {Codeword::Type::MALEFIC, "Malefic"},
        {Codeword::Type::MAMMON, "Mammon"},
        {Codeword::Type::MARATHON, "Marathon"},
        {Codeword::Type::PECCANT, "Peccant"},
        {Codeword::Type::PROSPERO, "Prospero"},
        {Codeword::Type::RAVEN, "Raven"},
        {Codeword::Type::SCRIP, "Scrip"},
        {Codeword::Type::FLOAT, "Float"}};

} // namespace Codeword
#endif
