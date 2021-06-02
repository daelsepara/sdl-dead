#ifndef __CHARACTER__HPP__
#define __CHARACTER__HPP__

#include <string>
#include <vector>

#include "codewords.hpp"
#include "items.hpp"
#include "skills.hpp"
#include "ships.hpp"

namespace Character
{
    enum class Type
    {
        CUSTOM = 0,
        ADVENTURER,
        BUCCANEER,
        CHANGELING,
        GYPSY,
        MARINER,
        SWASHBUCKLER,
        WARLOCK
    };

    class Base
    {
    public:
        std::string Name = "";

        std::string Description = "";

        Character::Type Type = Character::Type::CUSTOM;

        int Life = 10;

        int Money = 10;

        int ITEM_LIMIT = 8;

        int MAX_LIFE_LIMIT = 10;

        int SKILLS_LIMIT = 4;

        std::vector<Skill::Base> Skills = std::vector<Skill::Base>();

        std::vector<Item::Base> Items = std::vector<Item::Base>();

        std::vector<Codeword::Type> Codewords = std::vector<Codeword::Type>();

        std::vector<Item::Base> LostItems = std::vector<Item::Base>();

        std::vector<Skill::Base> LostSkills = std::vector<Skill::Base>();

        std::vector<Skill::Base> TemporarySkills = std::vector<Skill::Base>();

        Ship::Base Ship = Ship::NONE;

        int LostMoney = 0;

        int StoryID = 0;

#if defined(_WIN32) || defined(__arm__)
        long long Epoch = 0;
#else
        long Epoch = 0;
#endif

        Base()
        {
        }

        Base(const char *name, Character::Type type, const char *description, std::vector<Skill::Base> skills, int money)
        {
            Name = name;
            Type = type;
            Description = description;
            Skills = skills;
            Money = money;
        }

        Base(const char *name, Character::Type type, const char *description, std::vector<Skill::Base> skills, std::vector<Item::Base> items, int money)
        {
            Name = name;
            Type = type;
            Description = description;
            Skills = skills;
            Items = items;
            Money = money;
        }

        Base(const char *name, Character::Type type, const char *description, std::vector<Skill::Base> skills, std::vector<Item::Base> items, std::vector<Codeword::Type> codewords, int life, int money)
        {
            Name = name;
            Type = type;
            Description = description;
            Skills = skills;
            Items = items;
            Codewords = codewords;
            Life = life;
            Money = money;
        }
    };

    auto ADVENTURER = Character::Base("The Adventurer", Character::Type::ADVENTURER, "You have explored haunted castles, ruined cities, dank crypts and desolate forests in your constant search for gold and glory. Now try your luck on the high seas.", {Skill::FOLKLORE, Skill::ROGUERY, Skill::SEAFARING, Skill::SWORDPLAY}, {Item::SWORD}, 10);
    auto BUCCANEER = Character::Base("The Buccaneer", Character::Type::BUCCANEER, "You're a clever and resourceful pirate, loyal to your comrades and a deadly foe to anyone who crosses you.", {Skill::CUNNING, Skill::MARKSMANSHIP, Skill::SEAFARING, Skill::SWORDPLAY}, {Item::PISTOL, Item::SWORD}, 10);
    auto CHANGELING = Character::Base("The Changeling", Character::Type::CHANGELING, "Your origins are shrouded in mystery. A misfit in your own homeland, you wander far and wide in search of the truth.", {Skill::AGILITY, Skill::CUNNING, Skill::SPELLS, Skill::WILDERNESS_LORE}, {Item::MAGIC_WAND}, 10);
    auto GYPSY = Character::Base("The Gypsy", Character::Type::GYPSY, "Fleeing persecution in the Old World, you have come to the colonies of the New World to carve a new life of fame and fortune.", {Skill::BRAWLING, Skill::CHARMS, Skill::FOLKLORE, Skill::ROGUERY}, {Item::MAGIC_AMULET}, 10);
    auto MARINER = Character::Base("The Mariner", Character::Type::MARINER, "Born on the deck of a ship and raised with the salt breeze in your face, you have been toughened by the experience of a hundred ports and desert islands. No one can match your knowledge of the seven seas.", {Skill::AGILITY, Skill::SEAFARING, Skill::STREETWISE, Skill::WILDERNESS_LORE}, 10);
    auto SWASHBUCKLER = Character::Base("The Swashbuckler", Character::Type::SWASHBUCKLER, "With your dashing good looks, gallant wit, aristocratic manners and flair for stylish derring-do, you're a hero to your friends and a real pain in the neck to your enemies!", {Skill::AGILITY, Skill::CUNNING, Skill::STREETWISE, Skill::SWORDPLAY}, {Item::SWORD}, 10);
    auto WARLOCK = Character::Base("The Warlock", Character::Type::WARLOCK, "Your scholarly appeareance disguises the fact that you are one of the most powerful opponents a pirate captain could ever fear to face.", {Skill::CHARMS, Skill::MARKSMANSHIP, Skill::SPELLS, Skill::STREETWISE}, {Item::MAGIC_AMULET, Item::PISTOL, Item::MAGIC_WAND}, 10);
    auto CUSTOM = Character::Base("Custom Character", Character::Type::CUSTOM, "This is a player generated character.", {}, {}, 10);

    std::vector<Character::Base> Classes = {Character::ADVENTURER, Character::BUCCANEER, Character::CHANGELING, Character::GYPSY, Character::MARINER, Character::MARINER, Character::SWASHBUCKLER, Character::WARLOCK};

    int FIND_ITEM(Character::Base &player, Item::Type item)
    {
        auto found = -1;

        if (player.Items.size() > 0)
        {
            for (auto i = 0; i < player.Items.size(); i++)
            {
                if (player.Items[i].Type == item && player.Items[i].Charge != 0)
                {
                    found = i;

                    break;
                }
            }
        }

        return found;
    }

    int FIND_SKILL(Character::Base &player, Skill::Type skill)
    {
        auto found = -1;

        if (player.Skills.size() > 0)
        {
            for (auto i = 0; i < player.Skills.size(); i++)
            {
                if (player.Skills[i].Type == skill)
                {
                    found = i;

                    break;
                }
            }
        }

        return found;
    }

    bool VERIFY_ITEMS(Character::Base &player, std::vector<Item::Type> items)
    {
        auto found = 0;

        if (items.size() > 0)
        {
            for (auto i = 0; i < items.size(); i++)
            {
                auto result = Character::FIND_ITEM(player, items[i]);

                if (result >= 0)
                {
                    found++;
                }
            }
        }

        return found >= items.size();
    }

    int COUNT_ITEMS(Character::Base &player, std::vector<Item::Base> items)
    {
        auto found = 0;

        for (auto i = 0; i < items.size(); i++)
        {
            if (Character::FIND_ITEM(player, items[i].Type) >= 0)
            {
                found++;
            }
        }

        return found;
    }

    bool VERIFY_ITEMS_ANY(Character::Base &player, std::vector<Item::Base> items)
    {
        return Character::COUNT_ITEMS(player, items) > 0;
    }

    // Checks if player has the skill and the required item
    bool VERIFY_SKILL(Character::Base &player, Skill::Type skill)
    {
        auto found = false;

        if (player.Skills.size() > 0 && skill != Skill::Type::NONE)
        {
            for (auto i = 0; i < player.Skills.size(); i++)
            {
                if (player.Skills[i].Type == skill)
                {
                    if (player.Skills[i].Requirement != Item::Type::NONE)
                    {
                        found = Character::VERIFY_ITEMS(player, {player.Skills[i].Requirement});
                    }
                    else
                    {
                        found = true;
                    }

                    break;
                }
            }
        }

        if (!found && player.TemporarySkills.size() > 0 && skill != Skill::Type::NONE)
        {
            for (auto i = 0; i < player.TemporarySkills.size(); i++)
            {
                if (player.TemporarySkills[i].Type == skill)
                {
                    if (player.TemporarySkills[i].Requirement != Item::Type::NONE)
                    {
                        found = Character::VERIFY_ITEMS(player, {player.TemporarySkills[i].Requirement});
                    }
                    else
                    {
                        found = true;
                    }

                    break;
                }
            }
        }

        return found;
    }

    bool VERIFY_ANY_SKILLS(Character::Base &player, std::vector<Skill::Type> skills)
    {
        auto found = false;

        if (player.Skills.size() > 0 && skills.size() > 0)
        {
            for (auto i = 0; i < skills.size(); i++)
            {
                if (Character::VERIFY_SKILL(player, skills[i]))
                {
                    found = true;

                    break;
                }
            }
        }

        return found;
    }

    bool VERIFY_ALL_SKILLS(Character::Base &player, std::vector<Skill::Type> skills)
    {
        auto found = 0;

        if (player.Skills.size() > 0 && skills.size() > 0)
        {
            for (auto i = 0; i < skills.size(); i++)
            {
                if (Character::VERIFY_SKILL(player, skills[i]))
                {
                    found++;
                }
            }
        }

        return found == skills.size();
    }

    bool HAS_SKILL(Character::Base &player, Skill::Type skill)
    {
        auto found = false;

        if (player.Skills.size() > 0 && skill != Skill::Type::NONE)
        {
            for (auto i = 0; i < player.Skills.size(); i++)
            {
                if (player.Skills[i].Type == skill)
                {
                    found = true;

                    break;
                }
            }
        }

        return found;
    }

    int FIND_SKILL_ITEMS(Character::Base &player, Skill::Type skill, std::vector<Item::Type> items)
    {
        auto found = 0;

        if (player.Skills.size() > 0 && skill != Skill::Type::NONE && items.size() > 0)
        {
            for (auto i = 0; i < player.Skills.size(); i++)
            {
                if (player.Skills[i].Type == skill)
                {
                    for (auto j = 0; j < items.size(); j++)
                    {
                        if (Character::FIND_ITEM(player, items[j]) >= 0)
                        {
                            found++;
                        }
                    }
                }
            }
        }

        return found;
    }

    // verify that player has the skill and ANY of the items
    bool VERIFY_SKILL_ANY(Character::Base &player, Skill::Type skill, std::vector<Item::Type> items)
    {
        return Character::FIND_SKILL_ITEMS(player, skill, items) > 0;
    }

    // verify that player has the skill and ALL of the items
    bool VERIFY_SKILL_ALL(Character::Base &player, Skill::Type skill, std::vector<Item::Type> items)
    {
        return Character::FIND_SKILL_ITEMS(player, skill, items) == items.size();
    }

    bool VERIFY_SKILL_ITEM(Character::Base &player, Skill::Type skill, Item::Type item)
    {
        return Character::VERIFY_SKILL_ALL(player, skill, {item});
    }

    int FIND_CODEWORD(Character::Base &player, Codeword::Type codeword)
    {
        auto found = -1;

        if (player.Codewords.size() > 0)
        {
            for (auto i = 0; i < player.Codewords.size(); i++)
            {
                if (player.Codewords[i] == codeword)
                {
                    found = i;

                    break;
                }
            }
        }

        return found;
    }

    int FIND_CODEWORDS(Character::Base &player, std::vector<Codeword::Type> codewords)
    {
        auto found = 0;

        if (player.Codewords.size() > 0 && codewords.size() > 0)
        {
            for (auto i = 0; i < codewords.size(); i++)
            {
                auto result = Character::FIND_CODEWORD(player, codewords[i]);

                if (result >= 0)
                {
                    found++;
                }
            }
        }

        return found;
    }

    bool VERIFY_CODEWORDS_ANY(Character::Base &player, std::vector<Codeword::Type> codewords)
    {
        return Character::FIND_CODEWORDS(player, codewords) > 0;
    }

    bool VERIFY_CODEWORDS_ALL(Character::Base &player, std::vector<Codeword::Type> codewords)
    {
        return Character::FIND_CODEWORDS(player, codewords) == codewords.size();
    }

    bool VERIFY_CODEWORD(Character::Base &player, Codeword::Type codeword)
    {
        return Character::VERIFY_CODEWORDS_ALL(player, {codeword});
    }

    bool VERIFY_LIFE(Character::Base &player, int threshold = 0)
    {
        return player.Life > threshold;
    }

    bool VERIFY_POSSESSIONS(Character::Base &player)
    {
        return player.Items.size() <= player.ITEM_LIMIT;
    }

    void GET_ITEMS(Character::Base &player, std::vector<Item::Base> items)
    {
        player.Items.insert(player.Items.end(), items.begin(), items.end());
    }

    void GET_CODEWORDS(Character::Base &player, std::vector<Codeword::Type> codewords)
    {
        for (auto i = 0; i < codewords.size(); i++)
        {
            if (!Character::VERIFY_CODEWORD(player, codewords[i]))
            {
                player.Codewords.push_back(codewords[i]);
            }
        }
    }

    void REMOVE_CODEWORD(Character::Base &player, Codeword::Type codeword)
    {
        if (Character::VERIFY_CODEWORD(player, codeword))
        {
            auto result = FIND_CODEWORD(player, codeword);

            if (result >= 0)
            {
                player.Codewords.erase(player.Codewords.begin() + result);
            }
        }
    }

    void GET_UNIQUE_ITEMS(Character::Base &player, std::vector<Item::Base> items)
    {
        for (auto i = 0; i < items.size(); i++)
        {
            if (!Character::VERIFY_ITEMS(player, {items[i].Type}))
            {
                player.Items.push_back(items[i]);
            }
        }
    }

    void LOSE_ITEMS(Character::Base &player, std::vector<Item::Type> items)
    {
        if (player.Items.size() > 0 && items.size() > 0)
        {
            for (auto i = 0; i < items.size(); i++)
            {
                auto result = Character::FIND_ITEM(player, items[i]);

                if (result >= 0)
                {
                    player.Items.erase(player.Items.begin() + result);
                }
            }
        }
    }

    void LOSE_SKILLS(Character::Base &player, std::vector<Skill::Type> skills)
    {
        if (player.Skills.size() > 0 && skills.size() > 0)
        {
            for (auto i = 0; i < skills.size(); i++)
            {
                auto result = Character::FIND_SKILL(player, skills[i]);

                if (result >= 0)
                {
                    player.LostSkills.push_back(player.Skills[result]);

                    player.Skills.erase(player.Skills.begin() + result);
                }
            }
        }
    }

    void GAIN_LIFE(Character::Base &player, int life)
    {
        player.Life += life;

        if (player.Life < 0)
        {
            player.Life = 0;
        }
        else if (player.Life > player.MAX_LIFE_LIMIT)
        {
            player.Life = player.MAX_LIFE_LIMIT;
        }
    }

    void GAIN_MONEY(Character::Base &player, int money)
    {
        player.Money += money;

        if (player.Money < 0)
        {
            player.Money = 0;
        }
    }

    void LOSE_POSSESSIONS(Character::Base &player)
    {
        player.LostItems = player.Items;

        player.Items.clear();
    }

    void LOSE_ALL(Character::Base &player)
    {
        player.LostMoney = player.LostMoney;
        player.Money = 0;

        Character::LOSE_POSSESSIONS(player);
    }

    void TAKE_SHIP(Character::Base &player, Ship::Base ship)
    {
        player.Ship = ship;
    }

    void LOSE_SHIP(Character::Base &player)
    {
        player.Ship = Ship::NONE;
    }

    void DAMAGE_SHIP(Character::Base &player, int damage)
    {
        if (player.Ship.Type != Ship::Type::NONE)
        {
            player.Ship.Stars -= damage;

            if (player.Ship.Stars < 0)
            {
                player.Ship.Stars = 0;
            }
        }
    }

    bool CHECK_SHIP(Character::Base &player)
    {
        auto condition = false;

        if (player.Ship.Type != Ship::Type::NONE)
        {
            condition = player.Ship.Stars > 0;
        }

        return condition;
    }

    bool HAS_FOOD(Character::Base &player, int threshold)
    {
        return Item::COUNT_TYPES(player.Items, Item::Type::PROVISIONS) > threshold;
    }

    int CONSUME_FOOD(Character::Base &player, int amount)
    {
        auto consumed = 0;

        if (HAS_FOOD(player, 0))
        {
            for (auto i = 0; i < amount; i++)
            {
                if (Character::VERIFY_ITEMS(player, {Item::Type::PROVISIONS}))
                {
                    Character::LOSE_ITEMS(player, {Item::Type::PROVISIONS});

                    consumed++;
                }
            }
        }

        return consumed;
    }

} // namespace Character

#endif
