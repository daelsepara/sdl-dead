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
        BRIBE,
        TAKE
    };

    class Base
    {
    public:
        const char *Text = NULL;

        Choice::Type Type = Choice::Type::NORMAL;

        Skill::Type Skill = Skill::Type::NONE;

        std::vector<Item::Base> Items = std::vector<Item::Base>();

        Codeword::Type Codeword = Codeword::Type::NONE;

        std::vector<Item::Type> Accept = std::vector<Item::Type>();

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

        Base(const char *text, int destination, std::vector<Item::Type> bribe, int value)
        {
            Text = text;
            Destination = destination;
            Type = Choice::Type::BRIBE;
            Accept = bribe;
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

        Title = "Prologue";

        Image = "images/filler1-green.png";

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

        Image = "images/filler2-green.png";

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

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Points.";

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

        Image = "images/filler2-green.png";

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
        Choices.push_back(Choice::Base("Apply for a LETTER OF MARQUE", 409));
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

        Image = "images/filler3-green.png";

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

        Image = "images/filler2-green.png";

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

        Image = "images/filler3-green.png";

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
    Story025()
    {
        ID = 25;

        Text = "With a groan of protesting timbers, your ship lurches to a dead halt as her prow smashes into the Moon Dog's side. Your sailors cast grappling-hooks, catching the other ship's rail and pulling them together for the final battle.\n\nYou ship SUFFERS 1 damage.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::DAMAGE_SHIP(player, 1);
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

        Image = "images/mermaid-green.png";

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

        Image = "images/filler2-green.png";

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

        Image = "images/filler1-green.png";

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

        Text = "Sailors are a superstitious lot, easily spooked by any overt display of sorcery. Because of this you are reluctant to unleash the full force of your magic in front of the crew. Luckily Blutz realises your dilemma and provides you with an excuse to slip away. \"When I was a lad, we always used to say you could get a wind by whistling for it,\" he declares loudly. \"Its worth a try now, ain't it, shipmates?\" Turning to you, he adds: \"Begging your pardon, skipper, but it's an ill wind you get if you whistle while the captain's on deck.\"\n\n\"Eh? Oh yes, of course; I've heard that legend. Well, anything's worth trying. Carry on, Mister Blutz.\"\n\nWhile the crew start whistling, you go below to your cabin and conjure a wind. Returning on deck a little while later, you see the sails billowing and the sailors dancing for joy. \"Quick thinking, Mister Blutz,\" you mutter as the LADY OF SHALOTT clears the mouth of the bay.\n\n\"Just whistle anytime you need me, Cap'n\" he replies with a wink.";

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

        Text = "The sailmaster is the officer in charge of day-to-day navigation of the ship. His tiny cabin is strewn about with papers, compasses, books and other maritime paraphernalia.\n\nA sound from the bunk directly by your shoulder makes you give a start of alarm. You thought the blasted cabin was empty! But just as you are lunging forward, the blanket is tossed aside and you have a clear view of the bunk's occupant -- not a sailor, but only the little MONKEY that serves as the ship's mascot. Mister Chatter is what the crew call him. He squats on the bunk and watches as you search around the rest of the cabin.\n\nYou have time to grab two items from the following: a TOOLKIT, a BOOK OF CHARTS, a CRUCIFIX, a LODESTONE and the MONKEY.";

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

class Story040 : public Story::Base
{
public:
    std::string PreText = "";

    Story040()
    {
        ID = 40;

        Choices.clear();
        Choices.push_back(Choice::Base("Put in at at the island", 28));
        Choices.push_back(Choice::Base("Continue on your present course", 47));
        Choices.push_back(Choice::Base("Detour northwards towards the Smoking Islands", 66));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "By steering a southerly route you take advantage of the prevailing east current which should bear you to Port Leshand with the need for hard effort at the oars. Additionally, there is always the chance that you will be picked up by one of the many ships that ply these waters\n\nAfter a whole day at sea you do not have such hopes. In all that tie you have seen nothing but the boundless expanse of ocean all around you. The sky is cloudless, giving you no respite from the sun that beats mercilessly down from dawn to dusk. By night a cool wind leaves you huddled, shivering, inside your ragged clothes.\n\n";

        auto DAMAGE = -2;

        if (Character::VERIFY_SKILL(player, Skill::Type::WILDERNESS_LORE))
        {
            PreText += "[WILDERNESS LORE] ";

            DAMAGE = -1;
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Point(s).";

        if (player.Life > 0)
        {
            if (Character::VERIFY_SKILL(player, Skill::Type::WILDERNESS_LORE))
            {
                PreText += "\n\n[WILDERNESS LORE] You soak your ragged clothes in the sea to keep yourself warm at night and cool during the day.";
            }

            PreText += "\n\nShortly after sunrise on the second day, you catch sight of a small uncharted island off to port. In form it is a rough hump of rock with no more than a hundred paces from side to side, girt with weed and sandbanks covered with clumps of greenish algae.\n\n\"A coral reef,\" decides Grimes, noting the vague orange-pink shadow of rocks beneath the waves. \"There could at least be fresh rainwater here -- and insects, if not birds.\"\n\n\"What do we want with insects?\" asks Blutz in disgust.\n\n\"Food,\" you tell him. \"Necessity must overrule nicety if we're to survive.\"";
        }

        Text = PreText.c_str();
    }
};

class Story041 : public Story::Base
{
public:
    std::string PreText = "";

    Story041()
    {
        ID = 41;

        Image = "images/throwing-rocks-green.png";

        Bye = "You slump down into the bottom of the boat with an exhausted sigh of relief as you finally get out to open sea beyond reach of the islander's bombardment.\n\n\"I think they wanted us to stay for dinner,\" jokes Oakley with grim humour. \"I hope the natives on the next island are more friendly.\"\n\nSo do you.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Heavy stones fly about you like shots from a cannon as you beat your retreat. Several of them thud harmlessly into the soft sand but then you feel a hot slash of pain as one strikes the inside of your head, leaving a ragged gash. You stumble, but Blutz catches your arm and helps you into the boat.\n\nYou lose consciousness for a moment. The next thing you know, the boat is already out amid the waves with Oakley and Grimes plying the oars for all they're worth.\n\nThe battering hail of rocks continues as the natives watch you row away.\n\n";

        auto DAMAGE = -4;

        if (Character::VERIFY_SKILL(player, Skill::Type::CHARMS))
        {
            PreText += "[CHARMS] ";

            DAMAGE = -1;
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Point(s).";

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 116; }
};

class Story042 : public Story::Base
{
public:
    Story042()
    {
        ID = 42;

        Image = "images/filler3-green.png";

        Text = "You tread on a twig and Skarvench and his cronies leap up with angry roars to do battle. Discovered, you have no recourse but to rush in on them.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Background(Character::Base &player)
    {
        if (!Character::VERIFY_SKILL(player, Skill::Type::ROGUERY) && !Character::VERIFY_SKILL(player, Skill::Type::WILDERNESS_LORE))
        {
            return -1;
        }
        else
        {
            return 80;
        }
    }

    int Continue(Character::Base &player) { return 267; };
};

class Story043 : public Story::Base
{
public:
    Story043()
    {
        ID = 43;

        Text = "\"These are glad tidings!\" he declares with enthusiasm. \"I am always happy to launch gentlemen of fortune on their careers.\"\n\nFor the next hour you are shown around the shipyard while discussing the exact specifications of your new ship. You explain to Kemp everything you want, from the timber to be used and the kind of armaments right down to details such as cargo capacity, the figurehead, and even the cabin fittings.\n\n\"You know your vessels,\" he says approvingly. \"Naturally, in view of the fact that on every point you have stipulated that you want materials and labour of only the soundest and best quality, you must appreciate that the price will not be cheap.\"\n\nYou add up the costs and discover that you will need at least one DIAMOND to purchase even a small second-hand ship. Failing that, you will have to obtain one some other way. Promising to return as soon as you have come to a firm decision, you take your leave of Master Kemp and walk back into town.\n\n\"Where to now?\" says Oakley.\n\nYou think for a moment. \"We'll take rooms at the Sweat of the Brow inn. If Skarvench shows his face anywhere in Selenice, it'll be there.\"\n\nNever a truer word was spoken. You arrive at the inn and stand frozen in shock in the doorway. There the devil stands, large as life in front of you. A rum bottle is clutched in his hand and his crew throng the tap-room around him, cowering as he subjects them to one of his thunderous drunken rants.\n\nThen his eye alights on you. His snarling voice is cut off in mid-sentence. A thin line of spittle runs down into his beard as his teeth show shark-like in a vicious grin. It is the moment you have waited for. Face to face with your arch foe.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 14; };
};

class Story044 : public Story::Base
{
public:
    Story044()
    {
        ID = 44;

        Text = "Blutz directs the crew to fetch up the cargo from the hold. At first you have no idea what he's talking about, then you remember the barrels of rock salt that the last owner of the LADY OF SHALOTT left aboard when he sold her. The light begins to dawn when Blutz orders the cannons loaded with this salt. The first broadside scours the surface of the iceberg, and it is not long before water is trickling down in the hot noon sun.\n\n\"I remembered that salt can be used to melt ice and snow,\" explains Blutz, beaming with elation at the success of his plan. After two more broadsides the salt has etched its way deep into the ice and there comes a continuous crackling sound as the iceberg slowly breaks apart under the onslaught.\n\nAn attack with pickaxes completes the task. Soon the ice has been chipped away to leave a deep gouge, and the OCTAVIUS comes drifting forth gleaming into the full daylight. You board her, abandoning the sloop, and set a northward course.\n\nThe days pass and your new ship is a delight, handling better than any vessel you've ever sailed. You feel a glow of pride as you at last steer her through the harbour gate and up to the Selenice docks.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::TAKE_SHIP(player, Ship::OCTAVIUS);
    }

    int Continue(Character::Base &player) { return 184; };
};

class Story045 : public Story::Base
{
public:
    Story045()
    {
        ID = 45;

        Text = "Mermaids are like all faerie creatures in being motivated by caprice. They can be cruel or kind, as the whim takes them. It is well known that they sometimes seek the company of mortal men, whom they entice with their beauty and promise of secret wealth, because they constantly yearn to draw a little of the surface world's warmth and vitality into their own submerged realm of twilit silence. Few who have succumbed to a mermaid's lures survive to tell the tale. There are cases of men who have tarried a while under the sea, then returned with the gift of second sight -- for the mermaids are able to grant knowledge of future events. Such cases are rare. A more likely fate is to be washed up ton the beach, leeched of breath by the mermaid's kiss, dead face forever frozen in fearful rapture of having heard the mermaid's secrets and witnessed her unearthly beauty.\n\nYou know one more thing. Any question put to a mermaid must be answered truthfully if the questioner has a firm grip on her. In that respect, too, she is like any other faerie creature.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 64; };
};

class Story046 : public Story::Base
{
public:
    Story046()
    {
        ID = 46;

        Text = "Slurring his words, Mandrigard peers soddenly at you across the table. \"It's more talk you want, is it? Well, I'm talked out. Not all the blabber in a thousand harems will wipe out the curse I carry with me -- and you poor dolts are part of that curse now -- now, and forevermore!\"\n\nWine-soaked spittle sprays out from his lips as he screams all this. The look in his eyes is like the fires of hell. Then suddenly his eyelids droop, and he slumps forward across the treasure, mumbling, \"See this scar on my left hand? There's the proof, y'see? 'Tis where I broke the lock of that heathen shrine. See the stain of my curse, do you?\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 65; };
};

class Story047 : public Story::Base
{
public:
    std::string PreText = "";

    Story047()
    {
        ID = 47;

        Choices.clear();
        Choices.push_back(Choice::Base("Improvise Something with [SEAFARING]", 218, Skill::Type::SEAFARING));
        Choices.push_back(Choice::Base("... or [WILDERNESS LORE]", 218, Skill::Type::WILDERNESS_LORE));
        Choices.push_back(Choice::Base("Eat a MONKEY", 237, {Item::MONKEY}));
        Choices.push_back(Choice::Base("Otherwise", 275));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "A little rainfall helps to slake your thirst, but hunger still chews at your bellies and the constant blaze of the sun makes you dizzy.\n\nYou LOSE 1 Life Point.\n\n";

        Character::GAIN_LIFE(player, -1);

        if (player.Life > 0)
        {
            PreText += "Squinting into the sunset, Oakley gives a sudden cry of anguish. \"Another night of this, God rot me, and I'll be as mad as a gannet! If we only had something to eat.\" He gnaws the leather of his belt just to have a taste of something solid in his mouth.";
        }

        Text = PreText.c_str();
    }
};

class Story048 : public Story::Base
{
public:
    Story048()
    {
        ID = 48;

        Text = "You eat and drink while listening to Mortice tell his tale. It is a gruesome story, beginning with a storm at sea. Mortice was washed ashore on a deserted island along with a dozen corpses of his former shipmates. After many months he was picked up by a ship called Cold Grue, but there his hope soon turned to despair. \"By day I was locked up in the fo'c'sle, and only let out at night to toil on deck. I never knew a harsher taskmaster than El Draque, the captain of that fell ship! There were other poor sailors aboard with me, and if ever you set a foot wrong -- or even if you didn't, sometimes -- you'd be taken down to the hold an' never seen again. Once I watched El Draque and his corsairs bury treasure by moonlight on a stretch o' shore off Tortoise Island, under a rock marked with crossed bones. Aye, I marked that well; I'd be goin' back there, if I had myself a ship that could outrun the Cold Grue!\"\n\n\"And how did you escape?\" asks Blutz, chomping on a chicken leg.\n\n\"Why, I made myself this raft and starved until I was so thin I could squeeze out the fo'c'sle hatch like any bag of old scraps. There wasn't a soul stirring on deck during the hours o' daylight, you see. So I loaded up food and water and pushed off. Been adrift for weeks, I have, till I caught sight o' you jolly lads!\" He refills your cups from the full barrel beside him.\"\n\nYou gained the codeword RAVEN.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_CODEWORDS(player, {Codeword::Type::RAVEN});
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

class Story049 : public Story::Base
{
public:
    Story049()
    {
        ID = 49;

        Text = "You race off into the jungle not a moment too soon. Turning to peer back from the crest of a wooded hill, you see the Belle Dame already riding at anchor offshore. A rowboat is bringing Skarvench and his cut-throats to the beach even now.\n\n\"He'll never leave until he's found us,\" mutters Oakley as you trudge on through the dense green thickets.\n\n\"It's a big island,\" you call back over your shoulder. \"If we stay hidden long enough, he'll have to give up the search and leave. For all he knows we might be dead already.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::WILDERNESS_LORE))
        {
            return 144;
        }
        else
        {
            return 163;
        }
    }
};

class Story050 : public Story::Base
{
public:
    Story050()
    {
        ID = 50;

        Text = "A LETTER OF MARQUE would allow you to indulge in a spot of honest piracy -- or rather privateering, as it is called. Such a letter licenses you to act as a private soldier of Her Majesty's navy, with full entitlement to plunder Sidonian treasure-ships.\n\n\"But we'll never be able to get one,\" says Blutz despondently after you have all spent some time discussing the idea.\n\n\"That's right,\" growls Oakley. \"It costs almost as much in bribes to get hold of a LETTER OF MARQUE as you're likely to bring in as profit.\"\n\n\"Aha,\" you say, pulling a furled-up document from your sleeve and tossing it onto the table. \"What's this?\"\n\nGrimes inspects it with mounting astonishment. \"Why, it's a LETTER OF MARQUE, establishing your right to act as privateers on the Carab Sea! How did you get --\" He pauses and a slow grin suffuses his face. \"The ink's still wet.\"\n\nYou retrieve the LETTER OF MARQUE, beaming with pride. It is a good a forgery as any you've ever done. When the ink dries up it will be indistinguishable from the real thing.";

        Choices.clear();
        Choices.push_back(Choice::Base("(Marathon) Call on Master Capstick", 69, Codeword::Type::MARATHON));
        Choices.push_back(Choice::Base("Otherwise", 107));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::LETTER_OF_MARQUE});
    }
};

class Story051 : public Story::Base
{
public:
    Story051()
    {
        ID = 51;

        Text = "\"Fine,\" you say smartly. \"Go ahead and carve us up. Then see what Skarvench does to you when he hears about it.\"\n\nThe leader of the cut-throats replies with a scowl, but you see him hesitate. He's not sure. \"You're bluffing,\" he says. \"Skarvench said to deal with anyone who came around snooping after him.\"\n\n\"We're supposed to be with him,\" you say, adopting the tone you would use to a stupid child. You're push your luck, but that's how you like it.\n\n\"How do I know you're telling the truth..?\" he says, tiny eyes clouding with uncertainty. The knife point wavers.\n\nYou give a derisive snort. \"Would we be daft enough to just waltz in here asking questions if not?\"\n\n\"Get 'em to prove it, Cuss,\" prompts one of the other thugs.\n\nYou glare at them. \"Don't think we're going to start blabbing the details of the plan in a dump like this. Anyone might overhear. But, Cuss -- suffice it to say, there'll be a right royal fuss if we don't link up with the cap'n\"\n\n\"He's in Selenice by now, I should think,\" says Cuss, sheepishly putting away his knife. \n\n\"Uh, huh,\" you say nodding. \"We'll find him aboard --\"\n\n\"Aboard the Moon Dog,\" he supplies helpfully.\n\n\"That's the one. Be seeing you.\" You leave, waiting until you're around the corner to give a sigh of relief.\n\n\"What's this about the Moon Dog?\" Blutz wonders. \"Skarvench's ship was always the Belle Dame. Why change now?\"\n\n\"Perhaps we'll find out,\" you say. \"in Selenice.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 392; };
};

class Story052 : public Story::Base
{
public:
    Story052()
    {
        ID = 52;

        Text = "The elderly scholar makes another short-sighted lunge for his spectacles, only to trip over the outstretched leg of one of the ruffians and go sprawling. Their laughter is harsh and braying. The scholar gets to his feet and brushes the dust of his velvet robe. \"Please...\" he says, almost in tears. \"Give those back; I can't see without them.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Try [CUNNING]", 128, Skill::Type::CUNNING));
        Choices.push_back(Choice::Base("Use [STREETWISE]", 147, Skill::Type::STREETWISE));
        Choices.push_back(Choice::Base("[SWORDPLAY] Fight with a SWORD", 166, Skill::Type::SWORDPLAY));
        Choices.push_back(Choice::Base("[MARKSMANSHIP] Use a PISTOL", 185, Skill::Type::MARKSMANSHIP));
        Choices.push_back(Choice::Base("Fight with your bare hands", 204));

        Controls = Story::Controls::STANDARD;
    }
};

class Story053 : public Story::Base
{
public:
    Story053()
    {
        ID = 53;

        Image = "images/giant-green.png";

        Text = "He places his hand to his jaw and squints his eyes in thought, smiling as he considers your request.\n\n\"Will you ponder the matter until the stars go out and the moon cracks in two?\" you cry boldly. \"Our foe is mortal like ourselves, and does not unfold his plans at the testudineous pace you seem to favour.\"\n\n\"Have a care!\" pleads Blutz. \"You'll anger him. He might be the very god Neptune himself.\"\n\nYou round on him with a blaze of anger. \"God or not, I'm your skipper, Mister Blutz! Now keep your counsel while I parley with yon giant.\"\n\nThe giant rumbles with laughter, amused by this exchange. There is a sparkle in his green marble eyes as he says, \"Well spoken, mortal. At sea a man should respect neither god nor titan, but only his captain. I'll help you right enough, since I now see you deserve it, but what help is it you want? Will it be wealth to buy a ship -- or the wisdom to sail her well?\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Choose wealth", 148));
        Choices.push_back(Choice::Base("Choose wisdom", 167));

        Controls = Story::Controls::STANDARD;
    }
};

class Story054 : public Story::Base
{
public:
    Story054()
    {
        ID = 54;

        Text = "The warship pulls alongside to windward, stealing the breath from your sails. Clambering into the rigging, you run along the mainyard to where the sails of the two ships are already touching. One of the enemy sailors sees you and comes swinging down from the crow's nest, knife in hand. You duck nimbly under his knife-thrust and a cheer goes up from the deck of the LADY OF SHALOTT as your men see you stun your opponent with a sharp jab to the chin. He sags back, caught in the ratlines, and you grab the knife from his limp fingers. Climbing higher into the rigging of the enemy ship, with musket-shots whistling around your ears, you glance down to see the marines casting grappling hooks. Your own crew stand ready to repel boarders as two ships are pulled together.\n\nDigging your knife into the mainsail, you slide right down the billowing canvas, using deft twists of the blade to steer your descent. You land on the deck in front of the helmsman, the split canvas drooping above you. You raise the knife, but the helmsman has no stomach for a fight and runs off, allowing you to throw the whipstaff hard over. The two vessels begin to pull apart as the warship veers in response. Realising your plan too late, the marines make a dash back from the rail, but you have already jammed the whipstaff in position with the knife and swung up to the poopdeck rail out of reach. Running for the side, you launch yourself into space and catch hold of one of the grapple-lines, swiftly pulling yourself hand over hand back to the LADY OF SHALOTT amid the delighted shouts of your crew.\n\nOakley and the rest lose no time in cutting the remaining lines, and the ships drift rapidly apart. On the deck of the warship you can see the marines struggling to free the jammed whipstaff. By the time they can do that and repair the mainsail you tore in half, you'll have made your getaway.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 16; };
};

class Story055 : public Story::Base
{
public:
    Story055()
    {
        ID = 55;

        Text = "The next half-hour gives you as gruelling a test of your ship-handling skills as you've ever faced. Taking constant depth reckoning with a lead line, you steer the LADY OF SHALOTT slowly between reefs and sandbars until at last you are out of the bay in open waters.\n\nHere a light breeze ruffles the sails, but it is not enough to give you the headway you want. You order the rowboats lowered and commence kedging -- carrying the anchor as far ahead of the bows as possible and then dropping it so that you can winch the ship onwards. It is slow going, but at last you are well clear of Tortoise Island and the eldritch fog that surrounds it. Soon you pick up a decent wind and from then on it is plain sailing back to Selenice. But you make the voyage with bitter heart because you are returning empty-handed.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 396; };
};

class Story056 : public Story::Base
{
public:
    Story056()
    {
        ID = 56;

        Text = "Driven on by remorseless determination, you hardly notice the stirrings of mutiny. At all hours of the day and night you are to be seen pacing the deck, marking the wind and sea currents in you log-book or using a cross-staff to plot the position of the stars. The crew dare not question your judgement now -- they fear they would never get home without you.\n\nAt last your steadfastness is rewarded with a cry of \"Ice ho!\" from the deck. You race up the companion-way and give a great shout of triumph as you catch sight of the blow blue hump of an iceberg dead ahead.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 414; };
};

class Story057 : public Story::Base
{
public:
    Story057()
    {
        ID = 57;

        Text = "Despite having her sails in tatters from the storm earlier, the Rose is not quite out of the fight. Her crew realise the threat and man their cannons, bringing several telling shots. to bear on the Moon Dog. Once you are standing abaft your enemy, you add your own fire to that of the Rose. Raked by two foes, the Moon Dog shudders as her mainmast topples.\n\n\"She's dead in the water!\" you cry. \"Close for boarding!\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 6; };
};

class Story058 : public Story::Base
{
public:
    Story058()
    {
        ID = 58;

        Image = "images/filler4-green.png";

        Text = "According to the stories you have heard, Grimoire Island is inhabited not by a demon, but by a powerful witch called Ejada the Green. She is thought to be more than a thousand years old, and one legend is that she sealed a pact with an ancient earth god which guarantees her invulnerability so long as her feet remain on solid ground.\n\nBut, whether true or false, these folk-tales are not your first concern. Now you must sail on towards the first of the islands -- the one Oakley believes to be inhabited by savages.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 97; };
};

class Story059 : public Story::Base
{
public:
    Story059()
    {
        ID = 59;

        Text = "\"What is it you want of me? \"growls the god, fixing you in the sharp glare of his eyes.\n\n\"My Olympian lord,\" you begin, \"we are trapped on this ship...\"\n\n\"It's captain dared to pillage my shrine!\" Dionysus thunders. \"But we don't deserve this fate, lord,\" you protest.\n\nDionysus ponders your case. \"Perhaps not. If you were more my creature, I might be moved to mercy.\n\n\"Your creature, lord?\"\n\n\"The type of mortal I favour,\" continues Dionysus impatiently, \"is a roistering rowdy varlet, full of craziness and lusty with the more uproarious joys that life has to offer. Not for me these sober scholars with their books and scrolls.\"\n\n\"Not I, lord!\" you say hastily.\n\nHe nods thoughtfully. \"I wonder. Well, I'll whisk you off to your destination, but mind you're on your worst behaviour from now on. I can't abide a dainty do-gooder!\"At Dionysus's gesture, the wine soaking the decks rises in a cloud of giddying vapour. Reeling from the fumes, you grope out until you feel the hands of your friends. They cling to you as their only protection -- though, truth to tell, if the god had unleashed his full wrath then there would have been little enough that you could do.\n\nThe wine-mist clears. There is no sign of Dionysus or his panthers -- nor of the cursed ship. Now the four of you are huddle together in the corner of a dingy tavern. A burly barman stomps over and swabs at a puddle of spilled wine on the table in front of you. \"Ain't you got no homes to go to?\" he grumbles.\n\n\"Where are we?\" Oakley innocently asks him.\n\nThe barman gives him a contemptuous look. \"You drunken lubbers! This is a Slaughtered Goat tavern, in Port Leshand.\"\n\nYou have been spirited magically to where you wanted to go, but the god's services has its price. He has left your mind permanently tinged with exuberant madness that is his hallmark.\n\nYou must make room for the [ROGUERY] and [BRAWLING] skills.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (Character::VERIFY_ALL_SKILLS(player, {Skill::Type::ROGUERY, Skill::Type::BRAWLING}))
        {
            Choices.push_back(Choice::Base("You already have these skills", 9));
        }
        else if (Character::VERIFY_SKILL(player, Skill::Type::BRAWLING))
        {
            player.SKILLS_LIMIT = 3;

            Character::LOSE_SKILLS(player, {Skill::Type::BRAWLING});

            Choices.push_back(Choice::Base("Make room for [ROGUERY]", -59, Choice::Type::LOSE_SKILLS, 2));
        }
        else if (Character::VERIFY_SKILL(player, Skill::Type::ROGUERY))
        {
            player.SKILLS_LIMIT = 3;

            Character::LOSE_SKILLS(player, {Skill::Type::ROGUERY});

            Choices.push_back(Choice::Base("Make room for [BRAWLING]", -59, Choice::Type::LOSE_SKILLS, 2));
        }
        else
        {
            Choices.push_back(Choice::Base("Make room for [ROGUERY] and [BRAWLING]", -59, Choice::Type::LOSE_SKILLS, 2));
        }
    }
};

class Event059 : public Story::Base
{
public:
    Event059()
    {
        ID = -9;

        Controls = Story::Controls::NONE;
    }

    int Background(Character::Base &player)
    {
        player.SKILLS_LIMIT = 4;
        player.Skills.push_back(Skill::ROGUERY);
        player.Skills.push_back(Skill::BRAWLING);

        return 9;
    }
};

class Story060 : public Story::Base
{
public:
    Story060()
    {
        ID = 60;

        Text = "Raising your WAND you commence a chant of your own, calling upon the occult forces which empower your magic. Seeing this, the natives fall back with a frightened moan. Then one withered old man in a feather cloak steps forward: their shaman. Wielding an obscene wand carved from a human thigh bone, he screeches a hasty incantation and advances to match his sorcery against yours.\n\nSpells flash and sparkle in the air, but the uncanny duel is short-lived. Seeing that you are far more powerful a wizard than he, the shaman hurls his wand down into the sand in a gesture of surrender.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 22; };
};

class Story061 : public Story::Base
{
public:
    Story061()
    {
        ID = 61;

        Text = "Magic bends the very elements of nature to your will. The breeze obediently brings you the words of Skarvench and his cronies as they sit chatting over their bottle of grog. They are still more than fifty paces away, but you can now hear them as clearly as if they were right by your side!\n\n\"So what's this treasure for, Cap'n?\" hiccups the quartermaster.\n\n\"To pay a certain shipwright in Port Selenice, for one thing,\" says Skarvench. \"He's to be paid in gold for the new ship he's building us.\"\n\n\"New ship?\" says Porbuck the mate, roused from his dull witted torpor. \"I liked the old one...\"\n\n\"This one's better though. The Moon Dog, she's to be named, and her special sails were ensorcelled by the Queen's own wizard. Does things the Belle Dame never could.\"\n\n\"The Queen's wizard?\" repeat Curshaw.\n\n\"Aye, Will Wild himself. My dear half-brother! But he wants silver coins for his pains, see, so there's another reason for needing this here loot. Ahoy there, ye lazy lubbers, ain't you struck the box yet?\"\n\nThe two sailors look up from their work. \"Aye, Cap'n. Here it is.\"\n\nYou've heard enough.";

        Choices.clear();
        Choices.push_back(Choice::Base("Wait until they have taken the treasure aboard their ship and sailed off", 288));
        Choices.push_back(Choice::Base("Risk attacking them in your weakened state", 267));

        Controls = Story::Controls::STANDARD;
    }
};

class Story062 : public Story::Base
{
public:
    Story062()
    {
        ID = 62;

        Text = "A funnel of wind whiplashes down out of the sky. As she feels it engulf her, Ejada gives vent to a cry of alarm and tries to catch a handhold on the palace wall. Her hair and robes billow in the wind and she is sucked inexorably into the air. To your amazement, you can now see something like green shoots or rootlets dangling from the soles of her feet. As soon as these are tugged out of the ground, she begins visibly to weaken and soon she is begging for mercy.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 157; };
};

class Story063 : public Story::Base
{
public:
    Story063()
    {
        ID = 63;

        Text = "Kemp nods. \"Just recently finished. Skarvench took delivery of her two days ago, a fine galleon of forty guns which he means to name Moon Dog. Got some queer features to her, though.\"\n\nYou press him on the point. \"Such as?\"\n\n\"Well, first off he had me install gunports along the keel. \"The ship'll sink,\" says I, but Skarvench would have none of it -- just chortled like an old crow and showed me the designs he'd brought. \"Along the keel,\" he insists, \"and mind you fit the masts thus and so; they've a fair load to lift.\"\n\n\"Eh?\" You're puzzled. \"What did he mean by that?\"\n\nKemp sighs, \"My own guess is worthless, so doubtless your own is better. It's not how I've built any ship before, and I've built hundreds. The timber was too light also -- pine is easily split by cannon -- but Skarvench only laughed fit to burst and said, \"It depends where the cannons be pointing!\" So in the end, since his gold was good, I did it the way he wanted. Now I have other customers to attend to, so I'll be bidding you good day.\"\n\n\"Where to now?\" says Oakley as you walk back to town.\n\nYou think for a moment. \"We'll take rooms at the Sweat o' the Brow inn. If Skarvench shows his face anywhere in Selenice, it'll be there.\"\n\nYou have never spoken a truer word, for no sooner have you stepped through the doorway of the inn than you are rooted to the spot in shock. There the fiend stands, large as life in front of you. A rum bottle is clutched in his hand and his crew throng the tap-room around him, cowering as he subjects them to one of his thunderous drunken rants.\n\nThen his eyes alights on you. His snarling voice is cut off in mid-sentence. A thin line of spittle runs down into his beard as his teeth show shark-like in a vicious grin. It is the moment you have waited for. Face to face with your dearest foe.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 14; };
};

class Story064 : public Story::Base
{
public:
    Story064()
    {
        ID = 64;

        Text = "A long moment passes while you sit thunderstruck gawping in amazement at the mermaid like four fishes in a net. She waits, serene as a statue. Then a slow smile appears on her lips and, raising her pale arms, she turns to swim away...\n\nIt is Blutz who reacts first, shocking himself with his own impetuosity. His arm shoots out and he seizes a hunk of the mermaid's long mauve-pink hair. For her part, she gives a cry of shock -- abrupt and musical, like the plucked string of a harp -- and twists in his grasp like an eel.\n\n\"I got her!\" cries Blutz. His eyes shine as he looks around at the rest of you, partly seeking applause and partly reassurance.\n\nThen the mermaid herself speaks. Clutching at Blutz's hand, she slowly relaxes her struggles and says, \"Release me, man of the dry land, and I will aid you.\" Managing to twist around until she faces you, her eyes flash with wild light as she adds: \"But if you should harm me, I'll lay a curse on you to harrow the hearts of all who hear of it!\"";

        Choices.clear();
        Choices.push_back(Choice::Base("[CHARMS] Counter any such curse", 83, Skill::Type::CHARMS));
        Choices.push_back(Choice::Base("[SPELLS] Enthral her with magic", 102, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("Recommend Blutz to turn her loose", 121));
        Choices.push_back(Choice::Base("Ask her what lies ahead on your journey", 140));
        Choices.push_back(Choice::Base("Ask bout the best course you can take to Port Leshand", 159));

        Controls = Story::Controls::STANDARD;
    }
};

class Story065 : public Story::Base
{
public:
    Story065()
    {
        ID = 65;

        Text = "Taking your leave of the drunken captain, you investigate the ship. It is built in a style rarely seen these days, with high structures to fore and aft and small brass cannons designed to fire grape-shot at any enemy attempting to board. \"An old vessel,\" decides Grimes, \"and somewhat in the Moorish style.\" He points to abstract fretwork carvings in the woodwork. \"Such geometrical decoration is typical of the Moors.\"\n\n\"What's this?\" asks Blutz. He has found a wooden casket on the main deck, beside the gangplank rail.\n\nGrimes rubs his jaw thoughtfully. \"Perhaps a water tank?\"\n\n\"Er... I don't think so,\" replies Blutz, eyes widening as he takes a peek inside the casket. \"You'd better take a look at this, mates.\"\n\nYou peer over his shoulder, almost yelping with shock at what you see inside the casket. For although it is half full of rainwater as Grimes surmised, it also contains several dozen skeletal hands.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 84; };
};

class Story066 : public Story::Base
{
public:
    std::string PreText = "";

    Story066()
    {
        ID = 66;

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        PreText = "Rigging a small sail made from your torn shirts, you take the boat northwards. There you hope to find an island with food and fresh water to sustain you on the long journey back to civilization.\n\nHunger makes a knot of your belly, and thirst drives you to distraction.\n\nYou LOSE 1 Life Point.\n\n";

        Character::GAIN_LIFE(player, -1);

        if (player.Life > 0)
        {
            PreText += "You arrive at last at an island. Above the bright emerald line marking its jungle-fringed shore rises the steep cone of a volcano. Clouds of smoke wreath its summit, and you can see a dull red glimmer that can only be lava. \"Let's not put in here,\" say Blutz despite his thirst. \"It might erupt and kill us all.\"";

            if (!Character::VERIFY_SKILL(player, Skill::Type::WILDERNESS_LORE))
            {
                Choices.push_back(Choice::Base("Land here", 174));
                Choices.push_back(Choice::Base("Head towards the next island in the chain", 135));
            }
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 193; };
};

class Story067 : public Story::Base
{
public:
    Story067()
    {
        ID = 67;

        Text = "Few details of any sea-going craft escape your trained eye. You note that although Mortice's raft is made of oak planks, which is a heavy wood, it floats surprisingly light in the water. This is especially odd given that the raft also carries the burden of a man, a full rain barrel, and a large chest of provisions. You can only conclude there must be something buoyant lashed to the underside of the raft.";

        Choices.clear();
        Choices.push_back(Choice::Base("Query Mortice about this", 124));
        Choices.push_back(Choice::Base("Let it lie", 105));

        Controls = Story::Controls::STANDARD;
    }
};

class Story068 : public Story::Base
{
public:
    std::string PreText = "";

    Story068()
    {
        ID = 68;

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        PreText = "Scared witless by the gargoyle-prow and black sails of Skarvench's ship, the natives will not be easy to convince. Their chief believes the pirates will kill them if they suspect them of lying. In all honesty, you have to admit he is right. You must part with two items to bribe the natives. They will accept two of the following: a SWORD, a PISTOL, a MAGIC WAND, a MAGIC AMULET, a SHIP IN A BOTTLE, a CONCH-SHELL HORN, a BAT-SHAPED TALISMAN, a BLACK KITE, a DIAMOND, a TOOLKIT, a HEALING POTION, a BRONZE HELMET, a CRUCIFIX, or a DRAGON RING.";

        auto count = 0;

        std::vector<Item::Type> bribe = {Item::Type::SWORD, Item::Type::PISTOL, Item::Type::MAGIC_WAND, Item::Type::MAGIC_AMULET, Item::Type::SHIP_IN_BOTTLE, Item::Type::CONCH_SHELL_HORN, Item::Type::BAT_SHAPED_TALISMAN, Item::Type::BLACK_KITE, Item::Type::DIAMOND, Item::Type::TOOLKIT, Item::Type::HEALING_POTION, Item::Type::BRONZE_HELMET, Item::Type::CRUCIFIX, Item::Type::DRAGON_RING};

        for (auto i = 0; i < bribe.size(); i++)
        {
            count += Item::COUNT_TYPES(player.Items, bribe[i]);
        }

        if (count >= 2)
        {
            Choices.push_back(Choice::Base("Part with two such items", 144, bribe, 2));
        }
        else
        {
            PreText += "\n\nBut you are unable to part with such items.";
        }

        Choices.push_back(Choice::Base("Stay here to confront Skarvench", 87));
        Choices.push_back(Choice::Base("Run off into the jungle", 49));

        Text = PreText.c_str();
    }
};

class Story069 : public Story::Base
{
public:
    Story069()
    {
        ID = 69;

        Image = "images/capstick-green.png";

        Text = "Capstick has a fine house on Halyard Street, in one of the richest parts of town. Smartening yourselves up to look as respectable as possible, you ignore the sidelong glances and haughty sniffs of the wealthy passers-by, marching straight up to present yourselves at the front door. The servant who answers the door at first mistakes you for beggars, but once you've corrected that small misunderstanding he shows you through his master's study.\n\nCapstick is sitting by the fire with a book. Seeing you, he gives his great belly-shaking laugh and leaps up to greet you, commanding the servant to bring a bottle of sherry.\n\n\"Freshly taken off a Sidonian merchantman,\" he says shortly, lifting his glass to savour the smoky gold liquid before drinking. \"And..\" he smacks his lips, refills your glasses \"all the better for being plundered off one of those rascals, eh?\"\n\nSoon the conversation turns to the matters you discussed aboard the Jewel of Heaven. At this, Capstick's face falls. \"I have sour news,\" he tells you. \"I must sail for Glorianne in two days' time, and so I'll be unable to partner you in your attack on that devil Skarvench. Moreover I've told the tale to several high officials, but no one believes it's true.\"\n\nYou give a glum nod. \"Who can blame them, given the source of your information? We are vagabond ex-pirates, which is not the best pedigree for reliable testimony.\"\n\n\"But I believe you, by God!\" He produces an envelope and hands it to you. \"This is a DEED OF OWNERSHIP for a sloop that I own in Port Selenice. She's just a small craft, but better than no ship at all. Go to Selenice, get together a crew, and see if you can't beat this Skarvench at his own game.\"\n\nThanking Capstick for his help, you take your leave. \"I'm only sorry not to be sailing with you,\" are his parting words.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::DEED_OF_OWNERSHIP});
    }

    int Continue(Character::Base &player) { return 107; }
};

class Story070 : public Story::Base
{
public:
    Story070()
    {
        ID = 70;

        Text = "Most of the tavern's customers have scurried off into the night. Nursing your injuries, you stagger through the wreckage and take a stiff swig of rum from an overturned bottle on the bar.\n\nA weak bloody-mouthed spluttering comes from under broken trestle. Stepping over, you haul the chief cut-throat to his feet. With his teeth broken and his little close-set eyes swollen half closed, he doesn't look nearly so tough now -- like a lot of bullies you've known after the fight's been knocked out of them.\n\n\"Skarvench's new ship,\" you say, shaking him. \"What's it called?\"\n\nHis eyes flicker open. \"Can't tell you,\" he groans. \"He'd rip my lungs out.\"\n\nYou break the rum bottle against the wall and shove it towards his chest. \"He won't be able to find your lungs.\"\n\nThe threat breaks what's left of his nerve. In a panic stricken torrent, he blabbers about a ship called the Moon Dog which Skarvench is having built in Port Selenice.\n\nYou cast the lout back into the debris. As you go to leave you find the innkeeper, Drood, standing by the doorway, hopping from one foot to the other in agitation. \"Who's going to pay for this damage?\" he wails.\n\nBlutz pushes him aside. \"Don't think of it as damage. Think of it as a free redecoration.\"\n\nWith a laugh, the four of you set off along the street.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 392; }
};

class Story071 : public Story::Base
{
public:
    Story071()
    {
        ID = 71;

        Image = "images/filler4-green.png";

        Text = "The blind man is Greymalkin Smith. Once a pirate himself, he was blinded in powder keg explosion and now ekes out a living running errands around town and swapping gossip for drinks.\n\nYou have also seen the three ruffians before. In fact, just a few weeks ago you learned that the governor of Leshand has put a price on their heads.";

        Choices.clear();
        Choices.push_back(Choice::Base("Talk to Greymalkin", 33));
        Choices.push_back(Choice::Base("Intervene to stop the ruffians bullying the scholar", 52));
        Choices.push_back(Choice::Base("Go off to the shipyard", 374));

        Controls = Story::Controls::STANDARD;
    }
};

class Story072 : public Story::Base
{
public:
    Story072()
    {
        ID = 72;

        Image = "images/filler2-green.png";

        Text = "His laughter is the peal of summer thunder. \"Scurry off then, little mice. I mistook you for a sea rats at least!\"\n\nThe dolphin and the shark convey you back to the beach where you blew the horn. In awed silence, still stunned by the uncanny adventure, you disembark uncertainly and stagger on weak knees up the shore.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 203; }
};

class Story073 : public Story::Base
{
public:
    std::string PreText = "";

    Story073()
    {
        ID = 73;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Grappling hooks hug your vessel to the warship's flank, and marines come swarming over the rail with loud battle-cries. The fighting rages from stem to stern -- the clash of cutlasses, the bangs and acrid smoke of pistol shots, the screams of wounded men. Blood and gunpowder are the smells mingling on the briny breeze this afternoon.\n\nThe marines have numbers on their side, but they are pitched against some of the toughest buccaneers on the Carab Sea. Your men know they are fighting for their very lives, since almost every one of them has a price on his head.\n\n";

        auto DAMAGE = -6;

        if (Character::VERIFY_SKILL(player, Skill::Type::BRAWLING))
        {
            PreText += "[BRAWLING] ";

            DAMAGE = -3;
        }

        if (Character::VERIFY_SKILL(player, Skill::Type::SWORDPLAY))
        {
            PreText += "[SWORDPLAY] ";

            DAMAGE = -2;
        }

        if (Character::VERIFY_SKILL(player, Skill::Type::MARKSMANSHIP))
        {
            PreText += "[MARKSMANSHIP] ";

            DAMAGE = -2;
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Point(s).";

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 225; }
};

class Story074 : public Story::Base
{
public:
    Story074()
    {
        ID = 74;

        Text = "It is only a matter of minutes before you hear the sound you were dreading: an ominous scraping as the ship lurches to a halt. \"That tears it!\" says Grimes. \"We've run aground.\"\n\nA hasty inspection reveals that you have run the keel onto a sandbank. There is no damage to the hull, but you will have to wait until high tide to get off again. By now the fog is closing tightly around the bay, blotting out any sight of the island.\n\n\"We may as well sit it out until dawn,\" you decide.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 366; }
};

class Story075 : public Story::Base
{
public:
    Story075()
    {
        ID = 75;

        Text = "The storm fills the sky and your ship is just a speck in its grip. The rain lashes down out of a darkness blacker than night, drumming the deck. Waves as high as cliffs sweep past, flooding over the side and forcing each man to cling on for dear life. Your orders are drowned out by the palpable roar of the wind, which strains the sails to bursting point. You take the whipstaff yourself and push the prow into the onrushing tumult, seeking the hurricane's heart.\n\nGrimes rushes back, his face contorted with fear. \"Skipper!\" he cries. \"The hurricane must have scattered the Queen's fleet! There's a Gloriannic warship dead across our bows, and the wind's sweeping her straight towards us!\"\n\nYou can see the ship between billowing sheets of rain. Her mast is broken and she is careening out of control towards you. You have only seconds in which to avoid a collision.";

        Choices.clear();
        Choices.push_back(Choice::Base("Tilt the whipstaff to port", 113));
        Choices.push_back(Choice::Base("... to starboard", 132));

        Controls = Story::Controls::STANDARD;
    }
};

class Story076 : public Story::Base
{
public:
    Story076()
    {
        ID = 76;

        Text = "To your own amazement as much as your foe's, the weasel suddenly jumps out of your haversack and leaps across the deck to give him a painful bite on the hand. Skarvench drops the taper with a startled oath: \"Agh! Devil take the animal!\"\n\nHe seizes the weasel by its neck and casts it off over the side, but its attack has bought you the time you need to close in. Now you are face to face with Skarvench in a battle to the finish.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 171; }
};

class Story077 : public Story::Base
{
public:
    Story077()
    {
        ID = 77;

        Image = "images/filler2-green.png";

        Text = "Skarvench gives a sharp cough as he swigs a shot of rum. \"Guarded?\" he snarls. \"Aye, she'll be guarded. But what if a storm scattered her escort fleet? What then, eh my lads?\n\n\"There'd still be her flagship to contend with, Cap'n\" objects the quartermaster. \"The Rose, I'm told it's called -- a ship of eighty cannon!\"\n\n\"It's possible to pluck a rose, me hearties!\" rejoins Skarvench with a peal of harsh laughter. \"Specially when she lies becalmed, shrouded in mist with no target for her guns.\"\n\n\"But what's this talk of mist and dead calm?\" queries Borograve the master gunner. \"I thought the plan rested on a storm?\"\n\n\"It all relies too much on chance, if you ask me,\" says the first mate.\n\nYou tend to agree -- although you never knew Skarvench to trust anything to luck before, not even when playing dice. You are itching to hear how he is going to justify his scheme, but every second you linger here increases the risk of discovery.";

        Choices.clear();
        Choices.push_back(Choice::Base("Continue to eavesdrop regardless of the danger", 115));
        Choices.push_back(Choice::Base("Snatch a few supplies from the empty cabin opposite", 96));
        Choices.push_back(Choice::Base("Go straight back on deck empty-handed", 172));

        Controls = Story::Controls::STANDARD;
    }
};

class Story078 : public Story::Base
{
public:
    Story078()
    {
        ID = 78;

        Text = "Two more boxes are swiftly opened, their lids splintering under hard shovel-blows. These also contain dead bodies lying on bars of silver. The third gives you particular cause to shudder -- a thin rill of blood has caked on its lips, just as a careless or gluttonous man might leave a dribble of gravy.\n\n\"Vampires!\" gasps Blutz. All together you turn to look at the sun, now almost drowned in the western sea. In mere moments the last of the daylight will have drained away.\n\nBlutz pulls a stick from his belt and thrusts it into your hand. It is the broken stool-leg he got clouted with back in the tavern in Selenice. The end has splintered to leave a sharp point. Sharp enough to pierce a heart, if driven down with courage and strength.\n\nThere is just time to impale one of the three corpses you've unearthed. You glance from one to other. Which will it be?";

        Choices.clear();
        Choices.push_back(Choice::Base("Choose the body with blood on its lips", 169));
        Choices.push_back(Choice::Base("... the one with a skull tattoo", 188));
        Choices.push_back(Choice::Base("... the one with ice-blue eyes", 150));

        Controls = Story::Controls::STANDARD;
    }
};

class Story079 : public Story::Base
{
public:
    Story079()
    {
        ID = 79;

        Text = "As the cannibals close in, things look bleak indeed. Can you possibly outrun them and get the jollyboat out to sea before you are overwhelmed? Then you remember seeing fragments of coloured chalk further up the beach. \"Come on,\" you say urgently, pulling your companions after you, \"I've got an idea.\"\n\nThe cannibals follow in sullen silence as you retreat along the beach. Pretending to stumble, you gather pieces of pink chalk as you go and use these to daub spots on your skin. At first the others think you've lost your wits, but then Blutz sees what you have in mind. \"They'll think we're plague ridden!\" he cries. \"They certainly won't want to eat us then!\"\n\nThe four of you crouch shivering beside your boat as he cannibals come striding up. At first the look on their faces is one of ravenous glee, but this soon changes to horror when they get close enough to see the ugly blotches on your skin. The shivering helps to make it look as though you have a fever, but in fact there is no need for pretence -- you really are quaking in fear by now.\n\nYou give a ghastly moan and start to foam convincingly at the mouth. This is more than enough for the cannibals. Flinging down their weapons, they run off. Once they are out of sight along the beach, you get up and examine what they have left behind. Along with a profusion of spears and clubs, you find a FEATHER SHIELD and a SHARK's TOOTH SWORD. The latter is a blade of hardwood edged with shark's teeth -- unconventional but it serves as well as a normal sword.";

        Bye = "The others have lost no time getting the boat into the water. Hurrying in case the cannibals should realise they've been tricked and return, you put to sea.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Take = {Item::FEATHER_SHIELD, Item::SHARKS_TOOTH_SWORD};

        Limit = 2;
    }

    int Continue(Character::Base &player) { return 116; }
};

class Story080 : public Story::Base
{
public:
    Story080()
    {
        ID = 80;

        Text = "Moving with no more noise than a snake, you edge through the undergrowth until you are close enough to hear what Skarvench and the others. While the two seamen sweat over their spades, heaving up great clods of earth, Skarvench passes the grog bottle around and recounts his scurvy plans.\n\n\"So what's this treasure for, Cap'n?\" hiccups the quartermaster.\n\n\"To reward a certain shipwright in Port Selenice, for one thing,\" says Skarvench.\"He's to be paid in gold for the new ship he's building us.\"\n\n\"New ship?\" says Porbuck the mate, roused from his dull-witted torpor. \"I liked the old one.\"\n\nSkarvench ignores him. \"And the silver's for the Queen's wizard, William wild. He'll be supplying special sails for our new vessel -- aye, and a bit o' trickery into the bargain to ensure we take the Rose unhindered, me hearties!\" And he gives a low chuckle of perfect wickedness at the thought.\n\nThe scheming dog! His monstrous arrogance makes your blood boil.";

        Choices.clear();
        Choices.push_back(Choice::Base("Wait until they have taken the treasure aboard their ship and sailed off", 288));
        Choices.push_back(Choice::Base("Risk attacking them in your weakened state", 267));

        Controls = Story::Controls::STANDARD;
    }
};

class Story081 : public Story::Base
{
public:
    std::string PreText = "";

    Story081()
    {
        ID = 81;

        Choices.clear();
        Choices.push_back(Choice::Base("Run away now", 5));
        Choices.push_back(Choice::Base("Continue the duel with either a whirlwind spell", 62));
        Choices.push_back(Choice::Base("... or a darkness spell", 100));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "A torrent of red fire crackles around Ejada but she stands steadfast, weathering the onslaught. Your spell fades leaving her charred and withered like a burnt wooden effigy. But then, in front of your astonished gaze, she rapidly regenerates and in seconds is completely unscathed!\n\n\"My mother's gift to her daughter: unending vitality,\" she explains with a triumphant smile. Then with a gesture she causes fists of rock to rip up out of the ground and pummel.\n\n";

        auto DAMAGE = -6;

        if (Character::VERIFY_ITEMS(player, {Item::Type::FEATHER_SHIELD}))
        {
            PreText += "[Item:: FEATHER SHIELD] ";

            DAMAGE += 3;
        }

        if (Character::VERIFY_SKILL(player, Skill::Type::CHARMS))
        {
            PreText += "[CHARMS] ";

            DAMAGE += 1;
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Point(s)";

        Text = PreText.c_str();
    }
};

class Story082 : public Story::Base
{
public:
    Story082()
    {
        ID = 82;

        Text = "\"She was El Draque's ship,\" says Kemp. \"A fine stout vessel. I did some work on her once. Curious to choose a bat as your figurehead, but that was El Draque for you. Those scarlet sails can't have been cheap, either. I hear he was captured by the Gloriannic Navy and hanged at sea for his crimes -- though what became of the Grue, I can't say.\"\n\nKemp has other customers to attend to, so you bid him good day and walk back to town.\n\n\"Where to now?\" says Oakley.\n\nYou think for a moment. \"We'll take rooms at the Sweat o' the Brow inn. If Skarvench shows his face anywhere in Selenice, it'll be there.\"\n\nYou have never spoken a truer word, for no sooner have you stepped through the doorway of the inn than you are rooted to the spot in shock. There the fiend stands, large as life in front of you. A rum bottle is clutched in his hand and his crew throng the tap-room around him, cowering as he subjects them to one of this thunderous drunken rants.\n\nThen his eye alights on you. His snarling voice is cut off in mid-sentence. A thin line of spittle runs down into his beard as his teeth show shark-like in a vicious grin. It is the moment you have waited for. Face to face with your dearest foe.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 14; }
};

class Story083 : public Story::Base
{
public:
    Story083()
    {
        ID = 83;

        Text = "Touching your magical amulet, you utter the words of a brief incantation that will deflect any curse the mermaid might attempt.\n\nAt this she pouts. \"Such crude magic.\"\n\n\"Crude, perhaps, my lady,\" you return with a gallant flourish, \"but I have always found it no less effective for that\"";

        Choices.clear();
        Choices.push_back(Choice::Base("[SPELLS] Bring her under hypnotic control", 102, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("Tell Blutz to let her go at once", 121));
        Choices.push_back(Choice::Base("Ask her what lies ahead on your journey", 140));
        Choices.push_back(Choice::Base("Ask her about the best course you can take to Port Leshand", 159));

        Controls = Story::Controls::STANDARD;
    }
};

class Story084 : public Story::Base
{
public:
    Story084()
    {
        ID = 84;

        Text = "Most of the hands are just bare bone, but a couple still show traces of skin and sinew. One even wears a gold ring, though none of you cares to fish it out of the tank. \"I'm glad we haven't drunk from this,\" says Oakley quietly, closing the lid. \"No wonder the captain prefers wine. It could fair kill a bloke's thirst for fresh water, it could.\"\n\n\"Here's what did the job,\" announces Grimes, picking something up off the deck. He hands it to you: a long-bladed butcher's cleaver.\n\n\"I'm for leaving right now,\" declares Blutz, quaking with fear. But as he tries to climb back down the jolly boat moored alongside, he makes an ominous discovery. \"I can't get over the rail. It's as if some supernatural force is tugging me back!\"\n\nThe same applies to the rest of you. \"The ship is cursed,\" says Grimes. \"And now shipmates, we're cursed too.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("[SEAFARING] Make repairs to the boat", 103, Skill::Type::SEAFARING));
        Choices.push_back(Choice::Base("Use a TOOLKIT", 103, {Item::TOOLKIT}));
        Choices.push_back(Choice::Base("Use [CHARMS]", 122, Skill::Type::CHARMS));
        Choices.push_back(Choice::Base("Otherwise", 141));

        Controls = Story::Controls::STANDARD;
    }
};

class Story085 : public Story::Base
{
public:
    Story085()
    {
        ID = 85;

        Image = "images/giant-crab-green.png";

        Text = "Before long the others call to you, saying they have collected a goodly share of barnacles and other succulent shellfish from the shore of the island. You have meanwhile been strolling around in search of fresh water, but every single pool that has formed in depressions in the rock has turned out to be full of brine.\n\nSuddenly there is a shuddering underfoot. The whole island begins to shake. Your companions utter cries of alarm and you see them run towards the boat, abandoning their pile of shellfish. \"It's sinking into the sea!\" screeches Blutz. \"Hurry or we'll be drowned!\"\n\nOut of the corner of your eye you see something break the surface of the sea. You turn watching aghast as it rises high up into the air. It is sharp and huge, its serrated edge casting an orange-red shadow across the sky. As it flexes open and closed, you stare at it dumbfounded. And then you realise what it is: a giant pincer.\n\nThe shock almost makes you pass out. This is no island. You're on the back of a gigantic crab.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
        {
            return 123;
        }
        else
        {
            return 142;
        }
    }
};

class Story086 : public Story::Base
{
public:
    Story086()
    {
        ID = 86;

        Text = "Maybe it is ungracious to harbour suspicions about Mortice when he has been kind enough to feed you. All the same, you cannot help but notice certain disquieting facts. For one thing, the supply of food and water he has left is amazing given that he shows every sign of having been adrift for weeks. Also, he declined to eat or drink anything himself while you were eating, not even joining your toast at the end of the meal. His bald statement on the subject was, \"I never drink grog.\" That is a very odd thing for any seaman to say. Finally, his insistence at getting a formal invitation to board your boat, along with the fact that he apparently finds the moonlight rather bright for his eyes, is little short of sinister.\n\nOn the other hand, maybe you've just been at this game too long. Its your choice.";

        Choices.clear();
        Choices.push_back(Choice::Base("Invite him aboard", 143));
        Choices.push_back(Choice::Base("Let him spend the night where he is", 162));

        Controls = Story::Controls::STANDARD;
    }
};

class Story087 : public Story::Base
{
public:
    Story087()
    {
        ID = 87;

        Text = "Skarvench's face twists into a broad smile as he sees you striding along the foreshore towards him. But it is a smile to make your blood run with ice: the smile on a wolf's face before it seizes its prey.\n\n\"Ah, so you blokes have fared well!\" he thunders. \"Still hale and hearty, I see. And glad I am to see it, for I wanted to savour your deaths meself. Just knowing you'd been drowned would have left me inconsolable, like.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Fight him here and now", 182));
        Choices.push_back(Choice::Base("Use a THUNDERCLOUD FAN", 315, {Item::THUNDERCLOUD_FAN}));
        Choices.push_back(Choice::Base("Use a BAT-SHAPED TALISMAN", 334, {Item::BAT_SHAPED_TALISMAN}));
        Choices.push_back(Choice::Base("Bide your time", 201));

        Controls = Story::Controls::STANDARD;
    }
};

class Story088 : public Story::Base
{
public:
    Story088()
    {
        ID = 88;

        Text = "Rumours abound in a port like Leshand. Some are mere gossip, some are tall tales, some are outright lies -- and a very few are the gospel truth. The trick lies in telling the difference.\n\nYou keep your ear to the ground for a day or two, trawling the taverns on the lookout for information. What are are you interested in finding out about?";

        Choices.clear();
        Choices.push_back(Choice::Base("Look for rumours concerning the pirate El Draque", 183));
        Choices.push_back(Choice::Base("Look for information on Queen Titania's state visit", 221));
        Choices.push_back(Choice::Base("Hear news of Skarvench", 297));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::STREETWISE))
        {
            Choices[0].Destination = 164;
            Choices[1].Destination = 202;
            Choices[2].Destination = 278;
        }
        else
        {
            Choices[0].Destination = 183;
            Choices[1].Destination = 221;
            Choices[2].Destination = 297;
        }
    }
};

class Story089 : public Story::Base
{
public:
    Story089()
    {
        ID = 89;

        Text = "\"You've given me a cannon-load o' trouble,\" says Skarvench. \"Here's where I pay you back -- with my trusty basilisk here.\"\n\nYou glance down to see that he is standing beside a cannon which is pointing straight at you. Skarvench shows you the lighted taper in his hand.\n\n\"You despicable cur!\" you snarl. \"You've no stomach for facing me at close quarters, I see.\"\n\n\"Stow your bluster, mate,\" he sneers. \"Here's where you retire to a safe distance. Thirty fathoms down!\"";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_ITEMS(player, {Item::Type::WEASEL}))
        {
            Choices.push_back(Choice::Base("[MARKSMANSHIP] Use a PISTOL", 95, Skill::Type::MARKSMANSHIP));
            Choices.push_back(Choice::Base("[CHARMS] Use a MAGIC AMULET", 114, Skill::Type::CHARMS));
            Choices.push_back(Choice::Base("Use [AGILITY]", 133, Skill::Type::AGILITY));
            Choices.push_back(Choice::Base("Otherwise", 152));
        }
    }

    int Continue(Character::Base &player) { return 76; }
};

class Story090 : public Story::Base
{
public:
    Story090()
    {
        ID = 90;

        Text = "You fetch a foaming stoop of ale. After fastidiously transferring the contents to his odd saucer-shaped goblet, he turns his blind gaze on you. \"You were with that Skarvench, weren't ye?\"\n\n\"How did you --?\" begins Blutz.\n\nHe holds up his hand. \"I hears a thing or two. Like about Skarvench doin' in old Marshy. I sailed with Marshy, lads, once upon a time, and Skarvench weren't fit to spit upon his shoes. Talkin' of Skarvench, you know the new ship he's had built, the Moon Dog? Fitted with silver sails that came in a crate all the way from Glorianne. An' why did Skarvench keep askin' around about full moons an' cloud cover an' such -- ain't tide tables good enough for him no more? Makes you wonder, mates. Is it lunacy, or is there method in his madness?\"\n\nHe's a fine one to talk about lunacy,\" whispers Grimes as you get up to leave.\n\n\"I heard that too!\" screeches Greymalkin after you. \"Ye'd do well to pay heed to what I told you, if ye want to live. Watch out for that basilisk he had shipped aboard an an' all.\"";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_SKILL(player, Skill::Type::FOLKLORE) && !Character::VERIFY_SKILL(player, Skill::Type::SEAFARING))
        {
            Choices.push_back(Choice::Base("Step in to save the scholar from being bullied", 52));
            Choices.push_back(Choice::Base("Go to the shipyard", 374));
        }
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::FOLKLORE))
        {
            return 385;
        }
        else
        {
            return 109;
        }
    }
};

class Story091 : public Story::Base
{
public:
    Story091()
    {
        ID = 91;

        Image = "images/filler3-green.png";

        Text = "A key that no-one can see or touch? A riddle set by an ocean god is a mere trifle for an artful trickster like yourself. Pursing your lips, you whistle a few bars of a jaunty tune. To the amazement of others, this causes the chain to unlock itself and fall aside, giving you admittance to the harbour.\n\nYou spread your hands and take a bow. \"It was the key of C,\" you explain with a smile.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 205; }
};

class Story092 : public Story::Base
{
public:
    Story092()
    {
        ID = 92;

        Choices.clear();

        Controls = Story::Controls::NONE;
    }

    int Background(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORD(player, Codeword::Type::ICARUS))
        {
            return 130;
        }
        else
        {
            return 149;
        }
    }
};

class Story093 : public Story::Base
{
public:
    Story093()
    {
        ID = 93;

        Text = "With your every thought focussed on the goal of finding the iceberg, you are blinded to the stirrings of mutiny. Oakley, Grimes and Blutz come to your cabin. Although you are all old comrades, they seem nervous in the face of your driving obsession. \"Skipper,\" begins Oakley, \"the crew are discontent. They fear you'll sail us off the edge of the world.\"\n\n\"Edge of the world? Pah!\" you fling your charts down and take a swig of rum. \"It's a thousand leagues from here, at least.\"\n\n\"I don't care for the look on their faces, Cap'n,\" presses Grimes. \"They look like mourners at a funeral -- our funeral, if you won't turn back.\"\n\nYou give a sour scowl. \"And you, Mister Blutz? Are you party to this insubordination too?\"\n\n\"I'd sail with you to hell, skipper, if you asked me,\" replies Blutz. \"It's just... well, I never till now though you'd ask!\"\n\nSuddenly the door crashes in. The crew stand there with drawn swords, the bo'sun at their head. \"Out on deck,\" he growls. \"'Tis time we settled this.\"\n\nYou and your comrades are hauled up and tied. A plank is fixed out over the side of the ship. Even now, it is livid rage rather than fear that consumes you. You curse them for their perfidy, but to no avail. With a sword at your back, you are forced to climb over the rail and walk until you run out of plank...";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story094 : public Story::Base
{
public:
    Story094()
    {
        ID = 94;

        Text = "It seems like hours. At last the storm blows over. The full moon appears -- a blazing white beacon. The clouds go draining away like pools of quicksilver in the vast dark blue dish of the sky.\n\n\"Ship ahoy!\" cries the lookout. \"She's the Rose!\"\n\nIt is indeed the Queen's proud flagship, her spars snapped and rigging torn from the storm she's just weathered. Even so, she is a daunting oaken fortress on the slow swell of the ocean. There is no sign of the escort fleet -- presumably scattered or sent to the deeps by the recent hurricane. You order a cautious approach, wary in case the Rose's gunners open fire on you out of panic.\n\nBut this uncanny night still has surprises in store, it seems. As you draw closer to the drifting Rose, thick white fog boils out from nowhere and spreads rapidly across the sea. Within a minute it has entirely obscured your view of the ship. You gaze out at the blanket of fog, luminous in the moonlight, sitting on the waters like a malevolent entity. Tendrils drift across your own deck, and the crew look up at you with expressions of confusion and fear.\n\nYou sniff the air. \"There's a smell of sorcery here, my lads,\" you say to the others.\n\n\"Look up there!\" cries one of the sailors, and suddenly there is a moan of awestruck amazement from everyone on deck. You lift your eyes towards the sky and feel a sudden chill of supernatural dead. Sailing down out of the scattered clouds, her silver sails filled with lunar light, comes Skarvench's enchanted galleon: the Moon Dog.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!(Character::VERIFY_CODEWORD(player, Codeword::Type::HORAL) && Character::VERIFY_ITEMS(player, {Item::Type::POCKET_WATCH})))
        {
            Choices.push_back(Choice::Base("Use a BAT-SHAPED TALISMAN", 151, {Item::BAT_SHAPED_TALISMAN}));
            Choices.push_back(Choice::Base("Use a BLACK KITE", 170, {Item::BLACK_KITE}));
            Choices.push_back(Choice::Base("Otherwise", 208));
        }
    }

    int Continue(Character::Base &player) { return 189; }
};

class Story095 : public Story::Base
{
public:
    Story095()
    {
        ID = 95;

        Image = "images/filler2-green.png";

        Text = "Calmly levelling your PISTOL, you shoot the end off the taper. \"By all that's unholy!\" sears Skarvench. \"I never seen such a shot!\"\n\nNeither have you, but you do not let surprise cost you your momentary advantage. You race in before Skarvench can relight the fuse, and in seconds the two of you are locked in a fight to death.\n\nYou were not able to reload your PISTOL in time. You will not be able use it again.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        for (auto i = 0; i < player.Items.size(); i++)
        {
            if (player.Items[i].Type == Item::Type::PISTOL)
            {
                // Disable first pistol
                player.Items[i].Charge = 0;

                break;
            }
        }
    }

    int Continue(Character::Base &player) { return 171; }
};

class Story096 : public Story::Base
{
public:
    Story096()
    {
        ID = 96;

        Text = "You hurry into the cabin, startling the pet MONKEY which is perched on the bunk. Immediately it starts jumping up and down, chittering wildly, and the only thing you can do is grab it and stuff it into your haversack. Praying that no-one heard the noise, you head up on deck.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::MONKEY});
    }

    int Continue(Character::Base &player) { return 172; }
};

class Story097 : public Story::Base
{
public:
    std::string PreText = "";

    Story097()
    {
        ID = 97;

        Choices.clear();
        Choices.push_back(Choice::Base("Go ashore", 173));
        Choices.push_back(Choice::Base("Sail on towards the next island", 116));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Taking turns at the oars, you row westwards under the glare of a fierce sun. Soon your lips are parched, your necks blistered red in the heat. Everyone's spirits were at first buoyed up by the relief you felt at escaping from Skarvench's grasp, but soon you begin to wilt with the awful gnawing of discouragement and doubt. Will you survive long enough to reach land, or will the little jollyboat become your floating coffin?\n\n";

        if (Character::VERIFY_SKILL(player, Skill::Type::WILDERNESS_LORE))
        {
            PreText += "[WILDERNESS LORE] You soaked your clothes in the water to protect yourself from the heat.";
        }
        else
        {
            Character::GAIN_LIFE(player, -1);

            PreText += "You LOSE 1 Life Point through thirst, fatigue and heatstroke.";
        }

        if (player.Life > 0)
        {
            PreText += "\n\nAround noon of the second day you catch sight of Red Skull Island. \"Well?\" mutters Grimes through thirst-blackened lips. \"Do we risk going ashore? There might be fresh water... and food.\"\n\n\"Aye says Oakley.\" \"And it's us that might be the food, if there are cannibals in these parts.\"\n\nThey look to you to make the final decision.";
        }

        Text = PreText.c_str();
    }
};

class Story098 : public Story::Base
{
public:
    Story098()
    {
        ID = 98;

        Text = "The chief of the islander arrives. He is a very big man adorned in feathers and glass trinkets, with a weathered grey face like a carving in driftwood. Dipping his finger in a coconut-shell dish carried by an attendant, he proceeds to draw a design on your face in red dye.\n\n\"It's just like the warpaint of these natives,\" says Grimes, looking at you. \"I wonder what that means?\"\n\n\"Maybe he's inviting me to join the tribe,\" you say with a wry smile.\n\nNext the tribal shaman comes forward and draws a picture in the sand with his long bony fingers. It shows a woman with a scorpion crown. He spits on the picture, then lifts his ceremonial sceptre and points westwards. The chief says something which sounds like, \"Matya Ejada niyu,\" and each of the islanders in turn nods and repeats the words before stamping on the picture. Before long the image is completely lost in the scuffed sand.\n\n\"A curious little ritual,\" remarks Oakley. \"Now, why don't we shove off, mates before we outstay our welcome?\"\n\nYou have to agree. Clambering into the boat, you row off watched by the horde of silent islanders. \"You're not going to leave that warpaint on your face, are you?\" Oakley asks when you are well clear of the shore. \"It makes you look like a ruddy heathen.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Wash off the dye before it dries", 116));
        Choices.push_back(Choice::Base("Leave it", 116, Choice::Type::GET_CODEWORD, Codeword::Type::SCRIP));

        Controls = Story::Controls::STANDARD;
    }
};

class Story099 : public Story::Base
{
public:
    std::string PreText = "";

    Story099()
    {
        ID = 99;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Recognizing its former master, the little animal suddenly slips out of your grasp, bursts from the undergrowth and goes scampering towards him. Skarvench and his men leap up and seize their weapons, instantly alert. Standing rigid with a snarl stamped on this cruel face, Skarvench scans the jungle and then his eyes lock on yours despite the cover of foliage. You realise the game is up -- he's spotted you. You rise to your feet with a defiant battle-cry as he levels his pistol. Thirty paces separate you -- a distance you might cover in six seconds, from a standing start. A bullet can cross it in an instant...\n\nJust as Skarvench squeezes the trigger, the MONKEY leaps up and gives his wrist a painful nip. He bellows in range and the shot goes wide, whistling past your ear to embed itself in the bole of a tree. But you have no time to give thanks; within moments the pirates have closed in. The battle is joined, and you and your comrades are fighting for your lives.\n\n";

        if (Character::VERIFY_ALL_SKILLS(player, {Skill::Type::SWORDPLAY, Skill::Type::MARKSMANSHIP}))
        {
            Character::GAIN_LIFE(player, -7);

            PreText += "[SWORDPLAY] [MARKSMANSHIP] You LOSE 7 Life Points.";
        }
        else if (Character::VERIFY_ALL_SKILLS(player, {Skill::Type::BRAWLING, Skill::Type::MARKSMANSHIP}))
        {
            Character::GAIN_LIFE(player, -8);

            PreText += "[BRAWLING] [MARKSMANSHIP] You LOSE 8 Life Points.";
        }
        else
        {
            PreText += "Your combination of skills are insufficient to save you. You are quickly slain.";

            player.Life = 0;
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 23; }
};

class Story100 : public Story::Base
{
public:
    Story100()
    {
        ID = 100;

        Text = "Utter blackness falls like an iron door. You can hear your foe raging blindly, casting deadly bolts of occult force at random into the dark in her frenzied efforts to slay you.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_SKILL(player, Skill::Type::ROGUERY))
        {
            Choices.push_back(Choice::Base("Follow up your advantage with a whirlwind spell", 62));
            Choices.push_back(Choice::Base("Take advantage of the cover of darkness to sneak back to the boat", 6));
        }
    }

    int Continue(Character::Base &player) { return 176; }
};

class Story101 : public Story::Base
{
public:
    Story101()
    {
        ID = 101;

        Text = "Only one thing can save you and your comrades now. You must summon a rainstorm to provide you with the drinking water you so desperately need. But despite the dire straits you are now in, you cannot help hesitating. Conjuring with the weather is a risky business at best of times. The slightest slip can turn a breeze into a typhoon, or a scatter of snowflakes into a raging blizzard. You remember a time years ago, when you were just an apprentice wizard. You tried to conjure a sunny afternoon so you could go picnicking, only to start a three-week heat wave that burnt the fields brown and reduced rivers to muddy trickles.\n\nYou gaze a the wand in your hand. Mistakes like that are a long way in your past; you are an accomplished sorcerer now. On the other hand, the hurricane season is looming just a month away, and that makes the risk in summoning a storm particularly high.\n\n\"What are you waiting for?\" says Blutz. \"We'll die without fresh water.\"\n\n\"And what if rain swamps our boat and it sinks?\" you ask him. \"We'll be just as dead.\"\n\nDecide.";

        Choices.clear();
        Choices.push_back(Choice::Base("Try conjuring rain", 10));
        Choices.push_back(Choice::Base("Otherwise", 120));

        Controls = Story::Controls::STANDARD;
    }
};

class Story102 : public Story::Base
{
public:
    Story102()
    {
        ID = 102;

        Text = "\"Give me a hand!\" says Blutz. \"She's as slippery as a salmon.\"\n\nThe mermaid thrashes in his grasp, churning up sea-foam with her powerful tail, but Oakley and Grimes hurry to help, holding her fast until you can complete your spell. You chant the words. Her eyes glaze like frost; her struggling ceases. For a brief time, the magic makes her your slave.\n\n\"What is our best route home?\" you demand of her.\n\n\"Home?\" she says dully, speaking as though in deep sleep. \"Where is home?\"\n\n\"The far west. Port Leshand.\"\n\n\"Sail on your present course if you fear neither weird dooms nor fierce weather. Steer south if a witch's hospitality does not daunt you. West to face rain and wind and the nightmare ship; south to see the earth god's daughter.\"\n\nThere is along pause while you all weigh up these words. \"Er, perhaps not as lucid as we might've hoped...\" says Grimes.\n\n\"The best we'll get from a faerie creature, enthralled or not,\" you tell him. You dismiss the mermaid, breaking the spell with a snap of your fingers.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 178; }
};

class Story103 : public Story::Base
{
public:
    Story103()
    {
        ID = 103;

        Text = "You get the others' help in hooking the jollyboat's mooring rope and winching it up onto the desk by means of pulleys attached to the ship's yardarm. \"At least we can make sure our little craft is seaworthy,\" you tell the others as you bend to examine whatever damage the boat has taken during the days you have spent on the open ocean.\n\n\"Are you stark mad?\" says Oakley. \"We're trapped aboard a cursed ship, and all you find to do is fiddle with the damned jollyboat!\"\n\nYou hum a few bars of a sea shanty, then look up from your work with a relaxed grin. \"Let's think of a plan while we fix our boat up, mates. That way we'll be ready to jump ship when the chance comes our way.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::REMOVE_CODEWORD(player, Codeword::Type::DETRUDE);
        Character::REMOVE_CODEWORD(player, Codeword::Type::PECCANT);
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::CHARMS))
        {
            return 122;
        }
        else
        {
            return 141;
        }
    }
};

class Story104 : public Story::Base
{
public:
    Story104()
    {
        ID = 104;

        Text = "Certain features of this island are ominously reminiscent of an old sea-myth concerning the giant crab Pusat Tassek. This crab is said to be as big as a house. It basks in mid-ocean with the top of its shell exposed, sometimes staying in one place so long that sands gathers on its back and plants start to grow there, all the while feeding on fish that it attracts to its maw with a sweet-smelling chemical secretion.";

        Choices.clear();
        Choices.push_back(Choice::Base("Stay here to look for food", 85));
        Choices.push_back(Choice::Base("Put to sea heading on your previous course westward", 47));
        Choices.push_back(Choice::Base("Turn north towards the Smoking Islands", 66));

        Controls = Story::Controls::STANDARD;
    }
};

class Story105 : public Story::Base
{
public:
    Story105()
    {
        ID = 105;

        Image = "images/filler4-green.png";

        Text = "\"So,\" says Mortice as you settle down to sleep, \"are you going to invite me aboard your boat, or leave me here on my blessed raft all night?\"\n\nOakley smiles at him. \"Are you standing on ceremony, mate? Waiting for a bloody invite?\"\n\nMortice takes ill against this joking retort. \"Aye,\" he growls, spitting into his beard. \"An invite's just what I'm after. Well, haven't ye dined like lords at my expense until you're as full as farmyard geese? Call me over, damn your veins!\"\n\nBlutz is understandably not keen to sleep beside a lunatic, no matter how charitable. He turns to you and mutters under his breath, \"Well, our boat's pretty cramped already -- and no more comfortable than his raft, I'd say.\"\n\n\"What's that whispering?\" snarls Mortice, stamping his foot. \"Secrecy and distrust!\" Is this how you repay a bit o' kindness, eh? Come on, will you ask me aboard or not?\"\n\n\"Ask the skipper,\" says Grimes, nodding towards you.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_SKILL(player, Skill::Type::FOLKLORE))
        {
            Choices.push_back(Choice::Base("Ask Mortice to come aboard", 143));
            Choices.push_back(Choice::Base("Let him stay on his raft", 162));
        }
    }

    int Continue(Character::Base &player) { return 86; }
};

class Story106 : public Story::Base
{
public:
    Story106()
    {
        ID = 106;

        Image = "images/jewel-of-heaven-green.png";

        Text = "The clouds are black banners across the scarlet of sunset when, gazing into the face of approaching night, you spy a billowing sail gleaming wanly in the dusk. A ship bound for Leshand! Jumping to your feet, shouting and waving, you wait anxiously until an answering hail tells you they've seen you. The ship comes nearer, her prow sliding though the twilit waters, her sails pinned like sheets of gold against the darkening sky. Faces look down from the rail, and a rope ladder is lowered. You climb rapidly despite your fatigue, gladdened by the friendly speech of the sailors.\n\nA hand grasps yours and helps you up. \"Welcome aboard the Jewel of Heaven,\" says a Gloriannic voice. You do not reply at once, but fall on your knees alongside Oakley and the others, thanking almighty God for deliverance from the brink of doom.";

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 370; }
};

class Story107 : public Story::Base
{
public:
    Story107()
    {
        ID = 107;

        Text = "Finding a secluded snug in a tavern away from the docks, you consult with your friends as to what your next move should be.\n\nBlutz is all for telling the authorities what you know, \"They're in a better position than we are to protect Queen Titania,\" he argues.\n\n\"I disagree,\" says Grimes, \"An opportunity like this won't quickly come our way again. It's like the tide: take it at the flood and fortune follows; wait till it's out and you've missed your boat.\"\n\n\"We should go to Port Selenice,\" says Oakley. \"That's where Skarvench will go next. \"Let's see if we can't steal a march on the fiend and scupper his plans. The Gloriannic authorities will reward us richly, but even more important than that --\n\n\"More important than that, we get our revenge on Skarvench,\" you finish.";

        Choices.clear();
        Choices.push_back(Choice::Base("Head straight for Selenice", 145));
        Choices.push_back(Choice::Base("Go to the governor first", 126));

        Controls = Story::Controls::STANDARD;
    }
};

class Story108 : public Story::Base
{
public:
    Story108()
    {
        ID = 108;

        Text = "The days pass, balmy and full of ease after your long deprivation. With rest and food you recover quickly from your ordeal.\n\nAt last you catch sight of land, and after tacking along the coast for a few hours you arrive at Leshand harbour. A forest of masts sways along the wharf, and the sharp smells of tar and fish waft on the air. As the Jewel of Heaven ties up at the quayside, you are anxious to gather your few belongings and go ashore.\n\n\"Dry land,\" says Oakley, in the tone of a man greeting his long-lost sweetheart. \"I never thought to see it again!\"\n\nThe captain and crew are busy with unloading their cargo. You thank them, shaking each man's hand as you press across the deck and make your way down the gangplank.\n\nThe dock is a confused bustle, with longshoremen and sailors teeming around and wagons trundling to and fro. Pushing through the milling crowds, you head along a narrow alley in search of an inn.";

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 9; }
};

class Story109 : public Story::Base
{
public:
    Story109()
    {
        ID = 109;

        Text = "The basilisk is the name of a new type of powerful long-range cannon that has recently come into use on Gloriannic warships. They are not easy to obtain, being manufactured exclusively by the Queen's armourers at the Royal Arsenal. If Skarvench really has managed to lay his hands on one, he must have friends in high places at the Gloriannic court.\n\nThe commotion at the bar continues.";

        Choices.clear();
        Choices.push_back(Choice::Base("Head straight for Selenice", 52));
        Choices.push_back(Choice::Base("Go to the governor first", 374));

        Controls = Story::Controls::STANDARD;
    }
};

class Story110 : public Story::Base
{
public:
    std::string PreText = "";

    Story110()
    {
        ID = 110;

        Choices.clear();
        Choices.push_back(Choice::Base("Use both CORKSCREW and SHIP IN A BOTTLE", 261, {Item::CORKSCREW, Item::SHIP_IN_BOTTLE}));
        Choices.push_back(Choice::Base("Use DEED OF OWNERSHIP given to you by Master Capstick", 318, {Item::DEED_OF_OWNERSHIP}));
        Choices.push_back(Choice::Base("Pay with DIAMONDs", 299, {Item::DIAMOND}));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Type = Story::Type::NORMAL;

        PreText = "You lift your MAGIC WAND, occult syllables leaping to the front of your mind like war hounds eager to be unleashed. \"What can be locked can be unlocked,\" you assert. \"I shall open the chain by most potent art.\"\n\nThe colossus regards you with his cool majestic eyes. \"But, mortal: the chain is held closed by magic.\"\n\nYou laugh. \"Then I'll cast a spell to undo magic!\" No sooner do you, however, than the coracle is swept off away from the harbour at dizzying speed. If not for Blutz catching hold of your coat, you would have been thrown overboard. \"What's happened, skipper?\" he says as the four of you crouch terrified in the bottom of the coracle with the waves crashing against the sides.\n\n\"I forgot,\" you say with a groan. \"It was magic that brought us here in the first place. My spell undid that.\"\n\nIt is dawn by the time you reach Selenice. You are flung up onto the shore, and by the time you turn and look out to the sea, the coracle has vanished.";

        if (!Character::VERIFY_ITEMS(player, {Item::Type::CORKSCREW, Item::Type::SHIP_IN_BOTTLE}) && !Character::VERIFY_ITEMS_ANY(player, {Item::DEED_OF_OWNERSHIP, Item::DIAMOND}))
        {
            PreText += "\n\nYou have no hope of catching up with Skarvench. This is the end.";

            Type = Story::Type::DOOM;
        }
        else
        {
            PreText += "\n\nNow you must look for another way to obtain a vessel.";
        }

        Text = PreText.c_str();
    }
};

class Story111 : public Story::Base
{
public:
    Story111()
    {
        ID = 111;

        Text = "A rope is slung over the yardarm. The warship captain personally ties the end into a noose. As he puts it over your head, you cannot resist a few futile words of defiance. \"You enjoy your job, don't you?\" you snarl at him.\n\nHe gazes back at you coolly. \"I serve my Queen and country. That is all; there's nothing personal about this.\" He turns to the marines holding the end of the rope and gives a curt nod. You are hauled aloft to kick out your life under the shadow of you own ship's yardarm. It is a fate that awaits many pirates, and a far cry from the glorious destiny you dreamed of.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story112 : public Story::Base
{
public:
    Story112()
    {
        ID = 112;

        Image = "images/filler2-green.png";

        Text = "You have not long gone off watch, and are sitting in your cabin with a warming cup of grog, when there comes a stifled cry from up on deck. Bone weary, you throw on your cloak and grumpily stomp back up the companion-way. You are on the point of berating Blutz for calling out, certain that he has simply allowed the mist and the desolation of the spot to unnerve him, but the moment you emerge on deck those words choke off in your throat.\n\nEverything is swathed in the eerie greenish mist. Blutz stands amidships, backing away from the rail with little fluttering motions of his hands. You turn and behold the cause of his terror. Coming up over the side is a figure out of a nightmare -- a seaweed-draped corpse clad in robes sodden with sea water. As it climbs over the rail, its angular hunched stance and galvanic spasms of motion put you in mind of a spider's stalking gait. Patches of exposed bone show through the rotted flesh and it has only deep black sockets for eyes. In one hand it holds a rust-blotched sword; the other is rigid like a claw poised to strike.\n\n\"All hands on deck!\" Your voice is a thin reedy screech, strained by stark fear. Even as you hear the bustle of men rushing up from below, more of these ghastly apparitions appear at the rail, and you know that you are in for the toughest battle of your life.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 321; }
};

class Story113 : public Story::Base
{
public:
    Story113()
    {
        ID = 113;

        Text = "Your bows smash into the helpless warship with an anguished splintering of timbers. The ship lurches and you see at least one of your crew swept overboard by a titanic wave. He is immediately swallowed up by the storm's fury. There is nothing you can do to save him -- you may not even be able to save yourself.\n\nYou ship SUFFERS 2 damage.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::DAMAGE_SHIP(player, 2);
    }

    int Continue(Character::Base &player)
    {
        if (Character::CHECK_SHIP(player))
        {
            return 94;
        }
        else
        {
            return 227;
        }
    }
};

class Story114 : public Story::Base
{
public:
    Story114()
    {
        ID = 114;

        Text = "An all-purpose good luck charm is your best chance. Touching your amulet, you mutter the words of the cantrip at the same moment that Skarvench lights the basilisk cannon's fuse. There is a damp spluttering and then -- nothing.\n\n\"Misfire, curse it!\" snarls Skarvench. He pulls his sword from his belt. \"Very well, then, we'll have to settle our business up close an' personal, like.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 171; }
};

class Story115 : public Story::Base
{
public:
    Story115()
    {
        ID = 115;

        Text = "\"You ask me how I can be sure of Queen Titania's itinerary, my lads?\" growls Skarvench. \"You ask how I can whistle up a storm to scatter her escort fleet, then as quickly becalm her flagship in a bank of fog? And maybe you'll ask how I'll descend from the skies on a rope to whisk the pretty little package away before her soldiers even know what's what? Oh, what a bunch of scurvy doubting dogs you are, to be sure! There's one simple answer to all such cynical questions, and that's this: her wizard, William Wild, is my half-brother. He's in on the scheme, y'see.\"\n\nYou have heard enough. The whole world knows of the court wizard Dr Wild and the boundless trust placed in him by Queen Titania. If he plots betrayal, she is in real danger and not all her soldiers can save her.\n\nA floorboard creaks from further along the passage. You look around sharply. Someone is coming.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
        {
            Choices.push_back(Choice::Base("Hide in the sailmaster's cabin", 134));
            Choices.push_back(Choice::Base("Stand your ground", 191));
        }
    }

    int Continue(Character::Base &player) { return 153; }
};

class Story116 : public Story::Base
{
public:
    std::string PreText = "";

    bool HAS_FOOD = false;

    Story116()
    {
        ID = 116;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        HAS_FOOD = false;

        PreText = "Another day passes, and your voyage becomes an increasing ordeal as heat and fatigue take their toll. The sea sits all about you like a gleaming leaden plate; the sun turns the sky into a furnace of white haze. By night you shiver under the uncaring gaze of a million stars.";

        if (Character::HAS_FOOD(player, 0))
        {
            PreText += "\n\nYour supply of PROVISIONS DECREASED by 1.";

            Character::CONSUME_FOOD(player, 1);

            HAS_FOOD = true;
        }
        else
        {
            PreText += "\n\nYou've exhausted your supply of PROVISIONS.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player)
    {
        if (HAS_FOOD)
        {
            return 426;
        }
        else
        {
            return 155;
        }
    }
};

class Story117 : public Story::Base
{
public:
    std::string PreText = "";

    Story117()
    {
        ID = 117;

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        PreText = "You must offer the natives one of the following items; they won't accept anything else: a SWORD, a PISTOL, a MAGIC AMULET, a MAGIC WAND, a CRUCIFIX, a TOOLKIT, or all your MONEY.";

        auto count = 0;

        std::vector<Item::Type> bribe = {Item::Type::SWORD, Item::Type::PISTOL, Item::Type::MAGIC_WAND, Item::Type::MAGIC_AMULET, Item::Type::CRUCIFIX};

        for (auto i = 0; i < bribe.size(); i++)
        {
            count += Item::COUNT_TYPES(player.Items, bribe[i]);
        }

        if (count >= 1)
        {
            Choices.push_back(Choice::Base("Give them a gift", -117, bribe, 1));
        }
        else
        {
            PreText += "\n\nBut you are unable to part with such items.";
        }

        if (player.Money > 0)
        {
            Choices.push_back(Choice::Base("Give them ALL of Your MONEY", -117, Choice::Type::LOSE_MONEY, player.Money));
        }

        Choices.push_back(Choice::Base("You cannot or refuse to give anything: They start to turn nasty and you realize you had better run for it", 41));

        Text = PreText.c_str();
    }
};

class Event117 : public Story::Base
{
public:
    Event117()
    {
        Title = "Down Among the Dead Men: 117";

        ID = -117;

        Text = "They bring forward a shield woven of brightly coloured feathers and a wooden sword studded with shark's teeth which they offer in exchange.\n\nOakley gives a snort of disgust when he sees these. \"They're not worth a tenth of what we gave them!\"\n\n\"Maybe you shouldn't accept these gifts,\" cautions Blutz, catching your sleeve. \"The natives might get angry. Maybe it's just a token gesture and they don't really want to part with them.\"";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Take = {Item::FEATHER_SHIELD, Item::SHARKS_TOOTH_SWORD};

        Limit = 2;
    }

    int Continue(Character::Base &player) { return 98; }
};

class Story118 : public Story::Base
{
public:
    Story118()
    {
        ID = 118;

        Text = "You drag your boat up the beach under the blandly incurious gaze of the paradise-birds. Blutz gives an excited cry and points, saying, \"Look, above the treetops! It's a tower. A ruddy marble tower, mates.\"\n\nHe's right. In the declining golden light of the afternoon, you see a gleaming tower of polished stone. Since there are no creepers growing over it, the place is surely inhabited. But do you want to meet the inhabitant?";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_SKILL(player, Skill::Type::WILDERNESS_LORE))
        {
            Choices.push_back(Choice::Base("Head for the tower", 194));
            Choices.push_back(Choice::Base("Gather food and water", 232));
            Choices.push_back(Choice::Base("Put to sea immediately", 137));
        }
    }

    int Continue(Character::Base &player) { return 213; }
};

class Story119 : public Story::Base
{
public:
    std::string PreText = "";

    Story119()
    {
        ID = 119;

        Bye = "Ejada is done with you and you are free to return to the boat and sail away from here.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "You suggest that, instead of draining one person's entire soul so that he dies, she contents herself with a quarter of the life force taken from each of you. She considers this, then gives a short regal nod. \"I accept. Step forward , mortals.\"\n\nShe lays her knife against the chest of each of you in turn. A cold chill spreads through you as her magic leeches a part of your very soul.\n\nYou PERMANENTLY LOSE 1 Life Point and a skill of your choice.";

        player.MAX_LIFE_LIMIT--;

        Character::GAIN_LIFE(player, -1);

        Choices.clear();

        if (player.Skills.size() > 1)
        {
            if (player.Skills.size() < player.SKILLS_LIMIT)
            {
                player.SKILLS_LIMIT = player.Skills.size();
            }

            Choices.push_back(Choice::Base("Choose which skill to lose", 137, Choice::Type::LOSE_SKILLS, player.SKILLS_LIMIT - 1));
        }
        else
        {
            PreText += "\n\nYour entire soul has been drained.";

            player.Life = 0;
        }

        Text = PreText.c_str();
    }
};

class Story120 : public Story::Base
{
public:
    std::string PreText = "";

    Story120()
    {
        ID = 120;

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Type = Story::Type::NORMAL;

        PreText = "The days and nights become a flickering blur as you sink deeper into exhausted delirium. Arising from a fever, your eyes aching in your sockets, you behold a beautiful woman gliding across the dead calm of the sea. Her hair is the colour of honey and her skin is so white that it makes her lips blaze like rubies. Reaching you, she bends down and lifts you out of the boat as though you're weightless. Indeed, after your long ordeal your body has now become little more than skin stretched taught over bone. Borne higher and higher into the air, you realise with a curious detachment that you are not in a woman's arms at all, but in a kind of rope sling...\n\nNow you come properly awake, opening your eyes to find yourself on the deck of a ship. You are surrounded by sailors. One of them bends down and cradles your head, putting a cup of water to your lips.\n\n\"Where...? you croak feebly.\n\n\"On board the Jewel of Heaven,\" he replies. \"Now drink.\"\n\nThe water stings your shrivelled lips, runs like acid in your throat. After a few sips a wave of weakness enfolds you and you pass out.";

        if (player.Life < 3)
        {
            PreText += "\n\nYou never recover consciousness: you're beyond any help they can give.";

            Type = Story::Type::DOOM;
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 370; }
};

class Story121 : public Story::Base
{
public:
    Story121()
    {
        ID = 121;

        Text = "She swims well out of reach and remains silent while recovering her dignity. Then she rears up dolphin-like amidst the high waves and says: \"You were wise to set me free. If you had not, who can say what curse would have fallen on your heads? But now I will give you a proper reward for your courtesy.\"\n\nSwimming closer she catches the mooring rope and passing it over her shoulder, proceeds to tug your boat behind her as she swims rapidly southwards.\n\n\"A fine figurehead for our good ship Coffin Lid!\" declares Oakley, standing in the prow where the spray soaks his face. \"You'll agree to be our pallbearer too, I hope, madam, If the events turn against us?\"\n\n\"Sit down and be quiet, for God's sake,\" whines Blutz. \"Do you want her to drag us down into the depths?\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Let the mermaid take you south", 197));
        Choices.push_back(Choice::Base("Tell her to depart", 178));

        Controls = Story::Controls::STANDARD;
    }
};

class Story122 : public Story::Base
{
public:
    Story122()
    {
        ID = 122;

        Text = "The curse is immaterial. You are confident that your magical knowledge is enough to negate it -- at least so that you and your friends can escape from the ship. But Captain Mandrigard is another matter. Having suffered under the curse's power for so long, he is probably doomed forever now.\n\nAs you start to recite the charm, Grimes catches your sleeve and points up at the sails. \"We're running before an east wind,\" he says. \"No hurry in leaving the ship so long as can do it whenever we like. Let's leave it a day or so, when we'll be closer to home.\"\n\nBlutz rolls his eyes at this. \"Madness! Let's get away while we have the chance.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("[CHARMS] Neutralize the curse and escape right now", 160, Skill::Type::CHARMS));
        Choices.push_back(Choice::Base("Remain on board for the nonce, in line with Grimes's suggestion", 141));

        Controls = Story::Controls::STANDARD;
    }
};

class Story123 : public Story::Base
{
public:
    Story123()
    {
        ID = 123;

        Text = "The crab's huge claw descends from the sky to snap at you, but you dive nimbly over it in a forward roll and continue running towards the jollyboat without so much as breaking stride. The others are already aboard. You can hear their frantic shouts urging you on. As the crab rears and plunges you are almost flung off your feet, but the same surefootedness that has carried you across many a storm-tossed deck lets you keep your balance now. A last bound carries you clear of the \"shore\" and into the boat.\n\n\"Go!\" you yell. \"Work those oars as you've never worked 'em before, my hearties!\"";

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 161; }
};

class Story124 : public Story::Base
{
public:
    Story124()
    {
        ID = 124;

        Text = "\"An' what if I do have something under my raft?\" he counters darkly. \"Even a poor shipwrecked mariner's entitled to a bit o' shelter, ain't he, out here where the pickings are lean and there's precious little cover to keep a wight from shrivellin' up and blowing away in the wind?\"\n\nSeeing how you all stare at this outburst, he suddenly falls quiet and cracks his mad smile again, saying, \"But blow it, shipmates, why quarrel? Tomorrow there'll be no secrets between us, that I promise ye or my name's not Timmy Mortice.";

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 105; }
};

class Story125 : public Story::Base
{
public:
    Story125()
    {
        ID = 125;

        Text = "No rain falls. Soon your tongue is so parched that it clings to the roof of your mouth like flypaper. The slightest effort wearies you, and you spend most of your time lolling half in a faint, idly tilting the rudder or gazing out over the pitiless expanse of the ocean.\n\nYou LOSE 2 Life Points.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -2);
    }

    int Continue(Character::Base &player) { return 106; }
};

class Story126 : public Story::Base
{
public:
    Story126()
    {
        ID = 126;

        Text = "You are taken into the marble-floored audience hall of the fort, where the governor receives visitors. He proves to be a short dumpy man with a harried look about him, no doubt more suited to banquets and other frippery than to the harsh demands of royal security.\n\nAfter listening to what you have to say, he exchanges a few whispered words with his officials. Then, turning to you with a stern heavy-lidded expression, he says, \"No doubt you expect some reward for this tall tale of yours? You'll not get one -- not a penny. Do you think we are ready to panic at every wild rumour dredged up from the bottom of a wine-jug? Not a bit of it.\"\n\nWithout more ado you are seized by guards and thrown out into the street. \"You fools!\" cries Oakley, jumping to his feet. \"Don't you understand? The Queen's in danger!\"\n\n\"You're in danger of a flogging if you don't shove off, matey boy,\" snarls the captain of the guard as he closes the fortress gates.\n\nThe rest of you get up and brush the dirt of the gutter off your clothes. \"Well, so much for that,\" says Grimes. \"Now I say we should sail for Port Selenice without delay.\"";

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 145; }
};

class Story127 : public Story::Base
{
public:
    Story127()
    {
        ID = 127;

        Text = "You soon learn that the governor recently ordered preparations for a state visit by Queen Titania. Sitting in a harbour tavern with an old acquaintance of yours, Black Danny McClintock, you watch amazed as the scar-faced rogue orders a jug of spiced milk instead of his usual shot of strong rum. \"We've been warned off causing any affray, under the threat of Moses's Law on our bare backsides,\" he explains. \"I'm playing it safe by doing no drinking or gambling for the duration.\"\n\nYou nod, hiding a smile. Moses's Law is thirty-nine strokes of the birch, but what this pack of dockside villains fear more than the pain is the public humiliation. After strutting like bantam cocks around Leshand's byways for so long, they hate having to knuckle under to the law. Doubtless that's why you can see your old friend Snake-Eyes Johnson in the street just outside helping an old lady with her shopping basket -- and not even filching so much as an orange while he does it.\n\nThe others listen with interest when you meet up later to tell them what you've learned. \"This state visit,\" ponders Blutz. \"It must be someone pretty important to cause a clampdown like this.\"\n\nIf you are to have any hope of catching up with Skarvench you will have to move on soon. He would never show his face around Leshand, with so many murders to his name. But you also have a feeling it might be worth spending a little while digging out more rumours.";

        Choices.clear();
        Choices.push_back(Choice::Base("Stay for a while digging out rumours", 88));
        Choices.push_back(Choice::Base("Visit a chandler's to buy supplies", 12));
        Choices.push_back(Choice::Base("Look for someone who can identify unusual items", 31));
        Choices.push_back(Choice::Base("[ROGUERY] Apply a LETTER OF MARQUE", 409, Skill::Type::ROGUERY));
        Choices.push_back(Choice::Base("(Marathon) Pay a visit to Master Capstick", 69, Codeword::Type::MARATHON));
        Choices.push_back(Choice::Base("You have now completed all your business in Leshand", 107));

        Controls = Story::Controls::STANDARD;
    }
};

class Story128 : public Story::Base
{
public:
    Story128()
    {
        ID = 128;

        Text = "Pretending not to have noticed the three ruffians, you go up to the scholar and greet him like an old friend: \"Ah, here you are! I've been searching high and low. Captain Skarvench has been most concerned for your safety.\"\n\n\"Eh..?\" says the scholar, peering at you with large watery eyes. \"I don't know -- \" You hastily silence him with a poke between his ribs.\n\nThe ruffians are looking on nervously. \"Um, did you say Skarvench?\" says one of them at last, a sickly half-smile curdling on his rough features.\n\n\"Why, yes,\" you reply, turning as if noticing them for the first time. \"This gentleman is his new ship's surgeon. The captain's been waiting for him to arrive in Selenice. Have you fellows been looking after him? That's very gracious. Tell me your names -- the captain may wish to reward you when he hears about this.\"\n\nThere is the sound of three very audible gulps. \"Er... think nothin' of it,\" says one of the men, handing back the scholar's spectacles. \"We got to be goin', ain't we, lads?\" And they are out of the door in less time than it takes to drain a tot of rum.";

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 223; }
};

class Story129 : public Story::Base
{
public:
    Story129()
    {
        ID = 129;

        Image = "images/filler1-green.png";

        Text = "Which of these possessions will you use?";

        Choices.clear();
        Choices.push_back(Choice::Base("HORNPIPE", 243, {Item::HORNPIPE}));
        Choices.push_back(Choice::Base("MONKEY", 224, {Item::MONKEY}));
        Choices.push_back(Choice::Base("DRAGON RING", 262, {Item::DRAGON_RING}));
        Choices.push_back(Choice::Base("Give up and throw yourself on the giant's charity", 72));

        Controls = Story::Controls::STANDARD;
    }
};

class Story130 : public Story::Base
{
public:
    Story130()
    {
        ID = 130;

        Text = "The captain takes your LETTER OF MARQUE, scans it briefly, then regards you with his coldly disapproving gaze. \"This document is invalid. We have reports that you have been plundering Gloriannic ships, which disqualifies you from acting as a privateer on Her Majesty's behalf.";

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 111; }
};

class Story131 : public Story::Base
{
public:
    Story131()
    {
        ID = 131;

        Image = "images/boat-in-fog-green.png";

        Text = "You come on deck shortly before eight bells. The fog shrouds everything in a spectral pall. You look up at the rigging, which hangs like the shadow of a giant web. There is a rotting miasmal smell in the air, wafting from the swamps along the back of the bay. Blutz gives a rattling cough, mumbles something about yellow fever and wanting to be shot of this anchorage, and stumps below to get a cup of grog before turning in. You are left alone on the deck.\n\nGazing back towards the glow from the swamps, you hear the muffled sound of oars splashing far off in the darkness. A small boat appears, gradually taking solid form out of the fog, and in the light of the ship's lanterns you see a tall figure standing in the prow with two rowers hunched over the oars behind him. As the boat pulls alongside you have a clear view of the man -- tall and pale, with eyes of startling cobalt blue. His teeth flash in a smile as he hails you: \"Permission to come aboard?\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Give him permission to come onto your ship", 283));
        Choices.push_back(Choice::Base("Refuse", 302));

        Controls = Story::Controls::STANDARD;
    }
};

class Story132 : public Story::Base
{
public:
    Story132()
    {
        ID = 132;

        Text = "The Gloriannic ship goes rushing past, helpless in the grip of the storm. You catch a brief glimpse of tiny figures scurrying across her deck. Then a wave crashes down, obscuring all sight of her, and when you look again she is gone.\n\n\"God help the Rose if she's out in that,\" gasps Oakley, staring into the teeth of the hurricane.\n\nYou do not answer. It takes every ounce of your strength to hold the whipstaff and keep your own ship on an even keel. As the thunderclouds spit molten light into the darkness all around you, fracturing the heavens with their fury, you strike on implacably towards your goal.";

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 94; }
};

class Story133 : public Story::Base
{
public:
    Story133()
    {
        ID = 133;

        Text = "You duck into a forward roll just as the cannon belches forth its charge. The ball goes whizzing over your head, snapping a spar just where you were standing. You have the bad luck to be caught by a flying splinter of wood, but it only grazes your forehead.\n\nYou LOSE 1 Life Point.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -1);
    }

    int Continue(Character::Base &player) { return 171; }
};

class Story134 : public Story::Base
{
public:
    Story134()
    {
        ID = 134;

        Text = "You dart inside the cabin, pushing the door behind you and listening with bated breath as the heavy tread of boots advances along the passage and pauses just outside. Then the door starts to swing open...";

        Choices.clear();
        Choices.push_back(Choice::Base("Use [CHARMS]", 210, Skill::Type::CHARMS));
        Choices.push_back(Choice::Base("Use [ROGUERY]", 229, Skill::Type::ROGUERY));
        Choices.push_back(Choice::Base("You cannot avoid detection", 191));

        Controls = Story::Controls::STANDARD;
    }
};

class Story135 : public Story::Base
{
public:
    Story135()
    {
        ID = 135;

        Text = "Your tiny boat heads heads onward. By day you are seared by the sun; by night you are racked with chill. Salt spray chafes the sores on your skin, and the need to bail water constantly gives you no rest. Another two days crawl by, and you gradually give way to fever and exhaustion.\n\nYou LOSE 1 Life Point.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        Character::GAIN_LIFE(player, -1);

        if (player.Life > 0)
        {
            if (!Character::HAS_FOOD(player, 0))
            {
                if (Character::VERIFY_ITEMS(player, {Item::Type::MONKEY}))
                {
                    Choices.push_back(Choice::Base("Eat the MONKEY if you are heartless or desperate", 212, Choice::Type::LOSE_ITEMS, {Item::MONKEY}));
                    Choices.push_back(Choice::Base("Do not eat the monkey", 231));
                }
                else
                {
                    Choices.push_back(Choice::Base("You have nothing to eat", 231));
                }
            }
            else
            {
                Character::CONSUME_FOOD(player, 1);
            }
        }
    }

    int Continue(Character::Base &player) { return 212; }
};

class Story136 : public Story::Base
{
public:
    Story136()
    {
        ID = 136;

        Text = "\"Here's the question as I sees it,\" says Grimes. \"Do we try to make it all the way to Leshand, or do we strike southward first? I reckon we'd have a shorter hop to Pandanus Isle, and we could pick up provisions there.\"\n\n\"Or the natives could pick up provisions,\" says Oakley. \"Us.\"\n\nIt looked as if Blutz was about to go along with Grimes's suggestion, but at the mention of cannibals he looks nervously to the south. \"We were on that cursed ship a fair while, mates,\" he says. \"Surely Leshand can't be far off, if we stay bold.\"\n\n\"Bold!\" Oakley gives a croak of mocking laughter.\n\nThey can't decide amongst themselves. The decision is left to you.";

        Choices.clear();
        Choices.push_back(Choice::Base("Head south to the Smoking Islands", 156));
        Choices.push_back(Choice::Base("Steer straight ahead and hope to make it to Port Leshand without further mishap", 405));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORD(player, Codeword::Type::PECCANT))
        {
            Choices[1].Destination = 386;
        }
        else
        {
            Choices[1].Destination = 405;
        }
    }
};

class Story137 : public Story::Base
{
public:
    std::string PreText = "";

    bool HAS_FOOD = false;

    Story137()
    {
        ID = 137;

        Image = "images/filler3-green.png";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        HAS_FOOD = Character::HAS_FOOD(player, 0);

        PreText = "Swept onwards, your little craft starts to spring leaks.";

        if (Character::VERIFY_CODEWORD(player, Codeword::Type::FLOAT))
        {
            PreText += " However, there is no cause for alarm.";
        }
        else
        {
            PreText += " You gained the codeword DETRUDE.";

            Character::GET_CODEWORDS(player, {Codeword::Type::DETRUDE});
        }

        PreText += "\n\nThirst, hunger and the heat become your bitter foes. Petty quarrels break out as conditions worsen. Each man is nearing the end of his tether.\n\nYou LOSE 1 Life Point.";

        Character::GAIN_LIFE(player, -1);

        if (player.Life > 0)
        {
            if (!HAS_FOOD)
            {
                PreText += "\n\nYou've exhausted your supply of PROVISIONS.";
            }
            else
            {
                PreText += "\n\nYour supply of PROVISIONS DECREASED by 1.";

                Character::CONSUME_FOOD(player, 1);
            }
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player)
    {
        if (HAS_FOOD)
        {
            return 156;
        }
        else
        {
            return 175;
        }
    }
};

class Story138 : public Story::Base
{
public:
    Story138()
    {
        ID = 138;

        Text = "A strong breeze stretches your sails wide against the sky, driving you on towards your destiny. But you have no time to brood on what the future may hold; you have a ship to command. Seeing the way her prow cleaves the water, and the jaunty courage of your crew as they go about their chores, your heart brims with optimism. Soon Skarvench will see his last sunset in his life -- of that you feel sure.\n\nMore than a week goes by. On the ninth day, you stand on the deck watching the sun slide out of the sky. Long blazing beams of orange light turn the green waves to liquid gold. And then -- in the blink of an eye -- this idyllic scene is transformed. A purple murk rises from the western horizon, blotting out the afternoon sun behind thick thunderclouds. A cold gust blows in your face, setting the sails to a pensive fluttering like frightened birds. You know well the taste of that chill wind; it is the harbinger of the hurricane.\n\n\"This is but the twitch of the lion's tail compared to what will come,\" mutters Grimes. \"We'll have to put about.\" He calls to the crew: \"Strike the main topsail.\"\n\nYou turn. \"Belay that striking order. Lash it!\"\n\nOakley stares at you. \"Skipper, the hurricane'll tear us apart.\"\n\nThe first rain spits into your face, icily intense. \"'We're going in, hurricane or not. God is the master of the heavens and all the world -- but, by all that's holy, I'm the master of this ship!\"\n\nYou RECOVER 2 Life Points.";

        Choices.clear();
        Choices.push_back(Choice::Base("Use a THUNDERCLOUD FAN", 18, {Item::THUNDERCLOUD_FAN}));
        Choices.push_back(Choice::Base("[CHARMS] Use a MAGIC AMULET", 37, Skill::Type::CHARMS));
        Choices.push_back(Choice::Base("Use [SEAFARING]", 397, Skill::Type::SEAFARING));
        Choices.push_back(Choice::Base("Otherwise", 75));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, 2);
    }
};

class Story139 : public Story::Base
{
public:
    Story139()
    {
        ID = 139;

        Text = "Mulling over your extensive knowledge of myth and legend, you consider what the items might be. Obviously they are classical in style. Very old, then -- which suggests the possibility of powerful magic, since everyone knows that the sorcerers of ancient times knew many magical secrets that are now lost. On the basis of hopeful surmise, you finally identify the items as follows:\n\nThe DIAMOND would suffice to buy you a ship of your own but it has no magical properties, unless the effect of staggering wealth on men's greed can be accounted magical.\n\nThe CONCH-SHELL HORN reminds you of such an item which was said to be taken by the Trojans after the sack of Atlantis. It can be used to convey its owner to the secret harbour of Poseidon, god of the sea. This harbour is filled with treasures, but it is guarded by a locked gate which can only be opened by the note of a flute or pipe.\n\nThe THUNDERCLOUD FAN is surely sacred to the storm deity of far-off Cathay. If wielded carefully, it unleashes a hurricane which can be directed as one wishes.\n\nYou soon place the BRONZE HELMET as having belonged to a Spartan king. No doubt it confers skill at arms upon the wearer, since the Spartans were renowned for their martial prowess.\n\nAs for the DRAGON RING... you're not sure. It strikes a distant chord of memory, but nothing you can quite dredge to the surface. Handling it makes you feel distinctly uneasy, however.\n\nDo you wish to change the two items you're taking on the basis of this information?";

        Choices.clear();
        Choices.push_back(Choice::Base("Change the two items you are taking", 217, Choice::Type::TAKE, {Item::DIAMOND, Item::CONCH_SHELL_HORN, Item::THUNDERCLOUD_FAN, Item::BRONZE_HELMET, Item::DRAGON_RING}, 2));
        Choices.push_back(Choice::Base("Stick with what you have taken", 217));

        Controls = Story::Controls::STANDARD;
    }
};

class Story140 : public Story::Base
{
public:
    Story140()
    {
        ID = 140;

        Text = "\"Much maintenance,\" she replies in answer to your query. \"Furious storms could yet swamp your boat; icy rain will chill you; hunger will gnaw at your insides and thirst will wither your tongues --\"\n\n\"Is that all?\" says Oakley.\n\nShe looks hard at him. \"A cursed ship plies these waters. If you have nerves of iron and fear no fright under all of heaven, you might travel aboard her and safely be brought in sight of land.\"\n\n\"A cuh-cursed ship...\" stammers Blutz. \"What's the cuh-catch?\"\n\n\"You'd pay a high price for your passage,\" replies the mermaid. \"A sinister sacrifice is called for when you wish to disembark. But nothing,\" she stares at the hand grasping her long tresses, \"nothing you can't afford to part with.\"\n\nNervousness makes Blutz relax his grip. With a haughty twist, the mermaid pulls away from him.";

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 178; }
};

class Story141 : public Story::Base
{
public:
    Story141()
    {
        ID = 141;

        Text = "You return to the captain's cabin, where you find Mandrigard snoring, sprawled across a table full of gold coins. Oakley stands looking down at him with hands on hips, his expression an odd mixture of pity and loathing. \"One way to lift the curse,\" he says at last, \"might be to put an end to the wretch.\"\n\n\"Murder him?\" gasps Blutz. \"I don't hold with killing a man who's not standing on his hind legs. Anyway, you're only saying that so you can take his treasure.\"\n\n\"He's dead drunk,\" points out Grimes. \"We could take the treasure from under his nose without provoking so much as a murmur. He'd never miss a few choice bits, and what good is treasure to him if he can never spend it?\"\n\nAs usual the others look to you for authority.";

        Choices.clear();
        Choices.push_back(Choice::Base("Give the go-ahead to murder Mandrigard while he sleeps", 179));
        Choices.push_back(Choice::Base("Help yourself to just a few items of treasure", 198));
        Choices.push_back(Choice::Base("Go back up on deck", 217));

        Controls = Story::Controls::STANDARD;
    }
};

class Story142 : public Story::Base
{
public:
    std::string PreText = "";

    Story142()
    {
        ID = 142;

        Image = "images/filler3-green.png";

        Choices.clear();
        Choices.push_back(Choice::Base("[SEAFARING] Try swimming to safety", 180, Skill::Type::SEAFARING));
        Choices.push_back(Choice::Base("[CHARMS] Rely on a charm against drowning", 199, Skill::Type::CHARMS));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Type = Story::Type::NORMAL;

        PreText = "Huge eye-stalks rise from the water, swivelling to bring you under the scrutiny of the crab's ghastly black gaze. It's claw swings down at you like a yacht's boom, and it rears and twists in a furious effort to snatch you off its back. Realising that you will be torn in half instantly if you fall prey to the claws, you throw yourself flat and cling to the crab's shell for dear life. There is a great lurch, then sea water washes in to engulf you. The crab is diving into the depths -- and taking you along with it.";

        if (!Character::VERIFY_ANY_SKILLS(player, {Skill::Type::SEAFARING, Skill::Type::CHARMS}))
        {
            PreText += "\n\nThere is nothing you can do to save yourself. Your adventure ends right here.";

            player.Life = 0;
        }

        Text = PreText.c_str();
    }
};

class Story143 : public Story::Base
{
public:
    Story143()
    {
        ID = 143;

        Text = "Rising to your feet, you perform as elegant an imitation of a courtly bow as your uncouth background and the cramped conditions will allow. \"Of course, we had nearly forgotten our manners. Long privation can do that to the best of us --\"\n\n\"Yes, yes!\" says Mortice eagerly, gripping the side of your boat.\n\nOakley's brow furrows into a frown and he looks on the point of saying something, but not before you have completed your mock ritual with the words: \"Mister Mortice, you have my permission to come aboard our little vessel.\"\n\nInstantly there is a flutter of tattered rags and a soft thud as he lands beside you in a jollyboat. You are taken aback. He moved so fast! With a toothy smile, he says, \"You lot get some rest. I'll keep watch a while.";

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (!Character::VERIFY_ITEMS(player, {Item::Type::CRUCIFIX}) && !Character::VERIFY_SKILL(player, Skill::Type::CHARMS))
        {
            return 200;
        }
        else
        {
            return 181;
        }
    }
};

class Story144 : public Story::Base
{
public:
    Story144()
    {
        ID = 144;

        Text = "You hide out deep in the hinterland of the island, surviving off berries and fruit. Eventually you deem it safe to make your way back to the native village. Peering out from the sheltering foliage, you find that the Belle Dame has sailed off. The coast is clear.\n\n\"That fiend!\" rages Oakley. \"No doubt he's off to wreak more wickedness in the world. Are we really going to sit here sucking coconuts while he goes unpunished?\"\n\nYou all agree it is high time you pressed on with your journey. The natives are now too scared to repeat the offer of an escort; you're on your own.";

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 177; }
};

class Story145 : public Story::Base
{
public:
    Story145()
    {
        ID = 145;

        Text = "Experienced sailors like the four of you have no trouble working your passage to Port Selenice. You sign on aboard a caravel and for the next week or so your days are filled with the familiar routine of life at sea.\n\n\"Look at the sunset!\" calls Blutz across the deck one evening. He points to where long clouds like like mauve paint smears across a palette of gloriously mingled gold, scarlet, violet and grey. \"This is the life, eh, shipmates?\n\nGrimes looks up from trimming the topsails. \"I'll take no pleasure from any such sight,\" he says grimly, \"until I know that Skarvench no longer lives under the same sky as we.\"\n\nEventually you reach port, and the captain of the caravel PAYS you off with 5 doubloons. Taking up your packs, you stride down the gangplank and along the bustling quay.\n\nYou RECOVER 3 Life Points.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, 3);
        Character::GAIN_MONEY(player, 5);
    }

    int Continue(Character::Base &player) { return 165; }
};

class Story146 : public Story::Base
{
public:
    Story146()
    {
        ID = 146;

        Image = "images/ruffians-green.png";

        Text = "The innkeeper of The Hanged Man is a sour-faced man named Drood. You can see him at the bar polishing tankards with a filthy piece of rag. As you step up, he sets aside the tankard he's holding and gives you a long loury glare. \"Heard you were dead,\" he says. \"Seems the news hasn't reach you yet, though.\"\n\nYou ignore this. \"Skarvench been in?\" you ask.\n\n\"Not lately. Things are too hot for him in Leshand.\" Drood spits on the bar and starts wiping it.\n\nA beefy hand clamps on your shoulder and turns you around. Facing you are six burly ruffians. You vaguely recognise them as Skarvench's \"business associates\" -- men who act as his spies and assassins on shore.\n\nThere leader regards you with eyes like tiny beads of dull glass. \"Cap'n Skarvench is in Port Selenice takin' delivery of a new ship,\" he says, \"Why're you askin'?\"\n\n\"We're planning to meet him.\"\n\nYou start to move past the ruffians, then freeze as they draw knives. \"Tell you what,\" says the leader, \"you go straight to hell, and no doubt the cap'n will join you there when he's good and ready...\"\n\nIt's life or death.";

        Choices.clear();
        Choices.push_back(Choice::Base("Fight", 13));
        Choices.push_back(Choice::Base("Use [CUNNING]", 51, Skill::Type::CUNNING));
        Choices.push_back(Choice::Base("Use [AGILITY]", 32, Skill::Type::AGILITY));

        Controls = Story::Controls::STANDARD;
    }
};

class Story147 : public Story::Base
{
public:
    Story147()
    {
        ID = 147;

        Text = "Stepping up to the bar, you act as if you'd only just spotted the three ruffians. \"Toby Whipstaff!\" you say to the largest of them. \"Why, I haven't clapped eyes on you in a month o' Sundays! How blows the wind, Toby?\"\n\nHe greets you with a broad smile, forgetting his sport with the scholar. \"All's well. Last week we took a Sidonian galleon loaded with gold plate; pickings have rarely been richer.\"\n\nYou nod. \"And not just Sidonian pickings, I suppose, otherwise the governor wouldn't have set a price of a hundred doubloons on your head.\"\n\nHe fingers his neck nervously. \"Ah that must be the little business involving the Gloriannic merchantman a while back. I didn't expect them to make so much of it.\"\n\n\"You're too modest! Five sailors were killed, including the governor's godson.\"\n\nWhipstaff visibly pales. \"A hundred doubloons, eh? That much.\"\n\n\"Your brother's been posted for twice that. No doubt it was his expertise with the flensing-knife that attracted undue attention.\"\n\n\"My brother? But he's sailing for Leshand this very day. I must get to the docks!\" Tossing the spectacles on the bar, he races out with his two cronies close behind.";

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 223; }
};

class Story148 : public Story::Base
{
public:
    Story148()
    {
        ID = 148;

        Text = "He gives you a single large emerald -- one of his tears of mirth at your great gall. The dolphin and the shark convey you back, chatting to one another on the way. You cannot hear everything they are saying because of the splashing of the waves, but you gather they had their own ideas as to how you'd fare at Neptune's gate. \"One of them's the spitting image of that Ulysses,' you overhear the dolphin say. The shark snorts and replies, \"I'm more interested in the fat one. I like the look of him. I might hang around the shore tomorrow and see if he goes swimming.\n\nAt last you arrive at the beach near Selenice. Your adventure has taken the whole night. As the sun rises, the coracle sinks under the waves. Blutz gives a shudder and seeing this, you remark, \"Don't worry, Mister Blutz, you'll be all right so long as you don't go for a swim.\"\n\n\"Er, it's not that,\" he protests. \"I was just, er, a bit chilly. Come on, mates, let's go to the shipyard and spend our emerald!";

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 337; }
};

class Story149 : public Story::Base
{
public:
    Story149()
    {
        ID = 149;

        Text = "He examines the letter, then hands it back. \"All's in order,\" he says. His manner is far from friendly, but at least the expression of icy menace is gone from his eyes. He orders the marines to lower their weapons. You cannot help noticing that the marine sergeant keeps his pistol cocked, however. \"I will take delivery of Her Majesty's share of your plunder,\" says the captain curtly. \"This will save you the trouble of sailing to Leshand to hand it over.\"\n\nYou show him to the hold, where he makes an inventory of your treasure and then divides a sizeable pile from it -- nearly a quarter of all your spoils. \"You're levying a harsh tax,\" you say, pointing at the pile.\n\nFor the first time his face shows a smile. It is like a crack appearing on thin ice. \"You're mistaken. That pile is what you get to keep. We're taking all the rest.\"\n\nYou barely choke back a gasp. He means to take three-quarters of your treasure! You will barely have enough left to buy a decent ship.";

        Choices.clear();
        Choices.push_back(Choice::Base("Use [CUNNING]", 168, Skill::Type::CUNNING));
        Choices.push_back(Choice::Base("Allow him to take the Queen's share", 187));
        Choices.push_back(Choice::Base("Fight to keep what you have", 206));

        Controls = Story::Controls::STANDARD;
    }
};

class Story150 : public Story::Base
{
public:
    Story150()
    {
        ID = 150;

        Text = "You do not relish such grisly work, but there is no time for hesitation. Kneeling in the bottom of the pit, you raise the sharp stake and drive it deep into the corpse's chest. Instantly the mouth gapes open and there issues forth such a howl of cold hatred that it will haunt your dreams forevermore. The eyes blaze for an instant in their sockets, then darken in true death as a fountain of dry brown blood wells up around the wound.\n\nYou lurch to your feet, glad to feel your friends' hands at your shoulders. Gradually, under your horrified eyes, the corpses collapse and shrivel away to dust.\n\n\"Collect the treasure, shipmates,\" you say in a hoarse voice. \"And look sharp -- I'm keen to quit this place.\"\n\nThe moon has risen by the time all the loot is safely stowed aboard the LADY OF SHALOTT. Only then, with shaking hand do you broach a bottle of rum. Each man gulps his tot eagerly, anxious to rid himself of his memories of this ghastly evening.";

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 16; }
};

class Story151 : public Story::Base
{
public:
    Story151()
    {
        ID = 151;

        Text = "Clutching the talisman, you appeal to whatever ancient god or demon it depicts to use its power now. For a long instant nothing happens, and you fear that the talisman's magic has worn off with age, but then you see a black shadow spreading across the face of the moon. It has the outline of a bat's wing.\n\n\"The bat was the symbol of night in ancient times,\" says Grimes, his voice hushed in awe as the last moonlight vanishes like a shuttered lantern-beam and the world is plunged into starlit darkness.";

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 246; }
};

class Story152 : public Story::Base
{
public:
    std::string PreText = "";

    Story152()
    {
        ID = 152;

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "The basilisk cannon roars, hurling fire and hot iron towards you. You throw yourself to one side, but the blast still catches you.\n\nYou LOSE 5 Life Points.";

        Character::GAIN_LIFE(player, -5);

        if (player.Life > 0)
        {
            PreText += "\n\nYou cry out in terrible agony but manage to stagger towards your foe. \"You take a lot o' killing, I'll say that for ye,\" hisses Skarvench as he draws his sword. \"But now your luck's run out.\"";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 171; }
};

class Story153 : public Story::Base
{
public:
    Story153()
    {
        ID = 153;

        Text = "Reaching up, you take a firm grip on the bulkhead beam running across the ceiling of the passage. Then you swing yourself up until you are braced across the beam. A moment later you see the sailmaster's distinctive bald head appear below where you're hiding, but he does not look up. As he vanishes into his cabin, you drop silently to the floor and hurry up the companion-way to join your comrades.";

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 172; }
};

class Story154 : public Story::Base
{
public:
    Story154()
    {
        ID = 154;

        Text = "You row in towards the island, beaching your vessel on the deserted shore. Oakley gives a cry of delight as he spots a pineapple that has fallen from a tree at the top of the beach. Its juice stings his sun-cracked lips, but he chews ravenously at it all the same.\n\n\"Head's up,\" Grimes says tersely. \"We got company, shipmates.\"\n\nYou turn your head. A large group of Carab natives have emerged from the woods and are coming across the sand towards you. \"Welcoming party...\" you mutter under your breath, noticing the spears.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_CODEWORD(player, Codeword::Type::SCRIP))
        {
            Choices.push_back(Choice::Base("[MARKSMANSHIP] Attack using a PISTOL", 196));
            Choices.push_back(Choice::Base("Go hand-to-hand fighting", 215));
            Choices.push_back(Choice::Base("You prefer to parley", 272));
            Choices.push_back(Choice::Base("Put to sea before they reach you", 177));
        }
    }

    int Continue(Character::Base &player) { return 253; }
};

class Story155 : public Story::Base
{
public:
    std::string PreText = "";

    Story155()
    {
        ID = 155;

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Your limbs ache with the strain of rowing, like men who have been stretched on the rack. Slumping over the oars, you gaze feebly out across the merciless distance that still separates you from civilization. The water laps temptingly against the sides of your boat, but you know that it holds out a false promise: brine cannot slake a poor mariner's thirst, it can only drive him mad.\n\n";

        auto DAMAGE = -2;

        if (Character::VERIFY_SKILL(player, Skill::Type::SEAFARING))
        {
            PreText += "[SEAFARING] ";

            DAMAGE = -1;
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Point(s).";

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 426; }
};

class Story156 : public Story::Base
{
public:
    Story156()
    {
        ID = 156;

        Text = "The most westerly of the islands comes in sight. It is a large golden-shored jungle island with many welcoming coves. \"Others have put in here, when blown north off the main shipping route,\" Grimes recalls. \"The natives are said to be hospitable.\"\n\nYou stare into the west. Leshand is still two hundred leagues off, and it might be wise to re-provision before you undertake that long haul. And yet worry gnaws at your mind: \"Hospitable when faced with gifts and muskets and a sea-going vessel of ten cannon, perhaps. But how will they greet a handful of starving wretches in a ramshackle craft?\"\n\nIt's up to you.";

        Choices.clear();
        Choices.push_back(Choice::Base("Put in here", 154));
        Choices.push_back(Choice::Base("Sail on towards Port Leshand", 177));

        Controls = Story::Controls::STANDARD;
    }
};

class Story157 : public Story::Base
{
public:
    Story157()
    {
        ID = 157;

        Text = "Now you guess the truth. As daughter of the earth goddess, Ejada received unending strength and vitality as long as she remained in contact with the ground. Now she is like an uprooted flower wilting in the hot sunlight. \"Restore me to the earth,\" she begs, \"and all my treasures are yours.\"\n\n\"They are anyway.\" You learned never to trust a sorceress. Wedging her on a high cornice of the building, well clear of the soil that would regenerate her power, you go inside to explore. You soon find a hoard of magical treasures comprising a MAGIC WAND, a HEALING POTION, a SHIP IN A BOTTLE, and a BLACK KITE. The HEALING POTION can be drunk once at any time to restore your Life points to normal. The other items may or may not come in handy later.";

        Bye = "Returning to the beach, you quit Grimoire Island without further delay.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Take = {Item::MAGIC_WAND, Item::HEALING_POTION, Item::SHIP_IN_BOTTLE, Item::BLACK_KITE};

        Limit = 4;
    }

    int Continue(Character::Base &player) { return 137; }
};

class Story158 : public Story::Base
{
public:
    Story158()
    {
        ID = 158;

        Text = "Coconuts are often found drifting at sea. This is how coconut trees establish themselves on new islands, after all. They can float at sea for months and remain perfectly fresh, so there is no reason why this one should not be edible. You finally manage to convince Blutz that it has not bobbed up from the kingdom of the dead or any such nonsense, and he happily joins the rest of you in your meal.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 389; }
};

class Story159 : public Story::Base
{
public:
    Story159()
    {
        ID = 159;

        Text = "The mermaid splashes grey spume with her tail, writhing angrily in Blutz's grip and spitting like a snake. But she answers you none the less: \"Set your prow south if food and comfort are your aim, for the islands there more hospitable to land-dwellers than these storm-churned seas. Your present course westward will take you to a baleful rendezvous, and one you are unlikely to get away from in once piece.\"\n\n\"I don't like the sound of that,\" says Blutz. \"But tell us more about the isles to the south. Aren't there any dangers there?\"\n\n\"There is the witch Ejada,\" replies the mermaid. \"She seeks souls for her god, and such is her power that none can strike her down while her feet remain planted on solid earth --\"\n\nSuddenly flinging a handful of brine into Blutz's face, she pulls free of his grip, leaving only two or three coral-coloured hairs twined between his stubby fingers.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 178; }
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
auto story040 = Story040();
auto story041 = Story041();
auto story042 = Story042();
auto story043 = Story043();
auto story044 = Story044();
auto story045 = Story045();
auto story046 = Story046();
auto story047 = Story047();
auto story048 = Story048();
auto story049 = Story049();
auto story050 = Story050();
auto story051 = Story051();
auto story052 = Story052();
auto story053 = Story053();
auto story054 = Story054();
auto story055 = Story055();
auto story056 = Story056();
auto story057 = Story057();
auto story058 = Story058();
auto story059 = Story059();
auto event059 = Event059();
auto story060 = Story060();
auto story061 = Story061();
auto story062 = Story062();
auto story063 = Story063();
auto story064 = Story064();
auto story065 = Story065();
auto story066 = Story066();
auto story067 = Story067();
auto story068 = Story068();
auto story069 = Story069();
auto story070 = Story070();
auto story071 = Story071();
auto story072 = Story072();
auto story073 = Story073();
auto story074 = Story074();
auto story075 = Story075();
auto story076 = Story076();
auto story077 = Story077();
auto story078 = Story078();
auto story079 = Story079();
auto story080 = Story080();
auto story081 = Story081();
auto story082 = Story082();
auto story083 = Story083();
auto story084 = Story084();
auto story085 = Story085();
auto story086 = Story086();
auto story087 = Story087();
auto story088 = Story088();
auto story089 = Story089();
auto story090 = Story090();
auto story091 = Story091();
auto story092 = Story092();
auto story093 = Story093();
auto story094 = Story094();
auto story095 = Story095();
auto story096 = Story096();
auto story097 = Story097();
auto story098 = Story098();
auto story099 = Story099();
auto story100 = Story100();
auto story101 = Story101();
auto story102 = Story102();
auto story103 = Story103();
auto story104 = Story104();
auto story105 = Story105();
auto story106 = Story106();
auto story107 = Story107();
auto story108 = Story108();
auto story109 = Story109();
auto story110 = Story110();
auto story111 = Story111();
auto story112 = Story112();
auto story113 = Story113();
auto story114 = Story114();
auto story115 = Story115();
auto story116 = Story116();
auto story117 = Story117();
auto event117 = Event117();
auto story118 = Story118();
auto story119 = Story119();
auto story120 = Story120();
auto story121 = Story121();
auto story122 = Story122();
auto story123 = Story123();
auto story124 = Story124();
auto story125 = Story125();
auto story126 = Story126();
auto story127 = Story127();
auto story128 = Story128();
auto story129 = Story129();
auto story130 = Story130();
auto story131 = Story131();
auto story132 = Story132();
auto story133 = Story133();
auto story134 = Story134();
auto story135 = Story135();
auto story136 = Story136();
auto story137 = Story137();
auto story138 = Story138();
auto story139 = Story139();
auto story140 = Story140();
auto story141 = Story141();
auto story142 = Story142();
auto story143 = Story143();
auto story144 = Story144();
auto story145 = Story145();
auto story146 = Story146();
auto story147 = Story147();
auto story148 = Story148();
auto story149 = Story149();
auto story150 = Story150();
auto story151 = Story151();
auto story152 = Story152();
auto story153 = Story153();
auto story154 = Story154();
auto story155 = Story155();
auto story156 = Story156();
auto story157 = Story157();
auto story158 = Story158();
auto story159 = Story159();

void InitializeStories()
{
    Stories = {
        &event059, &event117,
        &prologue, &story001, &story002, &story003, &story004, &story005, &story006, &story007, &story008, &story009,
        &story010, &story011, &story012, &story013, &story014, &story015, &story016, &story017, &story018, &story019,
        &story020, &story021, &story022, &story023, &story024, &story025, &story026, &story027, &story028, &story029,
        &story030, &story031, &story032, &story033, &story034, &story035, &story036, &story037, &story038, &story039,
        &story040, &story041, &story042, &story043, &story044, &story045, &story046, &story047, &story048, &story049,
        &story050, &story051, &story052, &story053, &story054, &story055, &story056, &story057, &story058, &story059,
        &story060, &story061, &story062, &story063, &story064, &story065, &story066, &story067, &story068, &story069,
        &story070, &story071, &story072, &story073, &story074, &story075, &story076, &story077, &story078, &story079,
        &story080, &story081, &story082, &story083, &story084, &story085, &story086, &story087, &story088, &story089,
        &story090, &story091, &story092, &story093, &story094, &story095, &story096, &story097, &story098, &story099,
        &story100, &story101, &story102, &story103, &story104, &story105, &story106, &story107, &story108, &story109,
        &story110, &story111, &story112, &story113, &story114, &story115, &story116, &story117, &story118, &story119,
        &story120, &story121, &story122, &story123, &story124, &story125, &story126, &story127, &story128, &story129,
        &story130, &story131, &story132, &story133, &story134, &story135, &story136, &story137, &story138, &story139,
        &story140, &story141, &story142, &story143, &story144, &story145, &story146, &story147, &story148, &story149,
        &story150, &story151, &story152, &story153, &story154, &story155, &story156, &story157, &story158, &story159};
}

#endif