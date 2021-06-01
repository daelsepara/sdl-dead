#ifndef __SKILLS__HPP__
#define __SKILLS__HPP__

#include <vector>

#include "items.hpp"

namespace Skill
{
    enum class Type
    {
        NONE = -1,
        AGILITY,
        BRAWLING,
        CHARMS,
        CUNNING,
        FOLKLORE,
        MARKSMANSHIP,
        ROGUERY,
        SEAFARING,
        SPELLS,
        STREETWISE,
        SWORDPLAY,
        WILDERNESS_LORE        
    };

    class Base
    {
    public:
        const char *Name = NULL;
        const char *Description = NULL;
        Skill::Type Type;
        Item::Type Requirement = Item::Type::NONE;

        Base(const char *name, const char *description, Skill::Type type, Item::Type item)
        {
            Name = name;
            Type = type;
            Description = description;
            Requirement = item;
        }

        Base(const char *name, const char *description, Skill::Type type)
        {
            Name = name;
            Type = type;
            Description = description;
            Requirement = Item::Type::NONE;
        }
    };

    auto AGILITY = Skill::Base("AGILITY", "The ability to perform acrobatic feats, run, climb, balance and leap. A character with this skill is nimble and dexterous.", Skill::Type::AGILITY);
    auto BRAWLING = Skill::Base("BRAWLING", "Fisticuffs, wrestling holds, jabs and kicks, and the tricks of infighting. Not as effective as SWORDPLAY, but you do not need weapons - your own body is the weapon!", Skill::Type::BRAWLING);
    auto CHARMS = Skill::Base("CHARMS", "The expert use of magical wards to protect you from danger. Also includes that most elusive of qualities: luck. You must possess a MAGIC AMULET to use this skill.", Skill::Type::CHARMS, Item::Type::MAGIC_AMULET);
    auto CUNNING = Skill::Base("CUNNING", "The ability to think on your feet and devise clever schemes for getting out of trouble. Useful in countless situations.", Skill::Type::CUNNING);
    auto FOLKLORE = Skill::Base("FOLKLORE", "Knowledge of myth and legend, and how best to deal with supernatural menaces such as garlic against vampires, silver bullets against a werewolf, and so on.", Skill::Type::FOLKLORE);
    auto MARKSMANSHIP = Skill::Base("MARKSMANSHIP", "A long-range attack skill. You must possess a PISTOL to use this skill.", Skill::Type::MARKSMANSHIP, Item::Type::PISTOL);
    auto ROGUERY = Skill::Base("ROGUERY", "The traditional repertoire of a thief's tricks: picking pockets, opening locks, and skulking unseen in the shadows.", Skill::Type::ROGUERY);
    auto SEAFARING = Skill::Base("SEAFARING", "Knowing all about life at sea, including the ability to handle anything from a rowing boat right up to a large sailing ship.", Skill::Type::SEAFARING);
    auto SPELLS = Skill::Base("SPELLS", "A range of magical effects encompassing illusions, elemental effects, commands, and summonings. You must possess a MAGIC WAND to use this skill.", Skill::Type::SPELLS, Item::Type::MAGIC_WAND);
    auto STREETWISE = Skill::Base("STREETWISE", "With this skill you are never at a loss in towns and cities. What others see as the squalor and menace of narrow cobbed streets is home to you.", Skill::Type::STREETWISE);
    auto SWORDPLAY = Skill::Base("SWORDPLAY", "The best fighting skill. You must possess a SWORD to use this skill.", Skill::Type::SWORDPLAY, Item::Type::SWORD);
    auto WILDERNESS_LORE = Skill::Base("WILDERNESS LORE", "A talent for survival in the wild - whether it be forest, desert, swamp or mountain peak.", Skill::Type::WILDERNESS_LORE);

    std::vector<Skill::Base> ALL = {Skill::AGILITY, Skill::BRAWLING, Skill::CHARMS, Skill::CUNNING, Skill::FOLKLORE, Skill::MARKSMANSHIP, Skill::ROGUERY, Skill::SEAFARING, Skill::SPELLS, Skill::STREETWISE, Skill::SWORDPLAY, Skill::WILDERNESS_LORE};

    int FIND(std::vector<Skill::Base> &skills, Skill::Type skill)
    {
        auto found = -1;

        if (skills.size() > 0 && skill != Skill::Type::NONE)
        {
            for (auto i = 0; i < skills.size(); i++)
            {
                if (skills[i].Type == skill)
                {
                    found = i;

                    break;
                }
            }
        }

        return found;
    }

    int FIND_LIST(std::vector<int> selection, int item)
    {
        auto found = -1;
        
        for (auto i = 0; i < selection.size(); i ++)
        {
            if (selection[i] == item)
            {
                found = i;

                break;
            }
        }

        return found;
    }

    bool VERIFY(std::vector<Skill::Base> &skills, Skill::Base skill)
    {
        return FIND(skills, skill.Type) >= 0;
    }

    void ADD(std::vector<Skill::Base> &skills, Skill::Base skill)
    {
        if (!VERIFY(skills, skill))
        {
            skills.push_back(skill);
        }
    }

    void REMOVE(std::vector<Skill::Base> &skills, Skill::Base skill)
    {
        auto result = FIND(skills, skill.Type);

        if (result >= 0)
        {
            skills.erase(skills.begin() + result);
        }
    }

} // namespace Skill

#endif
