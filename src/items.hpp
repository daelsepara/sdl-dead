#ifndef __ITEMS__HPP__
#define __ITEMS__HPP__

#include <vector>

namespace Item
{
    enum class Type
    {
        NONE = -1,
        MAGIC_AMULET,
        MAGIC_WAND,
        PISTOL,
        SWORD,
        SHARKS_TOOTH_SWORD,
        FEATHER_SHIELD,
        CRUCIFIX,
        COMPASS,
        PARROT,
        THUNDERCLOUD_FAN,
        OBSIDIAN_NECKLACE,
        LETTER_OF_MARQUE,
        CONCH_SHELL_HORN,
        BAT_SHAPED_TALISMAN,
        BRONZE_HELMET,
        DRAGON_RING,
        TOOLKIT,
        BOOK_OF_CHARTS,
        LODESTONE,
        MONKEY,
        SHIP_IN_BOTTLE,
        BLACK_KITE,
        HEALING_POTION,
        DIAMOND,
        DEED_OF_OWNERSHIP,
        WEASEL,
        POCKET_WATCH,
        CORKSCREW,
        PROVISIONS,
        First = MAGIC_AMULET,
        Last = PROVISIONS
    };

    class Base
    {
    public:
        std::string Name;
        std::string Description;

        Item::Type Type = Item::Type::NONE;

        int Charge = -1;

        Base()
        {
        }

        Base(const char *name, const char *description, Item::Type type)
        {
            Name = name;
            Description = description;
            Type = type;
        }

        Base(const char *name, const char *description, Item::Type type, int charge)
        {
            Name = name;
            Description = description;
            Type = type;
            Charge = charge;
        }
    };

    // Item defaults

    auto MAGIC_AMULET = Item::Base("MAGIC AMULET", "MAGIC AMULET", Item::Type::MAGIC_AMULET);
    auto MAGIC_WAND = Item::Base("MAGIC WAND", "MAGIC WAND", Item::Type::MAGIC_WAND);
    auto PISTOL = Item::Base("PISTOL", "PISTOL", Item::Type::PISTOL);
    auto SWORD = Item::Base("SWORD", "SWORD", Item::Type::SWORD);
    auto FEATHER_SHIELD = Item::Base("FEATHER SHIELD", "FEATHER SHIELD", Item::Type::FEATHER_SHIELD);
    auto CRUCIFIX = Item::Base("CRUCIFIX", "CRUCIFIX", Item::Type::CRUCIFIX);
    auto COMPASS = Item::Base("COMPASS", "COMPASS", Item::Type::COMPASS);
    auto PARROT = Item::Base("PARROT", "PARROT", Item::Type::PARROT);
    auto THUNDERCLOUD_FAN = Item::Base("THUNDERCLOUD FAN", "THUNDERCLOUD FAN", Item::Type::THUNDERCLOUD_FAN);
    auto OBSIDIAN_NECKLACE = Item::Base("OBSIDIAN NECKLACE", "OBSIDIAN NECKLACE", Item::Type::OBSIDIAN_NECKLACE);
    auto SHARKS_TOOTH_SWORD = Item::Base("SHARK's TOOTH SWORD", "A blade of hard wood studded with shark's teeth", Item::Type::SHARKS_TOOTH_SWORD);
    auto LETTER_OF_MARQUE = Item::Base("LETTER OF MARQUE", "LETTER OF MARQUE", Item::Type::LETTER_OF_MARQUE);
    auto CONCH_SHELL_HORN = Item::Base("CONCH SHELL HORN", "CONCH SHELL HORN", Item::Type::CONCH_SHELL_HORN);
    auto BAT_SHAPED_TALISMAN = Item::Base("BAT-SHAPED TALISMAN", "BAT-SHAPED TALISMAN", Item::Type::BAT_SHAPED_TALISMAN);
    auto BRONZE_HELMET = Item::Base("BRONZE HELMET", "BRONZE HELMET", Item::Type::BRONZE_HELMET);
    auto DRAGON_RING = Item::Base("DRAGON RING", "DRAGON RING", Item::Type::DRAGON_RING);
    auto TOOLKIT = Item::Base("TOOLKIT", "TOOLKIT", Item::Type::TOOLKIT);
    auto BOOK_OF_CHARTS = Item::Base("BOOK OF CHARTS", "BOOK OF CHARTS", Item::Type::BOOK_OF_CHARTS);
    auto LODESTONE = Item::Base("LODESTONE", "LODESTONE", Item::Type::LODESTONE);
    auto MONKEY = Item::Base("MONKEY", "MONKEY", Item::Type::MONKEY);
    auto SHIP_IN_BOTTLE = Item::Base("SHIP IN A BOTTLE", "SHIP IN A BOTTLE", Item::Type::SHIP_IN_BOTTLE);
    auto BLACK_KITE = Item::Base("BLACK KITE", "BLACK KITE", Item::Type::BLACK_KITE);
    auto DIAMOND = Item::Base("DIAMOND", "DIAMOND", Item::Type::DIAMOND);
    auto HEALING_POTION = Item::Base("HEALING POTION", "HEALING POTION", Item::Type::HEALING_POTION);
    auto DEED_OF_OWNERSHIP = Item::Base("DEED OF OWNERSHIP", "DEED OF OWNERSHIP", Item::Type::DEED_OF_OWNERSHIP);
    auto WEASEL = Item::Base("WEASEL", "WEASEL", Item::Type::WEASEL);
    auto POCKET_WATCH = Item::Base("POCKET WATCH", "POCKET WATCH", Item::Type::POCKET_WATCH);
    auto CORKSCREW = Item::Base("CORKSCREW", "CORKSCREW", Item::Type::CORKSCREW);
    auto PROVISIONS = Item::Base("PROVISIONS", "PROVISIONS", Item::Type::PROVISIONS);

    std::vector<Item::Type> UniqueItems = {
        Item::Type::DRAGON_RING};

    bool IsUnique(Item::Type item)
    {
        auto unique = false;

        for (auto i = 0; i < Item::UniqueItems.size(); i++)
        {
            if (Item::UniqueItems[i] == item)
            {
                unique = true;

                break;
            }
        }

        return unique;
    }

    void REMOVE(std::vector<Item::Base> &items, Item::Base item)
    {
        if (items.size() > 0)
        {
            for (auto i = 0; i < items.size(); i++)
            {
                if (items[i].Type == item.Type)
                {
                    items.erase(items.begin() + i);

                    break;
                }
            }
        }
    }

    void ADD(std::vector<Item::Base> &items, Item::Base item)
    {
        if (items.size() > 0)
        {
            auto found = 0;

            for (auto i = 0; i < items.size(); i++)
            {
                if (items[i].Type == item.Type)
                {
                    found++;
                }
            }

            if (found == 0)
            {
                items.push_back(item);
            }
        }
        else
        {
            items.push_back(item);
        }
    }

    bool VERIFY(std::vector<Item::Base> &items, Item::Base item)
    {
        auto has = false;

        if (items.size() > 0)
        {
            for (auto i = 0; i < items.size(); i++)
            {
                if (items[i].Type == item.Type)
                {
                    has = true;

                    break;
                }
            }
        }

        return has;
    }

    int FIND(std::vector<int> list, int item)
    {
        auto found = -1;

        for (auto i = 0; i < list.size(); i++)
        {
            if (list[i] == item)
            {
                found = i;

                break;
            }
        }

        return found;
    }

    int FIND_TYPE(std::vector<Item::Base> list, Item::Type item)
    {
        auto found = -1;

        for (auto i = 0; i < list.size(); i++)
        {
            if (list[i].Type == item)
            {
                found = i;

                break;
            }
        }

        return found;
    }

    int COUNT_TYPES(std::vector<Item::Base> &list, Item::Type item)
    {
        auto found = 0;

        for (auto i = 0; i < list.size(); i++)
        {
            if (list[i].Type == item)
            {
                found++;
            }
        }

        return found;
    }

    int FIND_LEAST(std::vector<Item::Base> &list, Item::Type item)
    {
        auto found = -1;

        auto min = 255;

        for (auto i = 0; i < list.size(); i++)
        {
            if (list[i].Type == item)
            {
                if (list[i].Charge < min)
                {
                    found = i;

                    min = list[i].Charge;
                }
            }
        }

        return found;
    }

} // namespace Item
#endif
