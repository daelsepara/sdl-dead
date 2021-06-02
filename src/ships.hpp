#ifndef __SHIPS__HPP__
#define __SHIPS__HPP__

#include <vector>

namespace Ship
{
    enum class Type
    {
        NONE = -1,
        CALYPSO,
        FAERIE_QUEEN,
        LADY_OF_SHALOTT,
        METEOR,
        OCTAVIUS,
        PROVIDENCE,
        QUEENS_RANSOM,
        SHIVERED_TIMBER
    };

    class Base
    {
    public:
        std::string Name = "";
        int Stars = 0;
        Ship::Type Type = Ship::Type::NONE;

        Base()
        {
            Stars = 1;
        }

        Base(const char *name, int stars, Ship::Type type)
        {
            Name = name;
            Stars = stars;
            Type = type;
        }
    };

    auto NONE = Ship::Base("None", -1, Ship::Type::NONE);
    auto LADY_OF_SHALOTT = Ship::Base("Lady of Shalott", 1, Ship::Type::LADY_OF_SHALOTT);
    auto SHIVERED_TIMBER = Ship::Base("Shivered Timber", 2, Ship::Type::SHIVERED_TIMBER);
    auto QUEENS_RANSOM = Ship::Base("Queen's Ransom", 3, Ship::Type::QUEENS_RANSOM);
    auto FAERIE_QUEEN = Ship::Base("Faerie Queen", 3, Ship::Type::FAERIE_QUEEN);
    auto METEOR = Ship::Base("Meteor", 4, Ship::Type::METEOR);
    auto OCTAVIUS = Ship::Base("Octavius", 4, Ship::Type::OCTAVIUS);
    auto PROVIDENCE = Ship::Base("Providence", 5, Ship::Type::PROVIDENCE);
    auto CALYPSO = Ship::Base("Calypso", 5, Ship::Type::CALYPSO);
}

#endif
