#ifndef __STORY__HPP__
#define __STORY__HPP__

#include <vector>

#include "constants.hpp"
#include "controls.hpp"
#include "codewords.hpp"
#include "items.hpp"
#include "skills.hpp"
#include "character.hpp"

namespace Choice
{
    enum class Type
    {
        NORMAL = 0, // No requirements
        ITEMS,
        GET_ITEMS,
        SKILL,
        CODEWORD,
        MONEY,
        LIFE,
        ANY_ITEM,
        ANY_SKILL,
        SKILL_ITEM,
        SKILL_ANY,
        SKILL_ALL,
        FIRE_WEAPON,
        LOSE_ITEMS,
        LOSE_MONEY,
        LOSE_ALL,
        LOSE_SKILLS,
        GET_CODEWORD,
        LOSE_CODEWORD,
        GAIN_MONEY,
        GIVE,
        BUY_VEHICLE
    };

    class Base
    {
    public:
        const char *Text = NULL;

        Choice::Type Type = Choice::Type::NORMAL;

        Skill::Type Skill = Skill::Type::NONE;

        std::vector<Item::Base> Items = std::vector<Item::Base>();

        Codeword::Type Codeword = Codeword::Type::NONE;

        Ship::Type Ship = Ship::Type::NONE;

        int Value = 0;

        int Destination = -1;

        Base(Choice::Type type, const char *text, int destination, Skill::Type skill, std::vector<Item::Base> items, int value)
        {
            Type = type;
            Text = text;
            Destination = destination;
            Items = items;
            Skill = skill;
            Value = value;
        }

        Base(const char *text, int destination)
        {
            Text = text;
            Destination = destination;
        }

        Base(const char *text, int destination, Skill::Type skill, std::vector<Item::Base> items)
        {
            Text = text;
            Destination = destination;
            Type = Choice::Type::SKILL_ITEM;
            Items = items;
            Skill = skill;
        }

        Base(const char *text, int destination, std::vector<Item::Base> items)
        {
            Text = text;
            Destination = destination;
            Type = Choice::Type::ITEMS;
            Items = items;
        }

        Base(const char *text, int destination, Skill::Type skill)
        {
            Text = text;
            Destination = destination;
            Type = Choice::Type::SKILL;
            Skill = skill;
        }

        Base(const char *text, int destination, Codeword::Type codeword)
        {
            Text = text;
            Destination = destination;
            Type = Choice::Type::CODEWORD;
            Codeword = codeword;
        }

        Base(const char *text, int destination, Choice::Type type, int value)
        {
            Text = text;
            Destination = destination;
            Type = type;
            Value = value;
        }

        Base(const char *text, int destination, Choice::Type type)
        {
            Text = text;
            Destination = destination;
            Type = type;
        }

        Base(const char *text, int destination, Choice::Type type, std::vector<Item::Base> items)
        {
            Text = text;
            Destination = destination;
            Type = type;
            Items = items;
        }

        Base(const char *text, int destination, Choice::Type type, Skill::Type skill, std::vector<Item::Base> items)
        {
            Text = text;
            Destination = destination;
            Type = type;
            Skill = skill;
            Items = items;
        }

        Base(const char *text, int destination, Choice::Type type, std::vector<Item::Base> items, int value)
        {
            Text = text;
            Destination = destination;
            Type = type;
            Items = items;
            Value = value;
        }

        Base(const char *text, int destination, Choice::Type type, Codeword::Type codeword)
        {
            Text = text;
            Destination = destination;
            Type = type;
            Codeword = codeword;
        }

        Base(const char *text, int destination, Choice::Type type, Ship::Type ship)
        {
            Text = text;
            Destination = destination;
            Type = type;
            Ship = ship;
        }

        Base(const char *text, int destination, Choice::Type type, Ship::Type ship, int value)
        {
            Text = text;
            Destination = destination;
            Type = type;
            Ship = ship;
            Value = value;
        }
    };
} // namespace Choice

namespace Story
{
    enum class Type
    {
        NORMAL = 0,
        GOOD,
        DOOM
    };

    enum class Controls
    {
        NONE = 0,
        STANDARD,
        SHOP,
        BUY_AND_SELL,
        SELL,
        TRADE
    };

    class Base
    {
    public:
        int ID = 0;

        const char *Text = NULL;

        const char *Title = NULL;

        const char *Bye = NULL;

        const char *Image = NULL;

        Story::Controls Controls = Story::Controls::NONE;

        std::vector<Choice::Base> Choices = std::vector<Choice::Base>();

        std::vector<std::pair<Item::Base, int>> Shop = std::vector<std::pair<Item::Base, int>>();
        std::vector<std::pair<Item::Base, int>> Sell = std::vector<std::pair<Item::Base, int>>();

        std::pair<Item::Base, Item::Base> Trade;

        // Player selects items to take up to a certain limit
        std::vector<Item::Base> Take = std::vector<Item::Base>();

        // Player selects items to lose
        std::vector<Item::Base> ToLose = std::vector<Item::Base>();

        int Limit = 0;

        int LimitSkills = 0;

        Ship::Type Ship = Ship::Type::NONE;

        Story::Type Type = Story::Type::NORMAL;

        // Handle background events
        virtual int Background(Character::Base &player) { return -1; };

        // Handle events before story branches
        virtual void Event(Character::Base &player){};

        // Jump to next section
        virtual int Continue(Character::Base &player) { return -1; };

        Base()
        {
        }

        Base(int id)
        {
            ID = id;
        }

        Base(int id, const char *text, Story::Type type)
        {
            ID = id;
            Text = text;
            type = type;
        }

        Base(const char *text, Story::Type type)
        {
            Text = text;
            type = type;
        }
    };

    std::vector<Button> StandardControls(bool compact = false)
    {
        auto idx = 0;

        auto controls = std::vector<Button>();

        if (!compact)
        {
            controls.push_back(Button(0, "icons/up-arrow.png", 0, 1, 0, 1, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + border_space, Control::Type::SCROLL_UP));
            controls.push_back(Button(1, "icons/down-arrow.png", 0, 2, 0, 2, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + text_bounds - arrow_size - border_space, Control::Type::SCROLL_DOWN));

            idx = 2;
        }

        controls.push_back(Button(idx, "icons/map.png", idx, idx + 1, compact ? idx : 1, idx, startx, buttony, Control::Type::MAP));
        controls.push_back(Button(idx + 1, "icons/disk.png", idx, idx + 2, compact ? idx + 1 : 1, idx + 1, startx + gridsize, buttony, Control::Type::GAME));
        controls.push_back(Button(idx + 2, "icons/user.png", idx + 1, idx + 3, compact ? idx + 2 : 1, idx + 2, startx + 2 * gridsize, buttony, Control::Type::CHARACTER));
        controls.push_back(Button(idx + 3, "icons/items.png", idx + 2, idx + 4, compact ? idx + 3 : 1, idx + 3, startx + 3 * gridsize, buttony, Control::Type::USE));
        controls.push_back(Button(idx + 4, "icons/next.png", idx + 3, idx + 5, compact ? idx + 4 : 1, idx + 4, startx + 4 * gridsize, buttony, Control::Type::NEXT));
        controls.push_back(Button(idx + 5, "icons/exit.png", idx + 4, idx + 5, compact ? idx + 5 : 1, idx + 5, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

        return controls;
    }

    std::vector<Button> ShopControls(bool compact = false)
    {
        auto idx = 0;

        auto controls = std::vector<Button>();

        if (!compact)
        {
            controls.push_back(Button(0, "icons/up-arrow.png", 0, 1, 0, 1, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + border_space, Control::Type::SCROLL_UP));
            controls.push_back(Button(1, "icons/down-arrow.png", 0, 2, 0, 2, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + text_bounds - arrow_size - border_space, Control::Type::SCROLL_DOWN));

            idx = 2;
        }

        controls.push_back(Button(idx, "icons/map.png", idx, idx + 1, compact ? idx : 1, idx, startx, buttony, Control::Type::MAP));
        controls.push_back(Button(idx + 1, "icons/disk.png", idx, idx + 2, compact ? idx + 1 : 1, idx + 1, startx + gridsize, buttony, Control::Type::GAME));
        controls.push_back(Button(idx + 2, "icons/user.png", idx + 1, idx + 3, compact ? idx + 2 : 1, idx + 2, startx + 2 * gridsize, buttony, Control::Type::CHARACTER));
        controls.push_back(Button(idx + 3, "icons/items.png", idx + 2, idx + 4, compact ? idx + 3 : 1, idx + 3, startx + 3 * gridsize, buttony, Control::Type::USE));
        controls.push_back(Button(idx + 4, "icons/next.png", idx + 3, idx + 5, compact ? idx + 4 : 1, idx + 4, startx + 4 * gridsize, buttony, Control::Type::NEXT));
        controls.push_back(Button(idx + 5, "icons/shop.png", idx + 4, idx + 6, compact ? idx + 5 : 1, idx + 5, startx + 5 * gridsize, buttony, Control::Type::SHOP));
        controls.push_back(Button(idx + 6, "icons/exit.png", idx + 5, idx + 6, compact ? idx + 6 : 1, idx + 6, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

        return controls;
    }

    std::vector<Button> SellControls(bool compact = false)
    {
        auto idx = 0;

        auto controls = std::vector<Button>();

        if (!compact)
        {
            controls.push_back(Button(0, "icons/up-arrow.png", 0, 1, 0, 1, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + border_space, Control::Type::SCROLL_UP));
            controls.push_back(Button(1, "icons/down-arrow.png", 0, 2, 0, 2, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + text_bounds - arrow_size - border_space, Control::Type::SCROLL_DOWN));

            idx = 2;
        }

        controls.push_back(Button(idx, "icons/map.png", idx, idx + 1, compact ? idx : 1, idx, startx, buttony, Control::Type::MAP));
        controls.push_back(Button(idx + 1, "icons/disk.png", idx, idx + 2, compact ? idx + 1 : 1, idx + 1, startx + gridsize, buttony, Control::Type::GAME));
        controls.push_back(Button(idx + 2, "icons/user.png", idx + 1, idx + 3, compact ? idx + 2 : 1, idx + 2, startx + 2 * gridsize, buttony, Control::Type::CHARACTER));
        controls.push_back(Button(idx + 3, "icons/items.png", idx + 2, idx + 4, compact ? idx + 3 : 1, idx + 3, startx + 3 * gridsize, buttony, Control::Type::USE));
        controls.push_back(Button(idx + 4, "icons/next.png", idx + 3, idx + 5, compact ? idx + 4 : 1, idx + 4, startx + 4 * gridsize, buttony, Control::Type::NEXT));
        controls.push_back(Button(idx + 5, "icons/selling.png", idx + 4, idx + 6, compact ? idx + 5 : 1, idx + 5, startx + 5 * gridsize, buttony, Control::Type::SELL));
        controls.push_back(Button(idx + 6, "icons/exit.png", idx + 5, idx + 6, compact ? idx + 6 : 1, idx + 6, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

        return controls;
    }

    std::vector<Button> BuyAndSellControls(bool compact = false)
    {
        auto idx = 0;

        auto controls = std::vector<Button>();

        if (!compact)
        {
            controls.push_back(Button(0, "icons/up-arrow.png", 0, 1, 0, 1, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + border_space, Control::Type::SCROLL_UP));
            controls.push_back(Button(1, "icons/down-arrow.png", 0, 2, 0, 2, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + text_bounds - arrow_size - border_space, Control::Type::SCROLL_DOWN));

            idx = 2;
        }

        controls.push_back(Button(idx, "icons/map.png", idx, idx + 1, compact ? idx : 1, idx, startx, buttony, Control::Type::MAP));
        controls.push_back(Button(idx + 1, "icons/disk.png", idx, idx + 2, compact ? idx + 1 : 1, idx + 1, startx + gridsize, buttony, Control::Type::GAME));
        controls.push_back(Button(idx + 2, "icons/user.png", idx + 1, idx + 3, compact ? idx + 2 : 1, idx + 2, startx + 2 * gridsize, buttony, Control::Type::CHARACTER));
        controls.push_back(Button(idx + 3, "icons/items.png", idx + 2, idx + 4, compact ? idx + 3 : 1, idx + 3, startx + 3 * gridsize, buttony, Control::Type::USE));
        controls.push_back(Button(idx + 4, "icons/next.png", idx + 3, idx + 5, compact ? idx + 4 : 1, idx + 4, startx + 4 * gridsize, buttony, Control::Type::NEXT));
        controls.push_back(Button(idx + 5, "icons/shop.png", idx + 4, idx + 6, compact ? idx + 5 : 1, idx + 5, startx + 5 * gridsize, buttony, Control::Type::SHOP));
        controls.push_back(Button(idx + 6, "icons/selling.png", idx + 5, idx + 7, compact ? idx + 6 : 1, idx + 6, startx + 6 * gridsize, buttony, Control::Type::SELL));
        controls.push_back(Button(idx + 7, "icons/exit.png", idx + 6, idx + 7, compact ? idx + 7 : 1, idx + 7, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

        return controls;
    }

    std::vector<Button> TradeControls(bool compact = false)
    {
        auto idx = 0;

        auto controls = std::vector<Button>();

        if (!compact)
        {
            controls.push_back(Button(0, "icons/up-arrow.png", 0, 1, 0, 1, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + border_space, Control::Type::SCROLL_UP));
            controls.push_back(Button(1, "icons/down-arrow.png", 0, 2, 0, 2, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + text_bounds - arrow_size - border_space, Control::Type::SCROLL_DOWN));

            idx = 2;
        }

        controls.push_back(Button(idx, "icons/map.png", idx, idx + 1, compact ? idx : 1, idx, startx, buttony, Control::Type::MAP));
        controls.push_back(Button(idx + 1, "icons/disk.png", idx, idx + 2, compact ? idx + 1 : 1, idx + 1, startx + gridsize, buttony, Control::Type::GAME));
        controls.push_back(Button(idx + 2, "icons/user.png", idx + 1, idx + 3, compact ? idx + 2 : 1, idx + 2, startx + 2 * gridsize, buttony, Control::Type::CHARACTER));
        controls.push_back(Button(idx + 3, "icons/items.png", idx + 2, idx + 4, compact ? idx + 3 : 1, idx + 3, startx + 3 * gridsize, buttony, Control::Type::USE));
        controls.push_back(Button(idx + 4, "icons/next.png", idx + 3, idx + 5, compact ? idx + 4 : 1, idx + 4, startx + 4 * gridsize, buttony, Control::Type::NEXT));
        controls.push_back(Button(idx + 5, "icons/shop.png", idx + 4, idx + 6, compact ? idx + 5 : 1, idx + 5, startx + 5 * gridsize, buttony, Control::Type::TRADE));
        controls.push_back(Button(idx + 6, "icons/exit.png", idx + 5, idx + 6, compact ? idx + 6 : 1, idx + 6, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

        return controls;
    }

    std::vector<Button> ExitControls()
    {
        auto controls = std::vector<Button>();

        controls.push_back(Button(0, "icons/exit.png", 0, 0, -1, -1, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

        return controls;
    }

} // namespace Story

class NotImplemented : public Story::Base
{
public:
    NotImplemented()
    {
        ID = -1;

        Title = "Not implemented yet";

        Controls = Story::Controls::NONE;
    }
};

auto notImplemented = NotImplemented();

auto Stories = std::vector<Story::Base *>();

void *findStory(int id)
{
    Story::Base *story = &notImplemented;

    if (Stories.size() > 0)
    {
        for (auto i = 0; i < Stories.size(); i++)
        {
            if (((Story::Base *)Stories[i])->ID == id)
            {
                story = (Story::Base *)Stories[i];

                break;
            }
        }
    }

    return story;
}

class Prologue : public Story::Base
{
public:
    Prologue()
    {
        ID = 0;

        Text = "\"Pirates!\" The roar of cannonfire thunders across the waves as word leaves the captain's lips. Hurtling out of the billowing plumes of smoke come a barrage of iron shells. Each is larger than a man's fist, and strikes with a force that splinters the oak beams of your ship and shatters men's skulls like eggs. The mainmast takes a direct hit and topples, crushing the sailors standing under it.\n\nA grappling hook latches onto the rail. The pirates are getting ready to board you. Rushing to the side, you see their sinister vessel drawing alongside, black sails flapping in the breeze like a carrion-bird's wings. Her prow has the face of a medieval gargoyle. You read the name painted on her bows: the Belle Dame. But there is no look of beauty about her, nor hint of mercy on the faces of the eager brigands lining her rail.\n\nA crewman standing beside you utters a groan of fear. \"It's Skarvench's ship.\"\n\n\"Who's he?\" you ask, having to shout over the din of cannon shots and the pirates' battle-cries.\n\nHe stares at you as though you are a simpleton, and then remembers that this is your first voyage to the New World. \"The worst man that ever lived,\" is his blunt reply. And then the ships come together and the pirates are upon you.\n\nRushing headlong into the terrified crew, the pirates cleave a swathe of gory death across the ship's deck, their cutlasses rising and falling like scythes. You see the ship's officers fighting valiantly to defend the helm, but they are hopelessly outnumbered and soon butchered at their post. The fierce grins on the pirate's faces tell you that they expect easy pickings. You narrow your eyes as anger wells up inside you. You know that you will die today, but you feel no fear -- only a cold determination to sell your life dearly. Two pirates lunge at you. You duck the swing of the first, catch his arm and throw him against his crony. The sword intended for you ends up in a pirate's belly, and his knife comes up by reflex to slash at the man who has inadvertently impaled him.\n\n\"Two down...\" You turn, and then for the first time you clap eyes on Skarvench himself. He stands astride the rail, grasping a grappling-line in one hand and a pistol in the other, whipping his sea-dogs into a killing frenzy with his evil laughter. His broad back and gangling limbs make him look like a massive crow. His beard is as long and lank as seaweed, and a single eye blazes beneath his bald brow -- the other is covered by a leather patch.\n\nHe is raising his pistol. You are rooted to the spot under his baleful stare. It can't be fear you're feeling surely...\n\n\"Ah, matey,\" he says with a brown-toothed grin. \"Got to kill you again, 'ave I?\"\n\nAgain..? You have no time to ponder this enigma. In the next instant, he fires his pistol and your whole world goes black.\n\n--\n\nYou sit up with a gasp, sweat soaking your clothes.\n\n\"You've 'ad that dream again, eh?\"\n\nYou look around, memory trickling back as the dream recedes. The slow creaking of a ship's timbers, the unhurried heave of the waves... you are in the stuffy confines of the Belle Dame's bowels. Sailors snore fitfully around you, catching some sleep between chores. In the glimmer of an oil lamp sits Old Marshy, the ship's carpenter, whittling at a stick of wood. He glances across at you, shaking his head sadly. \"It was two years ago. Don't know why you can't stop 'aving the dreams.\"\n\n\"Dreams? Nightmares!\" you say, mopping the sweat away. As you do, you feel the scar across your forehead where Skarvench's bullet struck you. A finger's breadth to the right -- one less tot of rum for Skarvench's breakfast that fateful morning! -- and your brains would have been blown out. As it is the bullet only grazed you, leaving the visible mark on your head and the scar of hatred deep in your heart.\n\nNow that the nightmare has washed away, you recall the two years that have passed since that day. When you were first brought aboard the Belle Dame, Skarvench deemed you too insignificant to ransom and too close to death to be worth pressing into service. He would have cast you into the deep and never had a qualm -- that was the fate of most who survived the battle -- but Old Marshy undertook to nurse you back to health. You can well remember the weeks it took to get your strength back -- weeks experienced like glimpses in broken glass, because of fever. You remember Old Marshy holding the wooden spoons of gruel to your lips until his thin arms trembled with tiredness, urging you to eat. You remember the shouts of the pirates as they toiled in the rigging, and their drunken laughter under the stars at night. And most of all you remember Skarvench, looming through your thoughts like the embodiment of cruelty, striding the deck and waiting for you to die.\n\nYou did not die; thanks to Old Marshy you regained your strength. But death might have been better than the living hell you have had to endure these two years as an ordinary seaman aboard the cruellest ship to sail the Carab Sea. Skarvench metes out discipline as the whim takes him, revelling in the suffering of others; pain is his wine, and death his meat. Often you have had to stand by and watch a man whipped for the slightest mistake. Sometimes you have felt that whip yourself -- all to raucous laughter of Skarvench and his vicious pirate band.\n\n\"All hands on deck!\" Hearing the command, you shake the other sailors awake and hurry up out of the dingy confines of the orlop deck into the blaze of daylight.\n\nSkarvench stands on the poopdeck. The ox-like first mate, Porbuck gives you a shove and growls, \"You , get up in the rigging.\" As you climb, you glance out to sea. A small ship lies off the port bow and the Belle Dame is rapidly closing on her. You see a tall wooden crucifix standing amidships; she has no cannon. That is foolhardy. \"Go to sea on a prayer,\" as the adage goes, \"but take a keg of powder too.\"\n\nYou understand the reason for the other ship's lack of weaponry when you get a better view of the men lining her rail. They're all monks!\n\nSkarvench's voice goes snarling across the water. \"Heave to or be blown out o' the water!\" he calls. \"We'll be takin' your treasure, holy or not!\"\n\n\"We have no treasure,\" calls back one of the monks. \"We are poor brothers of the Saviour, travelling to the New World to spread His message to the heathen.\"\n\nSkarvench smiles -- always a sign of his bad temper -- and says, \"Is that so? Well, I know of no place more heathen than the ocean bed.\" He leans on the poopdeck rail and calls to the master gunner: \"Mister Borograve, prepare to give 'em a broadside. I want their shaved heads sent forty fathoms deep, where heaven can't hear their mealy-mouthed prayers!\"\n\nThe monks know they cannot outrun the Belle Dame. As Borograve orders the cannons primed, they begin to sing a hymn. It is a glorious and peaceful sound that reminds you of the meadows and villages of your homeland. Most of the sailors pause in their duties, overcome by the melancholy beauty of the song. Even one or two of the pirates look uneasy at what they are about to do.\n\n\"Prepare to fire,\" says Skarvench, keen as a hound at the scent of a kill.\n\n\"No!\" A carpenter's hammer goes flying through the air and strikes Skarvench's head with a crack loud enough to carry up to where you sit in the rigging. Skarvench remains as steady as a rock, his hand flashing out with the startling speed to snatch the hammer out of the air as it falls. then he turns. His face is a mask of white fury. The fact that there is a stream of blood flowing from his temple only makes him look all the more terrible. His gaze bores along the deck and finds:\n\n\"Mister Marsh! This your hammer, is it?\"\n\nOld Marshy quails, his one jot of boldness used up. \"B-but, Cap'n... they're holy men! I don't think...\n\nSkarvench tastes his own blood on his lip and savours it with his tongue. He gestures to a couple of pirates, and Old Marshy is seized and dragged up to the poopdeck. \"Lay his head on the rail there, lads,\" says Skarvench in a voice like honeyed venom. He raises the hammer. \"You're right, Mister Marsh; you don't think. That's the trouble with having nothin' in your brain-pan, see?\"\n\nFar too late, you realise what Skarvench is going to do. You give a gasp and start down through the rigging. But even as you act, you know there is nothing you can do...\n\nThe hammer smashes down. It sounds like a wineflask breaking. The ordinary seamen look away in horror. The pirates grin gleefully like their captain, excited by the grisly sight. The corpse slumps to the deck.\n\n\"God curse you, Skarvench,\" you mutter under your breath as you reach the foot of the mast. \"I'll see you dead for that.\"\n\n\"You're not alone in wishing that,\" whispers a voice, \"but I'd stow such talk unless you want your own skull under the hammer next.\"\n\nYou look around to see three of the crew -- Grimes, Oakley and Blutz -- men who, like you, were taken off plundered ships and force to work for the pirates. \"We've a plan,\" continues Grimes in a low voice. \"If we stay aboard this devil ship our days are surely numbered, so tonight we plan to jump ship. We're scheduled to take the evening watch. We'll lower the jollyboat with a few supplies, then strike out towards Port Leshand.\"\n\n\"Five hundred leagues of open ocean in a tiny boat like that!\" you gasp. \"It's near certain death.\"\n\n\"Better than certain death, which is what we can expect here,\" mutters Oakley. \"Look, you've got a reputation of being a handy customer to have along in a tight spot. To be honest, we haven't got much of a chance without you. Now, are you with us?\"\n\nYou glare back up at the tall stooped figure on the poopdeck. He stamps to and fro, the brain-smeared hammer still in his hand, annoyed that the monks made their getaway while he was distracted by Old Marshy. You'll make him pay for his crimes one day, but you know the moment is not yet right.\n\nYou turn to Grimes and the others and give a swift nod. \"I'm with you.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 1; }
};

class Story001 : public Story::Base
{
public:
    Story001()
    {
        ID = 1;

        Image = "images/filler1-green.png";

        Text = "You know that you will need supplies to have any chance of survival on the open sea. It means taking a big risk, since you will have to go right past the officers' cabins, but there is no help for it. While your comrades keep a nervous vigil, fearing discovery at any moment, you creep aft and descend below decks. The only light in the passage is the glow of an oil-lamp shining from the half-open door of Skarvench's cabin. As you skulk forward through the shadows, you hear the voice of the pirate captain raised in typically drunken bluster:\n\n\"What, my merry lads, is the easiest route to fortune, would you say?\"\n\n\"Why, piracy, Cap'n,\" you hear one of the men answer hurriedly.\n\n\"Aye, piracy, right enough,\" roars Skarvench. \"but what's the most profitable form of piracy, I'm askin' you? Why, 'tis kidnap and ransom, that's what. There's no cargo takes up so little space nor fetches so high a price as live human baggage -- so long as you choose the right person. Even you daft lubbers must've heard how Toliver Crimp earned himself a thousand doubloons last summer when he ransomed the Viceroy's nephew -- \"\n\n\"A thousand doubloons!\" cry the pirates in unison.\n\n\"A spit in the ocean compared to what I've got planned! I'll be earning us a king's ransom -- or a queen's ransom, rather, if you wants to split hairs on it -- when I capture the best prize of all. I'm talking about that pretty young Queen Titania of Glorianne, my hearties, who'll soon be sailing here on a tour of the colonies!\"\n\nYou were just tiptoeing past the door, glad of Skarvench's ranting as it kept you from being overheard, but this news roots you to the spot. Can Skarvench really mean to set his sights so high? The kidnapping of a monarch is surely beyond the limits of even his voracious ambition. Everyone knows that the Queen Titania is well guarded by her loyal admiral, Lord Calidor, whose naval tactics have sent many a foe to the sea's bottom. And no trickery or poison can prevail against her while she is protected by her wizardly counsellor, Dr. Wild. Skarvench's plan seems impossible, and yet you have suffered enough harsh experience of the man aboard his ship to know that , although unmatched for cruelty and greed, he is nobody's fool. He must really think he has a chance of carrying off the Queen!\n\nYou glance across the passage to the sailmaster's cabin. No light shows under the door. The sailmaster must still be in the gallery with most of the other pirates. Now is your chance to sneak into the empty cabin and gather a few items for your voyage -- and God knows, your comrades must be getting anxious for you to return. At any moment one of the pirates might go up on deck and your bid for freedom would be discovered. But Skarvench is still boasting of his madcap scheme, and despite your best instincts you feel compelled to eavesdrop further.";

        Choices.clear();
        Choices.push_back(Choice::Base("Stay where you are and listen to what Skarvench says", 20));
        Choices.push_back(Choice::Base("Look in the sailmaster's cabin for supplies", 39));
        Choices.push_back(Choice::Base("Decide to hurry straight up on the deck", 172));

        Controls = Story::Controls::STANDARD;
    }
};

class Story002 : public Story::Base
{
public:
    Story002()
    {
        ID = 2;

        Text = "Your chosen course takes you through raging storm-tossed seas where high waves constantly threaten to swamp the little jollyboat. There is no respite from bailing out the puddle of sea water that fills the bottom of the hull. From dawn to dusk the sky is darker than granite and your rare glimpses of the sun are greeted by groans of bleak dismay, for it only reminds you how cold you are. Frequent thunderstorms rattle behind the clouds, casting the corpselight glare of lightning across your terrified faces. And through it all an icy rain lashes down, hard as needles, numbing your weary limbs.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::WILDERNESS_LORE))
        {
            return 421;
        }
        else
        {
            return 222;
        }
    }
};

class Story003 : public Story::Base
{
public:
    Story003()
    {
        ID = 3;

        Text = "You make a valiant attempt to break through the encircling throng of natives, but to no avail. As two of them seize your arms, a third brings his wooden club crashing down on your skull. A blaze of painful white light is followed by darkness and oblivion. If you awaken at all, it will be to find yourself simmering in the cookpot of these fearsome cannibals.\n\nYour adventure is at an end.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story004 : public Story::Base
{
public:
    Story004()
    {
        ID = 4;

        Image = "images/forest-green.png";

        Text = "Hidden among the lush ferns of the jungle, you watch as Skarvench locates a mark carved on the trunk of a tall tree and then paces off towards a clearing. Pointing to the ground, he directs the two sailors to start digging while he and his officers rest in the shade with a bottle of grog.\n\n\"Looks like he's come here to collect his buried loot,\" muses Blutz.\n\n\"I wonder why,\" whispers Oakley. \"I mean, it's not like he needs extra cash, is it? I'd give anything to be a fly on his face right now and hear what they're talking about.\"\n\n\"A fly?\" snorts Grimes. \"I'd sooner be a hornet and sting the cur!\"";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_SKILL(player, Skill::Type::SPELLS))
        {
            Choices.push_back(Choice::Base("Risk sneaking closer to listen in on what they're saying", 42));
            Choices.push_back(Choice::Base("Stay hidden until they have collected the treasure and sailed away", 288));
        }
    }

    int Continue(Character::Base &player) { return 61; }
};

class Story005 : public Story::Base
{
public:
    std::string PreText = "";

    Story005()
    {
        ID = 5;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Ejada responds with a cry of rage and sorcerous gesture. Immediately a hail of red-hot stones pour down out of the sky to pelt you as you flee. \"Craven mortals, \" she thunders. \"I gave you the chance to leave with honour, but you spurned my kindness. Now suffer the consequences.\"\n\n\"Kindness, she calls it?\" gasps Blutz as he struggles to keep up through the battering rain of stones. \"She's killing us with her kindness!\n\n";

        auto DAMAGE = -6;

        if (Character::VERIFY_SKILL(player, Skill::Type::CHARMS))
        {
            DAMAGE += 2;

            PreText += "[CHARMS] ";
        }

        if (Character::VERIFY_ITEMS(player, {Item::Type::FEATHER_SHIELD}))
        {
            DAMAGE += 2;

            PreText += "[Item: FEATHER SHIELD] ";
        }

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Points.";

        Character::GAIN_LIFE(player, DAMAGE);

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 195; }
};

class Story006 : public Story::Base
{
public:
    std::string PreText = "";

    Story006()
    {
        ID = 6;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "All the pent-up emotion of your crew explodes in an excited roar as they go leaping onto the deck of the enemy ship with you at their head. The pirates stand ready to meet your boarding party, but the pounding they took from your guns has sapped their morale and the battle seems a forgone conclusion. Gunshots crack deafeningly all around you, and you are half blinded by the thick clouds of smoke and sprays of blood, but you charge right into the thick of the fray with a cry of, \"Have at them, lads!\"\n\nA bullet tears into your leg.\n\nYou LOSE 1 Life Point.";

        Character::GAIN_LIFE(player, -1);

        if (player.Life > 0)
        {
            PreText += "\n\nYou ignore the wound you have taken. The battle rages back and forth across the deck. Pirates come running at you but you dash them aside. Your only thought now is to find your foe and slay him yourself; you do not want him to have the mercy of a stray bullet.\n\nThe instant you catch sight of him, you realise your anxiety was misplaced. The bullets go whistling around his ears, but he stands there oblivious of danger, arms spread out and laughing like a fiend from the pit. You begin to wonder if he can be killed -- or are his hate and madness stronger than death itself?\n\nHis single eye fixes on you through the haze of gunsmoke. \"Ah, matey,\" he says. \"Come to see your old cap'n one last time, eh?\"";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 89; }
};

class Story007 : public Story::Base
{
public:
    Story007()
    {
        ID = 7;

        Text = "It is impossible to prevent it from leaking. Already dangerously low in the water, it now requires two people to bail constantly.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Backround(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORD(player, Codeword::Type::FLOAT))
        {
            return 26;
        }
        else
        {
            return -1;
        }
    }

    int Continue(Character::Base &player)
    {
        if (!Character::VERIFY_SKILL(player, Skill::Type::CHARMS))
        {
            Character::GET_CODEWORDS(player, {Codeword::Type::DETRUDE});
        }

        return 26;
    }
};

class Story008 : public Story::Base
{
public:
    Story008()
    {
        ID = 8;

        Image = "images/filler2-green.png";

        Text = "\"Never heard of the place!\" cries Mandrigard, spilling ruby wine across his gold and gems as he brings the goblet banging down hard on the tabletop.\n\n\"Never heard of it?\" you repeat incredulously. \"Why, man, it's the richest and biggest port of all the Gloriannic colonies.\"\n\nHe snorts indifferently. \"It means nothing. I have sailed the world's waters longer than such places have had a name. And though it grieves me to say it, I'm resigned to sailing on long after those ports have sunk into the sea.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Ask him to tell you more", 46));
        Choices.push_back(Choice::Base("Explore the rest of the ship", 65));

        Controls = Story::Controls::STANDARD;
    }
};

class Story009 : public Story::Base
{
public:
    Story009()
    {
        ID = 9;

        Choices.clear();

        Controls = Story::Controls::NONE;
    }

    int Backround(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORD(player, Codeword::Type::CHANCERY))
        {
            return 406;
        }
        else
        {
            return 423;
        }
    }
};

class Story010 : public Story::Base
{
public:
    Story010()
    {
        ID = 10;

        Text = "Half fainting from exhaustion, you stand on teetering legs and raise your wand to the sky, then softly speak the words of the spell. Over and over, like a child's nursery rhyme, your lilting chant carries across the flat calm of the sea.\n\nAt first hopeful, the others wait tensely for several minutes, finally giving sighs of despondency. They slump to the bottom of the boat, their postures showing they have lost all hope now. You abandon the spell and crouch down beside them. You left it too late. Your resolve was too weakened by hardship, your willpower too drained, for you to muster your magic.\n\nSplot! -- a loud wet slap as a damp spot appears on the dry grey timbers of the boat. Then another, and another. One strikes your face and you cry out in sheer joy. It is pure fresh rainwater! As it falls in a steady shower, the four of you lie sprawled in the bottom of the boat with your mouths wide open, giggling like lunatics.\n\nYou are still lying there an hour later, by now soaked in drizzle, when a shadow looms against the sky and a voice calls down to you: \"Ahoy there! We're throwing down a rope.\"\n\nAll four of you sit bolt upright. A ship has come right up alongside -- The Jewel of Heaven -- and you never even noticed the crew hailing you over the noise of your own merry laughter. \"Why, this is a glad day!\" says Oakley as you climb up the rope. \"First a good drink of water, and now a ride home into the bargain!\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 10; }
};

class Story011 : public Story::Base
{
public:
    Story011()
    {
        ID = 11;

        Text = "\"I see,\" he says soberly when you have told him all you know. He sets his cup aside and goes to make sure no-one is listening at the cabin door. Returning, he drops his voice and says, \"Keep this to yourselves. It may well be that we shall yet foil Skarvench's scheme, but we'll have no hope of catching him if word gets out that we're forewarned. Listen now: once you are settle in Leshand, come to my house on Halyard Street. Ask for Master Capstick -- that's me. There we'll make our plans to catch that sea rat.\"\n\nYou gained the codeword MARATHON.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_CODEWORDS(player, {Codeword::Type::MARATHON});
    }

    int Continue(Character::Base &player) { return 108; }
};

class Story012 : public Story::Base
{
public:
    Story012()
    {
        ID = 12;

        Text = "You make your way along the dockside, threading between the cars and bales and bustling sailors, until you come to a doorway under a painted sign showing a coil of rope and a ship's barrel. This is the shop of Gallowglass, a chandler and general trader from you have often bought supplies in the past. Catching sight of you through the open doorway, he beckons you inside. \"Ashore again, eh?\" he says jovially. \"But not for long, I'll be bound. What can I do for you?\" He shows you his wares. You can buy anything you have money for.\n\nAs he turns to serve another customer, Gallowglass adds, \"You won't be staying in port for the Queen's visit, then?\"\n\n\"When is she due to arrive?\" asks Grimes.\n\nGallowglass smiles and shrugs. \"A month or so. She's touring the colonies, I hear. Everyone's been told to stay on best behaviour or they must answer to the governor. Perhaps that's why I haven't sold half my usual turnover of gunpowder this week.\"\n\nLeaving the chandler's you consider your next move.";

        Choices.clear();
        Choices.push_back(Choice::Base("Find someone to identify any unusual items you've come across", 31));
        Choices.push_back(Choice::Base("Listen for rumours", 88));
        Choices.push_back(Choice::Base("Apply for a letter of marque", 409));
        Choices.push_back(Choice::Base("(Marathon) Pay a visit to Master Capstick", 69, Codeword::Type::MARATHON));
        Choices.push_back(Choice::Base("You have now completed all your business in Leshand", 107));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Shop = {{Item::CRUCIFIX, 8}, {Item::PISTOL, 10}, {Item::SWORD, 10}, {Item::COMPASS, 10}, {Item::PARROT, 2}};

        if (Character::VERIFY_SKILL(player, Skill::Type::ROGUERY))
        {
            Choices[2].Destination = 50;
        }
        else
        {
            Choices[2].Destination = 409;
        }
    }
};

class Story013 : public Story::Base
{
public:
    std::string PreText = "";

    Story013()
    {
        ID = 13;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "These men have cut-throat skills honed in a hundred desperate backstreet fights. They wield their knives with the precision of trained surgeons -- except that each finely judged cut is intended to cause death, not avert it.\n\n";

        auto DAMAGE = -6;

        if (Character::VERIFY_SKILL(player, Skill::Type::BRAWLING))
        {
            PreText += "[BRAWLING] ";

            DAMAGE = -3;
        }

        if (Character::VERIFY_SKILL(player, Skill::Type::MARKSMANSHIP))
        {
            PreText += "[MARKSMANSHIP] ";

            DAMAGE = -2;
        }

        if (Character::VERIFY_SKILL(player, Skill::Type::SWORDPLAY))
        {
            PreText += "[SWORDPLAY] ";

            DAMAGE = -2;
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Points.";

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 70; }
};

class Story014 : public Story::Base
{
public:
    Story014()
    {
        ID = 14;

        Image = "images/skarvench-green.png";

        Text = "A look of thunder flickers behind Skarvench's eye. \"Still alive, eh? Come and drink with your old cap'n!\" He waves the rum bottle as if inviting you to take it, but you'd sooner put your hand in a wolf's mouth.\n\nBlutz's blood is up at the sight of your hated foe. \"God rot your one eye, villain!\" he screams. \"I'd like to take that bottle and --\"\n\nThere is a crash of breaking wood and Blutz falls with a groan. Glancing to one side, you see he has been hit over the head with a stool. Curshaw stands there grinning, then puts his boot into the unconscious Blutz's ribs. He drops the broken leg of the stool beside him.\n\nOakley and Grimes stand face to face with the closing circle of Skarvench's men. You whirl to face the pirate captain himself. \"Enough, Skarvench; your quarrel's with me, not them.\"\n\nHe crows with laughter. \"Ah, that's a right noble sentiment and no mistake! See here, though: my quarrel's with all who'd try'n scupper my plans. I'm aimin' to bag me a queen, no less, an' then sell her to the highest bidder. So I'm goin' to have to do away with you, mate -- which I should've done long ago, but I guess my old heart's just too soft.\"\n\nHis hand goes to his belt. You realise he's reaching for a weapon, and your own fingers close instinctively on something on the table beside you. You raise it, and Skarvench gives a screech of laughter. You're holding only a corkscrew. He has a musket. \"I'll be the wealthiest man on the seven seas,\" he boasts. \"And he who would that wealth deny, down among the dead men let him lie!\"\n\nThere is a flash as he fires. Smoke fills the air and the musket-ball thuds into your chest. You feel an instant of searing pain, then everything goes black.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 362; }
};

class Story015 : public Story::Base
{
public:
    Story015()
    {
        ID = 15;

        Text = "Raising your arms to the heavens, you commence the incantation. At first the apparent gibberish coming from your lips gives your three companions cause to smile. But the smiles soon fade, to be replaced by wide-eyed awe, when they see black storm clouds piling up against the eastern sky at your command. The faint glow of sunrise is drowned in fresh darkness. Thunder cracks from far off like distant cannon-fire, sending a dull and ominous rumble across the world.\n\nA breeze ruffles your clothes. Finishing the spell, you glance down to see your friends crouching in the bottom of the jollyboat, faces drained of colour. \"Do not be afraid,\" you tell them. \"The full force of the storm will not reach us here. I have placed it athwart the Belle Dame's bows, and she'll have to run with the wind till it blows itself out. Skarvench will have a hard time following us now.\"\n\nA blossom of lightning flares beyond the sooty haze of the storm clouds. If only you felt as confident as you are trying to sound. But you know that such titanic elemental forces cannot be conjured lightly and indeed, even as you lower your MAGIC WAND, it explodes in a shower of crackling blue sparks!\n\nYou gained the codeword PROSPERO.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::LOSE_ITEMS(player, {Item::Type::MAGIC_WAND});

        Character::GET_CODEWORDS(player, {Codeword::Type::PROSPERO});
    }

    int Continue(Character::Base &player) { return 289; }
};

class Story016 : public Story::Base
{
public:
    Story016()
    {
        ID = 16;

        Text = "You sail back into Selenice harbour with a hold full of treasure and hearts full of confidence. News of your fortune spreads rapidly, bringing the master shipwright himself hurrying down to the quay to greet you.\n\n\"Come aboard, Master Kemp,\" you say, heartily pumping his hand as he steps off the gangplank. \"We've found rich pickings on our travels. Perhaps now you can sell us a ship more suited to our needs?\" With that, you throw open the hold covers with a theatrical flourish.\n\nThe sunlight reflects off your haul in patterns of gold, silver and ruby-red across Kemp's face. He looks up with as broad a smile as a mouth could manage and says, \"Why, captain. I have the very ship for you moored just along the quay.\"\n\nYou turn to look where he is pointing, a gasp of admiration escaping your lips as you do. The ship is a proud tall-masted galleon with sixty cannon bristling along her gunwales. Her figurehead is a painted oak mermaid of almost supernatural beauty. \"The Faerie Queen,\" says Blutz, reading the name emblazoned on the prow. \"I think I'm in love.\"\n\n\"That's the one for us,\" you concur. \"Master Kemp, you keep the sloop and the loot here in the hold. We'll have the FAERIE QUEEN.\"\n\nKemp nods, stunned at having made the quickest sale of his life, while you stride down the gangplank and along the quay to take command of your new vessel.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::TAKE_SHIP(player, Ship::FAERIE_QUEEN);
    }

    int Continue(Character::Base &player) { return 184; }
};

class Story017 : public Story::Base
{
public:
    Story017()
    {
        ID = 17;

        Text = "You agree it is senseless to try steering out of the bay in thick fog. The anchor is dropped, but as you turn to go below you are met by a deputation of crewmen. Their spokesman is the bo'sun - a great thickset man with a head like a cannonball, he stands before you twisting his cap in his hand with the nervousness of a small child. \"The thing is, Cap'n\" he says with many a glance to left and right, \"this looks a dire place to lie becalmed, an' now with this fog comin' in... Well, it's given some o' the men the jibbers, an' we was wonderin' -- with your reputation for magic an' that -- if you couldn't lay a charm to keep the ship safe from hobgoblins an' such?\"\n\n\"A simple enough request, bo'sun, and one I'm glad to grant if it will help the men's morale.\"Taking your MAGIC AMULET in hand, you recite a benediction that renders the ship inviolate against any assault by evil spirits or creatures of the night. Acknowledging the crew's thankful looks with a bland smile, you go down to your cabin and turn in. The night passes uneventfully.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 396; }
};

class Story018 : public Story::Base
{
public:
    Story018()
    {
        ID = 18;

        Text = "Sudden rain thunders down onto the deck, and a moment later you are hit by a wind that strains the sails to the verge of snapping. The sky above looks like molten tar, and lightning drops in dazzling splinters through the darkness. Drawing the fan from your sleeve, you rush forward and sweep it hard. There are mutterings of superstitious awe from the sailors as the storm abates. You can still see the titanic waves crashing down off your bows, but it seems that the fan forms a funnel through the storm -- a funnel through which you can steer your ship.\n\n\"Helmsman!\" you shout. \"Dead ahead: take us into the eye of the storm.\" The THUNDERCLOUD FAN vanishes from your hand now that its power is used up -- but it has served its purpose.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::LOSE_ITEMS(player, {Item::Type::THUNDERCLOUD_FAN});
    }

    int Continue(Character::Base &player) { return 94; }
};

class Story019 : public Story::Base
{
public:
    std::string PreText = "";

    Story019()
    {
        ID = 19;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Smoke-hazed flashes blister among the gunwales of the Moon Dog, followed by a sound like thunder that rolls across the water. Cannonballs crack against the timbers of your vessel. There is a cry of alarm as the mizzenmast splits, and you have to dodge to one side as the rigging comes crashing down. At least one of your crew is not so fortunate: you see him swept overboard by the broken boom as it falls.\n\nYou ship SUFFERS 2 damage.";

        Character::DAMAGE_SHIP(player, 2);

        if (Character::CHECK_SHIP(player))
        {
            PreText += "\n\nYou return fire at point-blank range, crippling the Moon Dog, and then close in for boarding.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player)
    {
        if (Character::CHECK_SHIP(player))
        {
            return 6;
        }
        else
        {
            return 227;
        }
    }
};

class Story020 : public Story::Base
{
public:
    Story020()
    {
        ID = 20;

        Text = "There is a murmur of amazement from the pirates in Skarvench's cabin. Then you hear a voice which you recognize as Curshaw, the weaselly quartermaster: \"But how, Cap'n? Them Gloriannes know the sea like as to porpoises. They'd blow us out of the water before we got within a league of the Queen's flagship.\"\n\nCrouching outside in the darkened passage, you nod to yourself. That's the question you'd have liked to ask.\n\nThere is a pause. You picture Skarvench giving one of his secretive smiles as he takes a pinch of snuff. Sure enough, there comes a satisfied sneeze and then his crowing voice is heard again: \"Never you mind the details, Mister. Thats for your old captain to sort out, ain't it? Suffice to say that there's a shipwright in Port Selenice who's being well paid for his work.\"\n\n\"But, Cap'n\" you hear the ox-like first mate, Porbuck protesting, \"we've always stuck by all your plans, but this surely can't be feasible. Won't Queen Titania be heavily guarded? It'd be our one ship against a dozen!\"\n\nPrecisely what you were thinking.";

        Choices.clear();
        Choices.push_back(Choice::Base("Wait and hear Skarvench's reply", 77));
        Choices.push_back(Choice::Base("Rejoin your friends", 172));
        Choices.push_back(Choice::Base("Risk taking the time to snatch some supplies from the sailmaster's cabin", 39));

        Controls = Story::Controls::STANDARD;
    }
};

class Story021 : public Story::Base
{
public:
    Story021()
    {
        ID = 21;

        Text = "Having sailed these waters often as an honest merchant before he was press-ganged into service on the Belle Dame, Oakley relates what he knows of the islands:\n\n\"Pandanus Island, the westernmost in the chain, has often been visited by ships,\" he says. \"The natives there are friendly enough. The next, known as Grimoire Island, is a mystery except I've heard the natives shun it out of fear for a hellish demon that lives there. Foolishness, of course. Next in the chain is Firepeak Island, which gets its name from the immense cone of a smouldering volcano that dominates its hinterland. I never met a man who went ashore there --\"\n\nBut what about the easternmost island?\" asks Blutz. \"That's the first one we'll come to.\"\n\nOakley shrugs. \"Red Skull Island. I've heard that too is inhabited, but it lies clear of the main shipping route and so the natives can have little contact with the outside world.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::FOLKLORE))
        {
            return 58;
        }
        else
        {
            return 97;
        }
    }
};

class Story022 : public Story::Base
{
public:
    Story022()
    {
        ID = 22;

        Text = "Overawed by what they have witnessed of your power, the cannibals are afraid to attack. Instead they come forward and drop to their knees, bowing to you as though in heathen prayer.\n\n\"Blow me!\" says Oakley. \"They think you're some kind o' demigod, mate.\"\n\n\"It seems they do.\"\n\nMilking the situation for all it's worth, you raise your voice to an angry shout and rail at the cannibals, cursing them for daring to try and harm you. Although they cannot understand your words, the meaning is clear enough. Quailing, they scurry off and return with gifts, strewing these before you on the sand in the hopes of assuaging your wrath.\n\nYou are offered a FEATHER SHIELD, an OBSIDIAN NECKLACE, and a SHARK's TOOTH SWORD, which is a blade of hard wood studded with shark's teeth that serves as well as any steel sword. Take whatever you want.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Take = {Item::FEATHER_SHIELD, Item::OBSIDIAN_NECKLACE, Item::SHARKS_TOOTH_SWORD};

        Limit = 1;
    }

    int Continue(Character::Base &player) { return 98; }
};

class Story023 : public Story::Base
{
public:
    Story023()
    {
        ID = 23;

        Text = "Who can say how long the carnage lasts? Amid explosive gunshots, hoarse yells and the clang of steel blades, your ragged but valiant band struggle to the death against Skarvench and his murderous henchmen.\n\nEventually the battle shrinks to just you and Skarvench. Crouching behind his cutlass, he weaves and lunges and parries -- cocksure and vicious at first, his sneering smile only gradually fading as he realises you are the better fighter. Then his taunts turn to weary gasps as he struggles desperately to defend himself.\n\nYou are exhausted too. You gulp at the air like a drowning man, each swing plumbing the last dregs of your strength. But at last the red rage fades. You r enemy lies dying at your feet. Looking up at you the evil light fades from his eyes, he musters a mad grin and shrieks with laughter. \"So that's your victory, is it mate?\" A bitter triumph, I'd say!\"\n\nYou look around, and now you see what he means. The forest floor is like a scene from a slaughterhouse, your friends lying dead along with the pirates. You stagger, sick at heart. You wanted revenge, but not at this high price.\n\nSkarvench gives a last laugh. \"See you in hell,\" he croaks.\n\nHe is dead.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story024 : public Story::Base
{
public:
    Story024()
    {
        ID = 24;

        Text = "The warship's captain comes aboard with a party of heavily armed marines. He casts a pebble-eyed glance at the assorted rogues of your ship's company, then turns to address you. \"I take it you are the captain of this rabble. I put it to you that your business on the high seas is nothing but common piracy and, this being so, I hereby take charge of your vessel in the name of Her Majesty the Queen.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_ITEMS(player, {Item::Type::LETTER_OF_MARQUE}))
        {
            return 92;
        }
        else
        {
            return 111;
        }
    }
};

class Story025 : public Story::Base
{
public:
    std::string PreText = "";

    Story025()
    {
        ID = 25;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "With a groan of protesting timbers, your ship lurches to a dead halt as her prow smashes into the Moon Dog's side. Your sailors cast grappling-hooks, catching the other ship's rail and pulling them together for the final battle.\n\nYou ship SUFFERS 1 damage.";

        Character::DAMAGE_SHIP(player, 1);

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player)
    {
        if (Character::CHECK_SHIP(player))
        {
            return 6;
        }
        else
        {
            return 227;
        }
    }
};

class Story026 : public Story::Base
{
public:
    Story026()
    {
        ID = 26;

        Text = "Despite all hardships, you can at least console yourselves with that fact that you are making good headway. The same gales that threaten to swamp your boat are also driving you swiftly westwards.\n\n\"It's a race against time,\" says Oakley with a sour grin, his hair plastered down against his white face by the unceasing rain. \"Will we get out of this before our food or our strength runs out?\"\n\n\"Our our luck,\" mutters Grimes.\n\n\"Stop it!\" screeches Blutz. \"I can't stand it much longer, stuck out here on this tiny boat and the endless ocean around and beneath us waiting to swallow us up.\"\n\n\"Aye!\" says Oakley. He slaps the timbers of the boat. \"That's all we have keeping us from a watery grave, mates. Barely more wood in her than a coffin lid... \" His eyes blaze feverishly and he gives a sudden wild laugh. \"So let's christen her, then: to the good ship Coffin Lid and all who sail in her, whether it be to Leshand harbour -- or straight down to hell!\"\n\nBlutz turns away, and suddenly his eyes start with fright. He is staring at something over your shoulder, in the water off to starboard. You turn slowly, following his gaze, and see something that makes your heart miss a beat. For there swims a sea maiden, with pearl-white skin and hair the colour of coral, whose beauty and silent haunted look seem as terrible as the ocean depths.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::FOLKLORE))
        {
            return 45;
        }
        else
        {
            return 64;
        }
    }
};

class Story027 : public Story::Base
{
public:
    Story027()
    {
        ID = 27;

        Text = "He sheds a single tear, which falls like a liquid pearl from the long beak of his nose to splatter on the gold coins strewn about his feat. \"My crew! My loyal lambs! Where are they now?\" He takes a long draught of wine from the seemingly inexhaustible supply in his goblet. \"Thirty-six of them came away with me from Hecuba Island, and all shared my curse. Yet one by one they slipped away. How, I'll never know -- for the curse was that we'd never make landfall, nor could we leave the ship. They broke the curse somehow, but they left their old captain behind along with the loot. God curse them for that, say I, and I'll drink to their ill health!\"\n\nHe gulps more wine, reeling now and plunging his head close to the table.";

        Choices.clear();
        Choices.push_back(Choice::Base("Take advantage of his drunkenness to go poking around the ship", 65));
        Choices.push_back(Choice::Base("Rouse him with further questions", 46));

        Controls = Story::Controls::STANDARD;
    }
};

class Story028 : public Story::Base
{
public:
    Story028()
    {
        ID = 28;

        Text = "There is a sweet smell in the air which you notice as you tie up the boat. Could it be honey? Unlikely, you think, as how could bees live here with no flowers from which to gather pollen? Your worries about food are soon allayed, though, when you see shoals of fish swimming in towards the island.\n\n\"Where are they going to? says Blutz, peering into the water. \"I can see dozens of fishes swimming this way, but none of them seems to be reaching the shore.\"\n\nOakley points at a dark indistinct shape moving sluggishly to and fro deep below the surface. \"Might that be a shark? Let's do no swimming, anyway, just to be on the safe side.\"\n\nStriding towards the centre of the little island, you discover a rock pool and fall to your knees beside it with a cry of joy. However, no sooner have you tasted the water than you give a grimace and spit it out. It tastes of salt. This strikes you as odd, since the pool is surely above the level of high tide.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_SKILL(player, Skill::Type::FOLKLORE))
        {
            Choices.push_back(Choice::Base("Gather food on the island", 85));
            Choices.push_back(Choice::Base("Decide to put to sea now and go north", 6));
            Choices.push_back(Choice::Base("Continue west", 47));
        }
    }

    int Continue(Character::Base &player) { return 104; }
};

class Story029 : public Story::Base
{
public:
    Story029()
    {
        ID = 29;

        Text = "Mortice gives you food and water from his store, while you relate the story of your time aboard Skarvench's ship and how you finally manage to escape, only to face further perils on the open sea.\n\nBy now the moon has risen, shedding a spectral glow across the phosphorescent foam on the water. \"A wondrous tale,\" says Mortice, still with the same fixed leer on his face.\n\n\"And what about you, oldster?\" asks Blutz as he chews the last scrap of meat off a chicken leg. \"How do you come to be adrift on a bare raft, with only a bucket of fresh water and a hamper of food for company?\"\n\n\"Ah!\" cries the old man. \"That's a wondrous tale, too. But it can wait till morning, methinks, for the hour is late and I perceive that the full meal has made you tired.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::SEAFARING))
        {
            return 67;
        }
        else
        {
            return 105;
        }
    }
};

class Story030 : public Story::Base
{
public:
    Story030()
    {
        ID = 30;

        Text = "You've been on the island just a week, living in a lean-to on the beach. One morning Blutz comes chasing up the beach, waving his arms and shouting for all he's worth.\n\nGrimes, sprawled on the sand in the shade of a palm, puffs his pipe and remarks, \"It's a rare occurrence that stirs our Blutz to move faster than a trot. What's up, d'ye think, lads\"\n\nYou smile. \"Perhaps the sun has gone in front of a cloud? Or a fish caught a seagull?\"\n\n\"Or he found a pearl inside a coconut?\" chuckles Oakley.\n\nBut your smiles vanish when Blutz reaches you and blurts out his news: \"The Belle Dame's just coming around the headland. She'll be dropping anchor in the bay, and here's us like four turkeys at Yuletide.\"\n\nYou RECOVER 1 Life Point.";

        Choices.clear();
        Choices.push_back(Choice::Base("Run off to hide in the interior of the island until Skarvench departs", 49));
        Choices.push_back(Choice::Base("First bribe the natives to say that you're not here", 68));
        Choices.push_back(Choice::Base("Go boldly down to confront Skarvench when he comes ashore", 87));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, 1);
    }
};

class Story031 : public Story::Base
{
public:
    Story031()
    {
        ID = 31;

        Text = "In a small courtyard off the fish market lives Doctor Scriptor, a collector of magical curios. You have brought him items in the past, both for identification and to see if he would buy them from you. He looks up from his dusty manuscripts and takes what you have brought to show him, holding up a jeweller's glass and passing each item in turn under the sharp scrutiny of his beady old eyes.\n\n\"Well?\" you ask.\n\n\"One moment.\" Scriptor gives a dry cough, perching his glasses on his thin nose and consulting a dusty leatherbound book. \"Hmm. Ah yes, ah yes. Eureka!\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Ask him about a CONCH SHELL HORN", 316, {Item::CONCH_SHELL_HORN}));
        Choices.push_back(Choice::Base("... a BAT-SHAPED TALISMAN", 335, {Item::BAT_SHAPED_TALISMAN}));
        Choices.push_back(Choice::Base("... a BRONZE HELMET", 354, {Item::BRONZE_HELMET}));
        Choices.push_back(Choice::Base("... the DRAGON RING", 373, {Item::DRAGON_RING}));
        Choices.push_back(Choice::Base("You don't have any of these. You may as well leave", 392));

        Controls = Story::Controls::STANDARD;
    }
};

class Story032 : public Story::Base
{
public:
    Story032()
    {
        ID = 32;

        Text = "You explode into a sudden flurry of dazzling action. Pushing your friends back out of danger, you dive nimbly to one side as the chief ruffian's knife whistles through the air just a hand's breath above your scalp. Then, springing up onto the bar, you launch yourself forward, tumbling in midair so as to go careening against the ruffian's legs with the force of a rolling barrel. They are bowled over like so many skittles.\n\nJumping to your feet, you pause just long enough to check that Blutz and the others have safely made their getaway. It is your one mistake. A clumsily thrown knife catches you in the thing, laying open a nasty gash.\n\nYou LOSE 1 Life Point.";

        Bye = "You limp hastily outside where your friends help you to get to safety. Only when you are sure there is no sound of pursuit do you slow to a walk.\n\n\"Well, that wasn't very successful,\" says Blutz, gasping for breath.\"\n\n\"What are you griping about, Mister Blutz?\" you say with a relieved grin. \"You've still got your health, and that's what counts.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -1);
    }

    int Continue(Character::Base &player) { return 392; }
};

class Story033 : public Story::Base
{
public:
    Story033()
    {
        ID = 33;

        Text = "The sunlight, filtering weakly through tobacco-stained windows, makes his eyes shine like pearls as he turns to you. \"Pull up a pew, mates,\" he says, stifling a sodden belch. \"Ol' Greymalkin is always ready to swap stories with a fellow buccaneer.\"\n\n\"Here is a fearless warrior of the waves, indeed,\" says Grimes behind his hand. \"He's in full sail on a sea of wine, and that smell isn't salt spray billowing on the wind!\"\n\n\"I heard that!\" snaps Greymalkin drunkenly. \"Poke fun at ol' Greymalkin if you like, ye scurvy nobbler -- I'll wager I saw more action afore my lights were put out than ye'll see in your whole poxy life. Aye, an' I heard a few tales in my time, too.\"\n\n\"Heard anything recently?\" you ask.\n\n\"Heard a fair bit. Talkin' about it dries the tongue out, though.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Buy a drink (1 doubloon)", 90, Choice::Type::LOSE_MONEY, 1));
        Choices.push_back(Choice::Base("Go over to the three bullies and the scholar", 52));
        Choices.push_back(Choice::Base("Pay a visit to the shipyard", 374));

        Controls = Story::Controls::STANDARD;
    }
};

class Story034 : public Story::Base
{
public:
    Story034()
    {
        ID = 34;

        Text = "His eyes roll in their sockets, each an orb as big as a boulder. \"A ship, is it? Well, there are many moored in this harbour. More ships than you could dream of: all the ships of myth and legend! But do you not see this harbour chain?\" His hand dips into the dark water, jangling the massive links as a man might play with a watch-chain.\n\n\"Won't you lift it,\" you boldly ask him; \"allow us to enter and choose a vessel?\"\n\nHe booms his mirth to the sky. \"Hah! You're audacious enough to be a hero, at least. No, I won't help you -- but see this lock? You could open the chain yourself easily enough, except for the fact that no man can see or touch the key that fits it.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("[CUNNING] Try something", 91, Skill::Type::CUNNING));
        Choices.push_back(Choice::Base("[SPELLS] Try unlocking the chain by magic", 110, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("Try an item that you think might do the trick", 129));
        Choices.push_back(Choice::Base("Failing any of these, you must admit defeat", 72));

        Controls = Story::Controls::STANDARD;
    }
};

class Story035 : public Story::Base
{
public:
    Story035()
    {
        ID = 35;

        Text = "\"Sidonian men-o'-war hard astern! Three of of 'em!\" cries your lookout. The Gloriannic warship sees them too and alters course to engage the enemy. Forgotten for the time being, your own ship is able to slip away.\n\nOakley joins you on the poopdeck. \"They're almost over the horizon,\" he says, glancing back. \"A nice bit of luck, those Sidonian ships turning up just when they did. But I'm a bit surprised at you making a run for it, skipper. I'd have thought you'd order us to muck in and help the Gloriannic captain.\"\n\nYou smile and pat the wand tucked into your belt. \"Help him, Mister Oakley? Against what -- those magical mirages I conjured? They'll be fading like a morning haze as soon as we're out of sight.\"\n\nHe laughs heartily to hear this.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 16; }
};

class Story036 : public Story::Base
{
public:
    Story036()
    {
        ID = 36;

        Text = "Sailors are a superstitious lot, easily spooked by any overt display of sorcery. Because of this you are reluctant to unleash the full force of your magic in front of the crew. Luckily Blutz realises your dilemma and provides you with an excuse to slip away. \"When I was a lad, we always used to say you could get a wind by whistling for it,\" he declares loudly. \"Its worth a try now, ain't it, shipmates?\" Turning to you, he adds: \"Begging your pardon, skipper, but it's an ill wind you get if you whistle while the captain's on deck.\"\n\n\"Eh? Oh yes, of course; I've heard that legend. Well, anything's worth trying. Carry on, Mister Blutz.\"\n\nWhile the crew start whistling, you go below to your cabin and conjure a wind. Returning on deck a little while later, you see the sails billowing and the sailors dancing for joy. \"Quick thinking, Mister Blutz,\" you mutter as the Lady of Shalott clears the mouth of the bay.\n\n\"Just whistle anytime you need me, Cap'n\" he replies with a wink.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 396; }
};

class Story037 : public Story::Base
{
public:
    Story037()
    {
        ID = 37;

        Text = "The storm turns the sky to boiling pitch, and in your fancy it seems that you would be swamped by celestial fires if it were not that the sea now boils up to the edge of heaven, hissing those fires into smoky darkness. Your crew cling to whatever comes to hand as mighty waves come heaving over the side. You see one man lose his balance and go hurtling across the deck -- only saved at the last moment by catching hold of the mainsail shrouds.\n\n\"Cap'n!\" cries the helmsman, peering into the thundering curtains of rain. \"I cannot see to steer her!\"\n\nYou hold your amulet before his eyes. Its burnished gold surface sparkles in the flicker of lightning. \"Focus your gaze on this,\" you tell him. \"Have faith.\"\n\nHe stands fast as though entranced, turning the whipstaff to follow each swing of the amulet. The sails strain, drawing shrieks of protest from the masts, and high waves crash around your bows, but you plunge on directly for the heart of the storm.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 94; }
};

class Story038 : public Story::Base
{
public:
    std::string PreText = "";

    Story038()
    {
        ID = 38;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::SEAFARING))
        {
            PreText = "You pull your ship deftly aft of the enemy ship without taking damage.";
        }
        else
        {
            PreText = "You are clipped by cannon-fire as you go in. Your ship SUFFERS 1 damage.";

            Character::DAMAGE_SHIP(player, 1);
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player)
    {
        if (Character::CHECK_SHIP(player))
        {
            return 415;
        }
        else
        {
            return 227;
        }
    }
};

class Story039 : public Story::Base
{
public:
    Story039()
    {
        ID = 39;

        Text = "The sailmaster is the officer in charge of day-to-day navigation of the ship. His tiny cabin is strewn about with papers, compasses, books and other maritime paraphernalia.\n\nA sound from the bunk directly by your shoulder makes you give a start of alarm. You thought the blasted cabin was empty! But just as you are lunging forward, the blanket is tossed aside and you have a clear view of the bunk's occupant -- not a sailor, but only the little monkey that serves as the ship's mascot. Mister Chatter is what the crew call him. He squats on the bunk and watches as you search around the rest of the cabin.\n\nYou have time to grab two items from the following: a TOOLKIT, a BOOK OF CHARTS, a CRUCIFIX, a LODESTONE and the MONKEY.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Take = {Item::TOOLKIT, Item::BOOK_OF_CHARTS, Item::CRUCIFIX, Item::LODESTONE, Item::MONKEY};

        Limit = 2;
    }

    int Continue(Character::Base &player) { return 172; }
};

auto prologue = Prologue();
auto story001 = Story001();
auto story002 = Story002();
auto story003 = Story003();
auto story004 = Story004();
auto story005 = Story005();
auto story006 = Story006();
auto story007 = Story007();
auto story008 = Story008();
auto story009 = Story009();
auto story010 = Story010();
auto story011 = Story011();
auto story012 = Story012();
auto story013 = Story013();
auto story014 = Story014();
auto story015 = Story015();
auto story016 = Story016();
auto story017 = Story017();
auto story018 = Story018();
auto story019 = Story019();
auto story020 = Story020();
auto story021 = Story021();
auto story022 = Story022();
auto story023 = Story023();
auto story024 = Story024();
auto story025 = Story025();
auto story026 = Story026();
auto story027 = Story027();
auto story028 = Story028();
auto story029 = Story029();
auto story030 = Story030();
auto story031 = Story031();
auto story032 = Story032();
auto story033 = Story033();
auto story034 = Story034();
auto story035 = Story035();
auto story036 = Story036();
auto story037 = Story037();
auto story038 = Story038();
auto story039 = Story039();

void InitializeStories()
{
    Stories = {
        &prologue, &story001, &story002, &story003, &story004, &story005, &story006, &story007, &story008, &story009,
        &story010, &story011, &story012, &story013, &story014, &story015, &story016, &story017, &story018, &story019,
        &story020, &story021, &story022, &story023, &story024, &story025, &story026, &story027, &story028, &story029,
        &story030, &story031, &story032, &story033, &story034, &story035, &story036, &story037, &story038, &story039};
}

#endif