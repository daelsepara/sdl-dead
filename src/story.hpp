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
        TAKE,
        PAY_WITH,
        SELL
    };

    class Base
    {
    public:
        const char *Text = NULL;

        Choice::Type Type = Choice::Type::NORMAL;

        Skill::Type Skill = Skill::Type::NONE;

        std::vector<Item::Base> Items = std::vector<Item::Base>();

        Codeword::Type Codeword = Codeword::Type::NONE;

        int Value = 0;

        int Destination = -1;

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
    };
} // namespace Choice

namespace Story
{
    enum class Type
    {
        NORMAL = 0,
        GOOD,
        DOOM,
        PIRACY
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

    std::vector<Button> ExitControls(bool compact = false)
    {
        auto idx = 0;

        auto controls = std::vector<Button>();

        if (!compact)
        {
            controls.push_back(Button(0, "icons/up-arrow.png", 0, 1, 0, 1, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + border_space, Control::Type::SCROLL_UP));
            controls.push_back(Button(1, "icons/down-arrow.png", 0, 2, 0, 2, (1.0 - Margin) * SCREEN_WIDTH - arrow_size, texty + text_bounds - arrow_size - border_space, Control::Type::SCROLL_DOWN));

            idx = 2;
        }

        controls.push_back(Button(idx, "icons/exit.png", compact ? idx : idx - 1, idx, compact ? idx : idx - 1, idx, (1.0 - Margin) * SCREEN_WIDTH - buttonw, buttony, Control::Type::BACK));

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
        PreText = "Ejada responds with a cry of rage and sorcerous gesture. Immediately a hail of red-hot stones pour down out of the sky to pelt you as you flee. \"Craven mortals, \" she thunders. \"I gave you the chance to leave with honour, but you spurned my kindness. Now suffer the consequences.\"\n\n\"Kindness, she calls it?\" gasps Blutz as he struggles to keep up through the battering rain of stones. \"She's killing us with her kindness!\"\n\n";

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

    void Event(Character::Base &player)
    {
        if (!Character::VERIFY_SKILL(player, Skill::Type::CHARMS))
        {
            Character::GET_CODEWORDS(player, {Codeword::Type::DETRUDE});
        }
    }

    int Continue(Character::Base &player)
    {
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
        Choices.push_back(Choice::Base("You have completed all your business in Leshand", 107));

        Controls = Story::Controls::SHOP;
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

        if (Character::VERIFY_SKILL_ANY(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::RUSTY_SWORD, Item::Type::CLEAVER, Item::Type::SHARKS_TOOTH_SWORD}))
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

        Text = "A look of thunder flickers behind Skarvench's eye. \"Still alive, eh? Come and drink with your old cap'n!\" He waves the rum bottle as if inviting you to take it, but you'd sooner put your hand in a wolf's mouth.\n\nBlutz's blood is up at the sight of your hated foe. \"God rot your one eye, villain!\" he screams. \"I'd like to take that bottle and --\"\n\nThere is a crash of breaking wood and Blutz falls with a groan. Glancing to one side, you see he has been hit over the head with a stool. Curshaw stands there grinning, then puts his boot into the unconscious Blutz's ribs. He drops the broken leg of the stool beside him.\n\nOakley and Grimes stand face to face with the closing circle of Skarvench's men. You whirl to face the pirate captain himself. \"Enough, Skarvench; your quarrel's with me, not them.\"\n\nHe crows with laughter. \"Ah, that's a right noble sentiment and no mistake! See here, though: my quarrel's with all who'd try'n scupper my plans. I'm aimin' to bag me a queen, no less, an' then sell her to the highest bidder. So I'm goin' to have to do away with you, mate -- which I should've done long ago, but I guess my old heart's just too soft.\"\n\nHis hand goes to his belt. You realise he's reaching for a weapon, and your own fingers close instinctively on something on the table beside you. You raise it, and Skarvench gives a screech of laughter. You're holding only a CORKSCREW. He has a musket. \"I'll be the wealthiest man on the seven seas,\" he boasts. \"And he who would that wealth deny, down among the dead men let him lie!\"\n\nThere is a flash as he fires. Smoke fills the air and the musket-ball thuds into your chest. You feel an instant of searing pain, then everything goes black.";

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
        Choices.push_back(Choice::Base("[SWORDPLAY] Fight with a SWORD", 166, Choice::Type::SKILL_ANY, Skill::Type::SWORDPLAY, {Item::SWORD, Item::RUSTY_SWORD, Item::CLEAVER, Item::SHARKS_TOOTH_SWORD}));
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

        if (Character::HAS_SKILL(player, Skill::Type::ROGUERY) && Character::HAS_SKILL(player, Skill::Type::BRAWLING))
        {
            Choices.push_back(Choice::Base("You already have these skills", 9));
        }
        else if (Character::HAS_SKILL(player, Skill::Type::BRAWLING))
        {
            player.SKILLS_LIMIT = 3;

            Character::LOSE_SKILLS(player, {Skill::Type::BRAWLING});

            Choices.push_back(Choice::Base("Make room for [ROGUERY]", -59, Choice::Type::LOSE_SKILLS, 2));
        }
        else if (Character::HAS_SKILL(player, Skill::Type::ROGUERY))
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
        ID = -59;

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

        std::vector<Item::Base> bribe = {Item::SWORD, Item::PISTOL, Item::MAGIC_WAND, Item::MAGIC_AMULET, Item::SHIP_IN_BOTTLE, Item::CONCH_SHELL_HORN, Item::BAT_SHAPED_TALISMAN, Item::BLACK_KITE, Item::DIAMOND, Item::TOOLKIT, Item::HEALING_POTION, Item::BRONZE_HELMET, Item::CRUCIFIX, Item::DRAGON_RING};

        for (auto i = 0; i < bribe.size(); i++)
        {
            count += Item::COUNT_TYPES(player.Items, bribe[i].Type);
        }

        if (count >= 2)
        {
            Choices.push_back(Choice::Base("Part with two such items", 144, Choice::Type::BRIBE, bribe, 2));
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
        else
        {
            if (Character::VERIFY_SKILL_ANY(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::RUSTY_SWORD, Item::Type::CLEAVER, Item::Type::SHARKS_TOOTH_SWORD}))
            {
                PreText += "[SWORDPLAY] ";

                DAMAGE = -2;
            }

            if (Character::VERIFY_SKILL(player, Skill::Type::MARKSMANSHIP))
            {
                PreText += "[MARKSMANSHIP] ";

                DAMAGE = -2;
            }
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Point(s).";

        Text = PreText.c_str();

        player.TemporarySkills.clear();
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
            PreText += "[Item: FEATHER SHIELD] ";

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

        Text = "Most of the hands are just bare bone, but a couple still show traces of skin and sinew. One even wears a gold ring, though none of you cares to fish it out of the tank. \"I'm glad we haven't drunk from this,\" says Oakley quietly, closing the lid. \"No wonder the captain prefers wine. It could fair kill a bloke's thirst for fresh water, it could.\"\n\n\"Here's what did the job,\" announces Grimes, picking something up off the deck. He hands it to you: a long-bladed butcher's CLEAVER.\n\n\"I'm for leaving right now,\" declares Blutz, quaking with fear. But as he tries to climb back down the jolly boat moored alongside, he makes an ominous discovery. \"I can't get over the rail. It's as if some supernatural force is tugging me back!\"\n\nThe same applies to the rest of you. \"The ship is cursed,\" says Grimes. \"And now shipmates, we're cursed too.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("[SEAFARING] Make repairs to the boat", 103, Skill::Type::SEAFARING));
        Choices.push_back(Choice::Base("Use a TOOLKIT", 103, {Item::TOOLKIT}));
        Choices.push_back(Choice::Base("Use [CHARMS]", 122, Skill::Type::CHARMS));
        Choices.push_back(Choice::Base("Otherwise", 141));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Take = {Item::CLEAVER};

        Limit = 1;
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

        if (Character::VERIFY_SKILL_ANY(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::RUSTY_SWORD, Item::Type::CLEAVER, Item::Type::SHARKS_TOOTH_SWORD}) && Character::VERIFY_SKILL(player, Skill::Type::MARKSMANSHIP))
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

        std::vector<Item::Base> bribe = {Item::SWORD, Item::PISTOL, Item::MAGIC_WAND, Item::MAGIC_AMULET, Item::CRUCIFIX, Item::TOOLKIT};

        for (auto i = 0; i < bribe.size(); i++)
        {
            count += Item::COUNT_TYPES(player.Items, bribe[i].Type);
        }

        if (count >= 1)
        {
            Choices.push_back(Choice::Base("Give them a gift", -117, Choice::Type::BRIBE, bribe, 1));
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

        PreText = "The days and nights become a flickering blur as you sink deeper into exhausted delirium. Arising from a fever, your eyes aching in your sockets, you behold a beautiful woman gliding across the dead calm of the sea. Her hair is the colour of honey and her skin is so white that it makes her lips blaze like rubies. Reaching you, she bends down and lifts you out of the boat as though you're weightless. Indeed, after your long ordeal your body has now become little more than skin stretched taught over bone. Borne higher and higher into the air, you realise with a curious detachment that you are not in a woman's arms at all, but in a kind of rope sling...\n\nNow you come properly awake, opening your eyes to find yourself on the deck of a ship. You are surrounded by sailors. One of them bends down and cradles your head, putting a cup of water to your lips.\n\n\"Where...?\" you croak feebly.\n\n\"On board the Jewel of Heaven,\" he replies. \"Now drink.\"\n\nThe water stings your shrivelled lips, runs like acid in your throat. After a few sips a wave of weakness enfolds you and you pass out.";

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
        Choices.push_back(Choice::Base("You have completed all your business in Leshand", 107));

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
                    Choices.push_back(Choice::Base("Do not eat the MONKEY", 231));
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

        Text = "You hide out deep in the hinterland of the island, surviving off berries and fruit. Eventually you deem it safe to make your way back to the native village. Peering out from the sheltering foliage, you find that the Belle Dame has sailed off. The coast is clear.\n\n\"That fiend!\" rages Oakley. \"No doubt he's off to wreak more wickedness in the world. Are we really going to sit here sucking COCONUTs while he goes unpunished?\"\n\nYou all agree it is high time you pressed on with your journey. The natives are now too scared to repeat the offer of an escort; you're on your own.";

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

        Text = "Clutching the TALISMAN, you appeal to whatever ancient god or demon it depicts to use its power now. For a long instant nothing happens, and you fear that the TALISMAN's magic has worn off with age, but then you see a black shadow spreading across the face of the moon. It has the outline of a bat's wing.\n\n\"The bat was the symbol of night in ancient times,\" says Grimes, his voice hushed in awe as the last moonlight vanishes like a shuttered lantern-beam and the world is plunged into starlit darkness.";

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

        Image = "images/filler3-green.png";

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

        Image = "images/filler2-green.png";

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

        Image = "images/filler2-green.png";

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

        Image = "images/filler3-green.png";

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

        Text = "COCONUTs are often found drifting at sea. This is how COCONUT trees establish themselves on new islands, after all. They can float at sea for months and remain perfectly fresh, so there is no reason why this one should not be edible. You finally manage to convince Blutz that it has not bobbed up from the kingdom of the dead or any such nonsense, and he happily joins the rest of you in your meal.";

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

class Story160 : public Story::Base
{
public:
    Story160()
    {
        ID = 160;

        Text = "Settling into your jollyboat, you are not sorry to see the gloomy hulk of the LARNASSOS fade off into the darkness and drizzle. As for Captain Mandrigard -- will he ever find rest or an end to his curse? You wonder.\n\n\"Should have more sense than to offend a high priest, shouldn't he,\" says Oakley. \"Save your pity for ourselves mate; we're not through this yet.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Steer south from here, towards the Smoking Islands", 135));
        Choices.push_back(Choice::Base("Stay on your present course", 349));

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
            Choices[1].Destination = 349;
        }
    }
};

class Story161 : public Story::Base
{
public:
    Story161()
    {
        ID = 161;

        Text = "Gazing back, you see the hump of the great crab's shell as it rears up, threshing at the water with its claws in a frenzied search for the human prey that so narrowly escaped its clutches.\n\n\"I expect it's rather short-sighted,\" Blutz says. \"Obviously it wouldn't need sharp vision, seeing as how fish are so plentiful in these waters.\"\n\n\"Yes, but keep your voice down,\" hisses Oakley. \"No reason to suppose that it's deaf as well.\"\n\nLeaving the crab far in your wake, you decide which way to go next.";

        Choices.clear();
        Choices.push_back(Choice::Base("Steer westwards", 47));
        Choices.push_back(Choice::Base("Steer north towards the Smoking Islands", 66));

        Controls = Story::Controls::STANDARD;
    }
};

class Story162 : public Story::Base
{
public:
    Story162()
    {
        ID = 162;

        Text = "Mortice becomes livid with rage, hissing out a torrent of curses to freeze the blood. At last, when his anger runs out of words, he lapses into silence and merely glares at you with incandescent yellow eyes.\n\n\"Perhaps we should board his vessel, if it comes to that,\" suggests Grimes.\n\nOakley agrees. \"There could well be treasure in that long box there,\" he says. His eyes are locked on Mortice.\n\nAll of you stand tense, alert. Mortice couches on his raft like a wild beast at bay. As he sees Oakley place his foot on the side of the jollyboat, ready to spring over to the raft, he gives a guttural snarl and says, \"Try it. I'll rip yer gizzard out through yer backside and feed it to the fishes.\"\n\n\"Emphatically unwelcoming,\" you remark. \"If we persist in trying to board the raft I think we'll have a fight on our hands.\"\n\n\"A fight?\" says Oakley, looking back at you. \"He's just one old lubber.\" But all the same he stays poised there, waiting for you to say the word.";

        Choices.clear();
        Choices.push_back(Choice::Base("Attack Mortice with bare hands", 219));
        Choices.push_back(Choice::Base("[SWORDPLAY] Attack with a sword", 238, Choice::Type::SKILL_ANY, Skill::Type::SWORDPLAY, {Item::SWORD, Item::RUSTY_SWORD, Item::CLEAVER, Item::SHARKS_TOOTH_SWORD}));
        Choices.push_back(Choice::Base("[MARKSMANSHIP] Use a PISTOL", 257, Skill::Type::MARKSMANSHIP));
        Choices.push_back(Choice::Base("Cut the raft adrift", 276));

        Controls = Story::Controls::STANDARD;
    }
};

class Story163 : public Story::Base
{
public:
    std::string PreText = "";

    Story163()
    {
        ID = 163;

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "\"Let's face it,\" says Oakley a few days later, \"we don't know the first thing about foraging. We'll starve if we stay here.\"\n\nYou have to admit he is right. Unable to trap birds or animals, you are forced back on a meager diet of nuts. You cannot even be sure which are safe to eat, and stomach pains and retching gradually sap your resolve.\n\nYou LOSE 1 Life Point.";

        Character::GAIN_LIFE(player, -1);

        if (player.Life > 0)
        {
            PreText += "\n\n\"It's hopeless,\" says Grimes. \"We'd be better off going out to face Skarvench. At least we might get a quick clean death.\"\n\nKnowing Skarvench, you doubt that. But it is better to boldly confront your foe than starve to death like miserable dogs. You lead others back to the shore.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 87; }
};

class Story164 : public Story::Base
{
public:
    Story164()
    {
        ID = 164;

        Text = "Haunting moonlit street corners and smoky low-raftered taverns, you gradually piece together a tale of real terror. It seems El Draque was a Carpathian mercenary who arrived in the New World ten years ago and at once embarked on a spree of unrestrained piracy. Instantly recognizable by his filed teeth and acid blue eyes, he inspired such fear that most ships surrendered as soon as he raised his flag. The general consensus among everyone you speak to is that he slept by day in a box in the cargo hold of his ship, that he drank the blood of those he murdered, and that he was impervious to mortal injury.\n\nThere is one more thing. A month ago, taken unawares by a Gloriannic frigate, El Draque was caught and hanged at sea. His body was then flung overboard. The authorities were satisfied -- at least enough to pay out the bounty on his head to the frigate captain who caught him. But then, a week or so later, that same frigate captain was found dead in a harbour-front inn. His throat has been sliced from ear to ear, but the weird thing was there was that there was hardly a drop of blood.\n\nYou've heard enough to guess that the career of the notorious El Draque has not yet ended.";

        Choices.clear();
        Choices.push_back(Choice::Base("Find out more about Skarvench's activities", 278));
        Choices.push_back(Choice::Base("Ask around concerning the impending royal visit", 202));
        Choices.push_back(Choice::Base("Visit a chandler's to buy supplies", 12));
        Choices.push_back(Choice::Base("Look for someone who can identify unusual items", 31));
        Choices.push_back(Choice::Base("Apply for a LETTER OF MARQUE", 409));
        Choices.push_back(Choice::Base("(Marathon) Pay a visit to Master Capstick", 69, Codeword::Type::MARATHON));
        Choices.push_back(Choice::Base("You have completed all your business in Leshand", 107));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::ROGUERY))
        {
            Choices[4].Destination = 50;
        }
        else
        {
            Choices[4].Destination = 409;
        }
    }
};

class Story165 : public Story::Base
{
public:
    Story165()
    {
        ID = 165;

        Text = "Of all the ports in the Carab Sea, only Selenice -- 'the Pirates' Haven' -- would it be safe for a bloodthirsty cut-throat like Skarvench to show his face and openly spend his ill-gotten gold. Selenice has no allegiance to any nation. It is ruled by the common consent of buccaneers who live here -- the Brethren of the Coast, as they term themselves -- and it is buccaneers and their families who are the town's only citizens.\n\nCuriously, life here is not the lawless mayhem that outsiders imagine. The buccaneers of Selenice arrive here glutted with more than their share of violence and hardship. They want nothing more than to peacefully squander their loot on ale, women and dice. One rule that is stringently enforce above all others is an absolute ban on the use of weapons. Normal brawls can and do occur, for buccaneers are hard men filled with pride, and tempers can flare up easily when the rum flows freely. But any brawl is settled barehanded, since to draw a weapon in Selenice is to invite summary justice from the Brethren of the Coast. However you may have fared elsewhere under the laws of civilized kingdoms, you'd do well not to fall afoul of the Brethren.\n\nPassing a pedlar in the street outside the Thorny Knot tavern, Oakley glances across at you. \"Maybe we should do a spot of shopping, skipper?\"\n\n\"I'd rather do a spot of drinking,\" says Blutz, casting a longing eye at the tavern.";

        Choices.clear();
        Choices.push_back(Choice::Base("Buy something from the pedlar", 336));
        Choices.push_back(Choice::Base("Go into the tavern", 355));
        Choices.push_back(Choice::Base("Go off to see the local shipbuilder", 374));

        Controls = Story::Controls::STANDARD;
    }
};

class Story166 : public Story::Base
{
public:
    Story166()
    {
        ID = 166;

        Text = "Drawing your SWORD, you lunge towards the three bullies with a fierce yell. The terrified scholar throws himself flat and crawls under a table. The fight ranges back and forth across the room until suddenly you are seized from behind. Craning your neck, you see a throng of disapproving faces. A tall dour-faced man steps forward, saying, \"To draw a weapon in Selenice contravenes the code of the Brethren of the Coast. Fortunately we were able to stop you before anyone got seriously hurt.\"\n\nYour weapons are confiscated and any doubloons you were carrying are taken as fine. Then you are bustled out of the inn and sent packing.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::LOSE_ITEMS(player, {Item::Type::SWORD, Item::Type::PISTOL});

        player.LostMoney += player.Money;

        player.Money = 0;
    }

    int Continue(Character::Base &player) { return 374; }
};

class Story167 : public Story::Base
{
public:
    Story167()
    {
        ID = 167;

        Text = "He takes a mighty breath and blows it out at you, sending your coracle surging away on a huge billowing wave. You careen through the sea-soaked darkness, shivering for hours in the teeth of an unseasonal gale until finally you are cast up onto the beach outside Selenice.\n\nDawn tinges the sky with rose and gold. You sit up. There is no sign of the coracle. Waves lap the shoreline, seeming to whisper the secrets of the sea. You know those secrets well now;\n\nYou must make room for the [SEAFARING] skill.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (Character::HAS_SKILL(player, Skill::Type::SEAFARING))
        {
            Choices.push_back(Choice::Base("You already have [SEAFARING] skill", -167));
        }
        else
        {
            Choices.push_back(Choice::Base("Acquire [SEAFARING] skill", -167, Choice::Type::LOSE_SKILLS, player.SKILLS_LIMIT - 1));
        }
    }
};

class Event167 : public Story::Base
{
public:
    std::string PreText = "";

    Event167()
    {
        Title = "Down Among the Dead Men: 167";

        ID = -167;

        Choices.clear();
        Choices.push_back(Choice::Base("Use a CORKSCREW and a SHIP IN A BOTTLE", 261, {Item::CORKSCREW, Item::SHIP_IN_BOTTLE}));
        Choices.push_back(Choice::Base("Use a DEED OF OWNERSHIP", 318, {Item::DEED_OF_OWNERSHIP}));
        Choices.push_back(Choice::Base("Buy a ship with DIAMONDs", 299, {Item::DIAMOND}));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Type = Story::Type::NORMAL;

        PreText = "Returning to town ";

        if (!Character::HAS_SKILL(player, Skill::Type::SEAFARING))
        {
            player.Skills.push_back(Skill::SEAFARING);
        }

        if (!Character::VERIFY_ITEMS(player, {Item::Type::CORKSCREW, Item::Type::SHIP_IN_BOTTLE}) && !Character::VERIFY_ITEMS(player, {Item::Type::DEED_OF_OWNERSHIP}) && !Character::VERIFY_ITEMS(player, {Item::Type::DIAMOND}))
        {
            Type = Story::Type::DOOM;

            PreText += "you have exhausted all your options. You have no hope of catching up with Skarvench and this is the end.";
        }
        else
        {
            PreText += "you run through your remaining options.";
        }

        Text = PreText.c_str();
    }
};

class Story168 : public Story::Base
{
public:
    Story168()
    {
        ID = 168;

        Text = "After agreeing to the captain's demands, you direct your crew to carry the bulk of the treasure aboard the warship. At least, that's the way it seems. The truth is that only the top of each chest contains gold coins - the rest is filled with the salt that was left aboard the LADY OF SHALOTT by her last owner. A few groans, pleas, tears and offers of bribery help to make this charade convincing. The warship sails off towards Leshand and you turn your prow towards Selenice, hoping to be long gone before they discover you've tricked them.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 16; }
};

class Story169 : public Story::Base
{
public:
    Story169()
    {
        ID = 169;

        Text = "This is grim work, but you cannot afford the luxury of hesitation. The sunlight is all but gone. Kneeling quickly beside the open coffin, you raise the stake in both hands and plunge it down with all your strength into the corpse's breast. There is a terrible gasping sigh from the dead lips. It reminds you of autumn leaves scattering in a breeze. Then the body crumples like withered parchment.\n\nBlutz cries out. At the same moment, the sun is blotted out beyond the horizon and blue darkness rushes across the shore.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 347; }
};

class Story170 : public Story::Base
{
public:
    Story170()
    {
        ID = 170;

        Image = "images/filler1-green.png";

        Text = "Handing the kite to a sailor, you tell him to go up into the rigging and cast it towards the sky. \"What good will that do, skipper?\" asks Oakley as you watch the man climb.\n\n\"Call it a hunch, Mister Oakley. That witch Ejada wouldn't treasure anything so mundane as a kite unless it possessed some kind of magical power. Now we'll find out exactly what.\"\n\n\"It's a long shot,\" says Blutz, watching the Moon Dog dip lower in the night sky with silver sails gleaming.\n\nYou watch the sailor reach the top of the mast and throw the kite up into the heavens. Caught by some wind that the sails do not feel, it soars aloft higher and higher, seeming to grow larger as it goes so that it spreads like an inkblot against the moon.\n\n\"The dragon wing of night o'erspreads the world...\" breathes Grimes, his voice barely a whisper. And the last of the moonlight is blotted out, leaving only the gleam of ships' lanterns on the low bank of fog and the spangling of a million stars in the clear blackness above.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 246; }
};

class Story171 : public Story::Base
{
public:
    std::string PreText = "";

    Story171()
    {
        ID = 171;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "\"I don't know how you escaped death before,\" snarls Skarvench, \"but this time I'm going to make sure of the matter. I'll cut off your head and stick it on the bowsprit of my ship!\n\nHis sword comes slicing down in a lethal arc, barely missing your shoulder as you dodge desperately aside. It splinters a great chunk of wood out of the mast behind you. Skarvench only gives a bellow of insensate fury and draws it back for another swing. His is in a killing rage, and this fight will be every bit as dangerous as you had anticipated.\n\n";

        auto DAMAGE = -5;

        if (Character::VERIFY_SKILL(player, Skill::Type::BRAWLING))
        {
            DAMAGE = -3;

            PreText += "[BRAWLING] ";
        }
        else
        {
            if (Character::VERIFY_SKILL(player, Skill::Type::MARKSMANSHIP))
            {
                DAMAGE = -2;

                PreText += "[MARKSMANSHIP] ";
            }

            if (Character::VERIFY_SKILL_ANY(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::RUSTY_SWORD, Item::Type::CLEAVER, Item::Type::SHARKS_TOOTH_SWORD}))
            {
                DAMAGE = -2;

                PreText += "[SWORDPLAY] ";
            }
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Points.";

        Text = PreText.c_str();

        player.TemporarySkills.clear();
    }

    int Continue(Character::Base &player) { return 361; }
};

class Story172 : public Story::Base
{
public:
    Story172()
    {
        ID = 172;

        Image = "images/belle-dame-green.png";

        Text = "The others are waiting for you on deck. In the slanting rays of the setting moon you make out the furtive silhouettes of Grimes, tall and gaunt; Oakley, strong as a tar barrel; and fat little Blutz.\n\nThey have the jollyboat swung out over the side. Stealthily you lower it into the water, working in deep silence like four burglars intent on a night's business. From the below wafts the sound of a hornpipe and snatches of revelry as the crew sing sea shanties in the galley. Climbing down to the jollyboat, you shove off from the side and row with muffled oars away from the brooding bulk of Belle Dame. The moon slips below the western horizon, leaving the night studded with stars. There is no wind and the sea is as flat as a pane of glass. As the sounds of jollity fade into the distance, only the soft splash of your oars remains to disturb the eerie quiet.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::SEAFARING))
        {
            return 381;
        }
        if (Character::VERIFY_ITEMS(player, {Item::Type::BOOK_OF_CHARTS}))
        {
            return 381;
        }
        else if (Character::VERIFY_SKILL(player, Skill::Type::CHARMS))
        {
            return 399;
        }
        else if (Character::VERIFY_SKILL(player, Skill::Type::SPELLS))
        {
            return 416;
        }
        else
        {
            return 289;
        }
    }
};

class Story173 : public Story::Base
{
public:
    Story173()
    {
        ID = 173;

        Text = "You beach the jollyboat on a narrow strand of fine white sand backed by high cliffs. At the top of the cliffs you can clearly see the tall green boles of coconut trees. \"We're saved!\" cries Blutz, dancing an absurd little jig. \"We can eat those COCONUTs and even drink the milk if we can't find fresh water.\"\n\n\"But there's a problem,\" says Grimes, surveying the steep cliffs with a dour gaze. \"Who's going to climb up there and get them? You, Mister Blutz?\"";

        Choices.clear();
        Choices.push_back(Choice::Base("[AGILITY] Climb the cliffs alone", 192, Skill::Type::AGILITY));
        Choices.push_back(Choice::Base("Make your way along the beach in search of a way up", 211));
        Choices.push_back(Choice::Base("Try looking for food here on the beach", 230));
        Choices.push_back(Choice::Base("Put to sea and continue west towards the next island", 116));

        Controls = Story::Controls::STANDARD;
    }
};

class Story174 : public Story::Base
{
public:
    Story174()
    {
        ID = 174;

        Image = "images/filler4-green.png";

        Text = "Putting into a small cove, you moor the boat beside a large rock and then scramble ashore up a rocky moss-coated slope. Immediately you are confronted by lush jungle teeming with colour and life. Bright bulbous fruits dangle enticingly from the tree branches, yours for the taking. High up amid the emerald foliage, parrots in stained-glass hues peer down at you curiously, heads cocked to one side giving them a comical expression.\n\nYou and your friends have no difficulty in gathering food and fresh water. You RECEIVE two meals' worth of PROVISIONS for yourself.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::PROVISIONS, Item::PROVISIONS});
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORD(player, Codeword::Type::PROSPERO))
        {
            return 250;
        }
        else
        {
            return 269;
        }
    }
};

class Story175 : public Story::Base
{
public:
    std::string PreText = "";

    Story175()
    {
        ID = 175;

        Image = "images/filler3-green.png";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Your head swims; your limbs tremble with weakness. Looking into Oakley's face, you give a croak of bleak amusement. \"Saints alive, man, you look as though you'd been keelhauled!\"\n\nHe manages a wry half-smile- \"You think you do don't?\" Staggering over to slump beside you, he adds, \"We're not for long for this world now now, are we, mate?\"\n\nYou gaze into the west, almost all hope gone.\n\n";

        auto DAMAGE = -2;

        if (Character::VERIFY_SKILL(player, Skill::Type::SEAFARING))
        {
            DAMAGE = -1;

            PreText += "[SEAFARING] ";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Point(s).";

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 156; }
};

class Story176 : public Story::Base
{
public:
    Story176()
    {
        ID = 176;

        Text = "Resorting to an old trick of your trade, you toss a few pebbles to distract Ejada. She thinks she has heard you creeping away, and gives a wild laugh as she hurls her deathly bolts in the direction of the sound. Meanwhile you sneak into her tower and hastily feel your way along the wall until you come to a treasure chest. From this you pull a large DIAMOND and a BLACK KITE.\n\nEjada is still striding about the outside casting her spells into the undergrowth. \"Show yourself, coward!\" she screeches. \"This darkness won't last forever.\"\n\nIndeed it won't. Before the spell can wear off, you take your friends' arms and lead them back to the beach";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Take = {Item::DIAMOND, Item::BLACK_KITE};

        Limit = 2;
    }

    int Continue(Character::Base &player) { return 195; }
};

class Story177 : public Story::Base
{
public:
    Story177()
    {
        ID = 177;

        Text = "Taking stock of your situation leaves you in a grim mood. \"We're still more than two hundred leagues out from Port Leshand, and there are no islands along the route for us to restock our supplies. What we've got left for now is going to have to keep us going for at least ten days.\"\n\nOakley has another thought, equally sobering. Pointing at the timbers of your vessel - now warped by the constant sun and the battering of high waves -- he mutters: \"Ten days? We might not stay afloat that long.\"\n\n\"Maybe we shouldn't try to make it all the way to Leshand,\" suggests Blutz. \"We could head south from here towards the main shipping lanes. There's a good chance we'd be rescued by a friendly vessel.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Go south", 367));
        Choices.push_back(Choice::Base("Keep on heading west", 404));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORD(player, Codeword::Type::PECCANT))
        {
            Choices[4].Destination = 386;
        }
        else
        {
            Choices[4].Destination = 404;
        }
    }
};

class Story178 : public Story::Base
{
public:
    Story178()
    {
        ID = 178;

        Text = "The flash of coral-pink tail against the white-foamed grey of the sea, and then she is gone.\n\nThunder rattles the buttresses of heaven, and the sky gleams with distant lightning. Grimes squints into the west. \"Another storm rolling in ahead,\" he says. \"We're in for a battering.\"\n\n\"Let's head south!\" cries Blutz in sudden desperation. \"There are fewer storms, and we could pick up supplies among the islands, some of which are inhabited.\"\n\n\"Yes,\" grunts Oakley. \"By cannibals.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Give the order to steer south", 135));
        Choices.push_back(Choice::Base("Stay on your present westward course", 235));

        Controls = Story::Controls::STANDARD;
    }
};

class Story179 : public Story::Base
{
public:
    Story179()
    {
        ID = 179;

        Text = "It takes no special skill to murder a man while he sleeps, just a callous disregard for life. As Mandrigard's bright red blood drips down onto the floorboards and scattered jewels, you and your three companions stare at one another in the flickering lamplight. You all know the significance of your dreadful deed. Before you were merry rogues -- swashbucklers with one eye for plunder and one eye for thrills. Now you are rank villains.\n\nCramming your pockets with gold and gems worth a king's ransom you hurry away from the scene of the murder, up onto the deck where you at last feel a shudder of remorse.\n\nOakley recognizes the look on your face; he wears the same expression himself. Nodding, he cries, \"If this fresh breeze could only clean up my lungs of the stench of butchery - and this rain wash my hands of Mandrigard's blood!\"\n\n\"Forget it,\" grunts Grimes. \"The deed's done. \"We can never go back to being as we were before.\"\n\nYou gained the codeword CHANCERY.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_CODEWORDS(player, {Codeword::Type::CHANCERY});

        Choices.clear();

        Choices.push_back(Choice::Base("[CHARMS] Escape from the ship", 236, Skill::Type::CHARMS));

        if (player.Items.size() > 0)
        {
            Choices.push_back(Choice::Base("You think you have an item in your possession that might help", 255));
        }

        Choices.push_back(Choice::Base("Otherwise", 388));
    }
};

class Story180 : public Story::Base
{
public:
    Story180()
    {
        ID = 180;

        Image = "images/filler2-green.png";

        Text = "The giant crab drops down into the murk of the ocean, sinking as rapidly as a rock, and you are being carried along with it in the strong undertow. Luckily you were able to get a good lungful of air before you went under, and now you make full use of your remaining strength to strike powerfully up towards the glimmering pane of light that marks the surface.\n\nThe water drags at you like liquid lead. Your pulse thunders in your ears and your chest is burning with the need for air, but you struggle on with desperate strokes, clawing your way upwards until at last you break the surface.\n\nGasping for air, you are barely aware of your friends hauling you into the jollyboat. \"Come on, lads!\" you hear Oakley's voice yelling. \"Let's get clear before it resurfaces.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 161; }
};

class Story181 : public Story::Base
{
public:
    Story181()
    {
        ID = 181;

        Text = "You sleep soundly, waking at dawn to discover that Mortice and his raft have vanished. \"Good riddance to him, too,\" growls Oakley when you shake him awake with the news.\n\n\"He was a rather creepy character,\" Grimes concedes.\n\n\"Yes, but what about the food and water he had?\" Blutz reminds them. \"Now we're just as badly off as we were before.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 332; }
};

class Story182 : public Story::Base
{
public:
    std::string PreText = "";

    Story182()
    {
        ID = 182;

        Image = "images/filler3-green.png";

        Choices.clear();
        Choices.push_back(Choice::Base("Fight on", 220));
        Choices.push_back(Choice::Base("Surrender", 201));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Skarvench and his men are not the sort to be taken unawares. With savagery shining from their eager faces, they close to surround you. The clash of steel and the sharp crack of musket shots ring out, startling the constant jungle murmur into silence. Gunpowder smoke and the abattoir stink of blood clog your nostrils. You are heavily outnumbered, and the struggle grows ever more desperate.";

        if (Character::VERIFY_SKILL(player, Skill::Type::MARKSMANSHIP) && Character::VERIFY_SKILL_ANY(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::RUSTY_SWORD, Item::Type::CLEAVER, Item::Type::SHARKS_TOOTH_SWORD}))
        {
            Character::GAIN_LIFE(player, -5);

            PreText += "\n\n[SWORDPLAY] [MARKSMANSHIP] You LOSE 5 Life Points.";
        }
        else
        {
            PreText += "\n\nYou sell your lives dearly, but in an ultimately futile massacre.";

            player.Life = 0;
        }

        Text = PreText.c_str();
    }
};

class Story183 : public Story::Base
{
public:
    Story183()
    {
        ID = 183;

        Image = "images/filler4-green.png";

        Text = "\"El Draque?\" whispers an old sea salt whom you get talking to. \"Have ye not heard? He was captured and hanged at sea barely a month ago. By one account, his body was thrown overboard, but then swam three times around the ship before it sank.\"\n\nGrimes peers into the sailor's tankard. \"What are you drinking mate?\"\n\n\"Why, are you buying a round?\" says the fellow briskly.\n\n\"No,\" Grimes replies. \"I was just going to advise you to drink a bit less of it.\" As you leave the tavern, he says, \"Enough of these taproom tales. It's time we shipped out after Skarvench.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 392; }
};

class Story184 : public Story::Base
{
public:
    Story184()
    {
        ID = 184;

        Choices.clear();

        Controls = Story::Controls::NONE;
    }

    int Background(Character::Base &player)
    {
        if (player.Ship.Type != Ship::Type::NONE)
        {
            switch (player.Ship.Type)
            {
            case Ship::Type::LADY_OF_SHALOTT:
                player.Ship.Stars = 1;
                break;
            case Ship::Type::SHIVERED_TIMBER:
                player.Ship.Stars = 2;
                break;
            case Ship::Type::QUEENS_RANSOM:
                player.Ship.Stars = 3;
                break;
            case Ship::Type::FAERIE_QUEEN:
                player.Ship.Stars = 3;
                break;
            case Ship::Type::METEOR:
                player.Ship.Stars = 4;
                break;
            case Ship::Type::OCTAVIUS:
                player.Ship.Stars = 4;
                break;
            case Ship::Type::PROVIDENCE:
                player.Ship.Stars = 5;
                break;
            case Ship::Type::CALYPSO:
                player.Ship.Stars = 5;
                break;
            default:
                player.Ship.Stars = 1;
                break;
            }
        }
        else
        {
            player.Ship.Stars = 0;
        }

        return 320;
    }
};

class Story185 : public Story::Base
{
public:
    Story185()
    {
        ID = 185;

        Text = "One of the bullies gives a brutish sneer. \"You won't use that,\" he says with a scornful glance at the PISTOL. \"You'd be strung up for using a weapon in a brawl.\"\n\nYou shrug. \"True, I might get a rope around my neck -- if I'm caught. But it's a sure thing you won't attend the hanging. You'll be dead meat by then.\" He stares at you, licking his thick lips uncertainly. \"You wouldn't dare. Even if you kill me, my buddies here'll rip you apart.\"\n\nYou raise your PISTOL purposefully. It is aimed right between his eyes. \"Again, maybe that's so, but it won't do you any good with your brains splattered all over that wall.\"\n\nHis nerve breaks. With a snarl, he draws his cronies away and they slope off into the street. You tuck the PISTOL back inside your shirt before anyone sees you with it.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 223; }
};

class Story186 : public Story::Base
{
public:
    Story186()
    {
        ID = 186;

        Text = "Signing on a small crew, you set sail. A strong following wind allows you to make good headway, and you reach the island within a fortnight. As you coast in search of safe anchorage, Blutz points out a smaller isle that would be joined to the main island at low tide. Beyond it lies a bay where you drop anchor. Going ashore on the smaller island armed with shovels, you soon discover a boulder marked with crossed bones. \"Here's where we shall dig,\" you tell the others.\n\nYou labour on throughout the afternoon -- and hot work it is, with barely a breath of wind under a sun steaming through coastal marsh-haze. The western sky is already turning the colour of blood when there is the scrape of iron on wood. \"I've found a box!\" yells Blutz.\n\n\"And I another!\" Grimes calls out a moment later.\n\nScooping away the sand with your hands, you uncover a dozen large wooden crates. \"This is a goodly hoard!\" you say, breathless with sudden excitement. \"Break one open, lads, and let's see El Draque's treasure.\"\n\nGrimes smashes a hasp with his shovel. There is a creak as you wrench the lid up. A strong smell of tobacco and tar rises from the interior -- and something else: formaldehyde. A corpse lies there, resting on silver ingots, eyes staring sightlessly from a face which is colourless but untouched by decay. On the waxy flesh of its bare chest you see a tattoo with the legend \"Dethly is fear\".\n\n\"In God's holy name,\" breathes Oakley, \"what's this?\"\n\nBlutz grabs your arm. \"The sun's close to setting, skipper. For heaven's sake, let's forget the treasure and put to sea while we still can!\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Open the other boxes", 78));
        Choices.push_back(Choice::Base("Wait until nightfall", 347));
        Choices.push_back(Choice::Base("Return to the ship and set sail at once", 413));

        Controls = Story::Controls::STANDARD;
    }
};

class Story187 : public Story::Base
{
public:
    Story187()
    {
        ID = 187;

        Text = "The captain and his marines wait like hawks for your decision. You can sense Oakley and the others readying themselves for a fight, but you know that both honour and common-sense demand that you give in to these conditions.\n\n\"All right, tell your men to load the Queen's gold aboard your ship.\" After he has issued the order, your resentment is still smouldering. \"I expect you'd have preferred us to fight,\" you say. \"You enjoy killing pirates, I'll bet.\"\n\nHe shrugs as if your opinion means nothing. \"Killing pirates is my duty. But you're not a pirate are you? You're a privateer, and it's not my job to quarrel with privateers. Not so long as they pay the Queen her due.\"\n\nHe returns to his warship and turns in the direction of Leshand. \"Any orders? asks Grimes as you watch the warship sail away.\n\n\"Yes, Mister Grimes. Lay in a course for Selenice while we still have a few doubloons in our hold.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 301; }
};

class Story188 : public Story::Base
{
public:
    Story188()
    {
        ID = 188;

        Image = "images/filler2-green.png";

        Text = "This is grim work, but you cannot afford the luxury of hesitation. In moments the sunlight will be gone. Quickly dropping to your knees beside the open box, you raise the stake in both hands and plunge it down hard into the corpse's heart. A terrible gasping sigh escapes the dead lips, reminding you of the sound of autumn leaves scattering in a breeze. Then the body crumbles like ancient parchment.\n\nBlutz cries out. At the same moment, the sun is blotted out beyond the horizon and night rushes triumphantly across the world.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 347; }
};

class Story189 : public Story::Base
{
public:
    Story189()
    {
        ID = 189;

        Text = "You take out your POCKET-WATCH and glance at it. The glass was cracked when it stopped Skarvench's bullet, but it is still working. \"Midnight,\" you say, and close the case with a click.\n\nThere is a gasp from the sailors. One man almost falls out of the rigging in shock. Staring at the sky, they watch as an encroaching arc of darkness closes in front of the moon. \"'Tis doomsday!\" cries the bo'sun. \"First an unseasonal hurricane, then becalmed in fog, then flying ships - an' now a dragon devours the moon!\" A low moan of dread escapes the crew's lips.\n\nStand fast, you timid swabs!\" you thunder down at them from the poopdeck. \"Have you never seen an eclipse of the moon before?\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 246; }
};

class Story190 : public Story::Base
{
public:
    Story190()
    {
        ID = 190;

        Text = "The BRONZE HELMET fills your mind with the battle-lore of the Spartans. You now count as having [BRAWLING] and [SWORDPLAY] in addition to your usual skills. You sense the effect is only temporary - but it should last long enough to help you defeat Skarvench, or die trying.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        player.TemporarySkills.clear();

        if (!Character::HAS_SKILL(player, Skill::Type::BRAWLING))
        {
            player.TemporarySkills.push_back(Skill::BRAWLING);
        }

        if (!Character::HAS_SKILL(player, Skill::Type::SWORDPLAY))
        {
            player.TemporarySkills.push_back(Skill::SWORDPLAY);
        }
    }

    int Continue(Character::Base &player) { return 209; }
};

class Story191 : public Story::Base
{
public:
    std::string PreText = "";

    Story191()
    {
        ID = 191;

        Choices.clear();
        Choices.push_back(Choice::Base("[SWORDPLAY] Attack him before he can sound the alarm", 286, Choice::Type::SKILL_ANY, Skill::Type::SWORDPLAY, {Item::SWORD, Item::RUSTY_SWORD, Item::CLEAVER, Item::SHARKS_TOOTH_SWORD}));
        Choices.push_back(Choice::Base("[BRAWLING] Fight him", 248, Skill::Type::BRAWLING));
        Choices.push_back(Choice::Base("[CUNNING] Fall back", 305, Skill::Type::CUNNING));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Type = Story::Type::NORMAL;

        PreText = "You come face to face with the sailmaster. For a moment he stands there in simple perplexity. As an ordinary seaman you are not supposed to be in this part of the ship. \"What are you doing..?\" he starts to say.";

        if (!Character::VERIFY_ANY_SKILLS(player, {Skill::Type::BRAWLING, Skill::Type::CUNNING}) && !Character::VERIFY_SKILL_ANY(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::RUSTY_SWORD, Item::Type::CLEAVER, Item::Type::SHARKS_TOOTH_SWORD}))
        {
            Type = Story::Type::DOOM;

            PreText += "\n\nYou are helpless to prevent him from alerting the other pirates, who rush out of Skarvench's cabin to seize you. Your adventure ends before it even began.";
        }

        Text = PreText.c_str();
    }
};

class Story192 : public Story::Base
{
public:
    Story192()
    {
        ID = 192;

        Text = "With a dexterity that amazes your companions, you scale the cliffs like a monkey and have soon hurdle down enough COCONUTS to keep you all supplied for days. You scramble back down to the beach amid cheers of delight.\n\n\"Well done,\" says Oakley. He is smiling, but you notice he turns to cast a wary look along the shore. \"Now I suggest we lose no time loading these aboard and casting off. I've no wish to run into the natives hereabouts.\"\n\nYou GATHER 2 COCONUTs.";

        Choices.clear();
        Choices.push_back(Choice::Base("Leave this island and head west as Oakley suggests", 116));
        Choices.push_back(Choice::Base("Explore further", 211));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::COCONUT, Item::COCONUT});
    }
};

class Story193 : public Story::Base
{
public:
    Story193()
    {
        ID = 193;

        Image = "images/filler2-green.png";

        Text = "\"No, you're wrong,\" you tell Blutz. \"Look at most of the island. It's well covered in vegetation, right?\" That volcano has most likely been hissing and spitting for years, but if there had been any major eruption then the jungle wouldn't have grown up to that extent.\"\n\n\"All the same,\" says Grimes, \"let's not dally longer than we have to. The sight of those lava-covered slopes puts me in mind of Satan's brimstone fires!\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Go ashore", 174));
        Choices.push_back(Choice::Base("Row on westwards", 135));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::PROVISIONS, Item::PROVISIONS});
    }
};

class Story194 : public Story::Base
{
public:
    Story194()
    {
        ID = 194;

        Image = "images/plaza-green.png";

        Text = "Despite the thick jungle, you reach the tower quickly by following a stone pathway that leads through the undergrowth. You emerge into a wide grass-covered plaza and facing you is a white marble palace with a high tower. You move cautiously closer and Oakley runs his hand over the monumental carvings beside the entrance. They show a queen or priestess dispatching her enemies into luridly depicted hells.\n\n\"How was this stone brought here?\" Grimes wonders aloud. \"It's not local to the island, if I'm any judge.\"\n\n\"You're right,\" says a woman's voice. \"I brought it here by magic.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 251; }
};

class Story195 : public Story::Base
{
public:
    Story195()
    {
        ID = 195;

        Text = "It seems that the witch's exertions have weakened the spell she cast to bury your jollyboat. Or perhaps desperation lends you unprecedented strength. Whatever the reason, you manage to dig the boat out of the sand and drag it down to the water's edge. Piling in, you put out to sea at once.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 137; }
};

class Story196 : public Story::Base
{
public:
    Story196()
    {
        ID = 196;

        Text = "A shot rings out. A man falls dead. It is a sad, grim, brutally sudden scene which has been played out many times on the stage of life. As always, the onlookers stand for a moment, stunned, waiting for Death to withdraw into the wings so the action can resume.\n\nThe moment passes. The natives are not awed by your ability to kill at a distance -- they have seen firearms before, and know it is no miracle. There is an angry shout, and a thrown rock grazes your hand. The PISTOL is knocked to the ground. The natives stand watching you, ominously tense, torn between shock, grief and rage.";

        Choices.clear();
        Choices.push_back(Choice::Base("Get out while you can, abandoning your PISTOL", 177, Choice::Type::LOSE_ITEMS, {Item::PISTOL}));
        Choices.push_back(Choice::Base("Stand and fight", 215));

        Controls = Story::Controls::STANDARD;
    }
};

class Story197 : public Story::Base
{
public:
    std::string PreText = "";

    Story197()
    {
        ID = 197;

        Bye = "You see a fleece of white cloud, then a green-tinged hump of land comes in sight. \"Yonder is Red Skull Island,\" announces the mermaid. \"Here, food and water are yours for the taking -- subject only to those laws of ownership which pertain throughout the surface world.\" With a sly wink which raises belated misgivings in your mind, she releases the tow-rope and slides beneath the waves.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Gradually you leave behind the icy rain that has been your constant accompaniment throughout the journey. The southern waters into which the mermaid is now taking you are calmer, the weather warmer. Even so, the comfort only allows you time to regret your other deprivations - not the least of which is hunger.";

        Choices.clear();

        if (Character::VERIFY_ITEMS(player, {Item::Type::MONKEY}))
        {
            Choices.push_back(Choice::Base("Eat the MONKEY if you are heartless or desperate", 173, Choice::Type::LOSE_ITEMS, {Item::MONKEY}));
            Choices.push_back(Choice::Base("Do not eat the MONKEY (LOSE 2 Life Points)", 173, Choice::Type::LIFE, -2));
        }
        else
        {
            Character::GAIN_LIFE(player, -2);

            PreText += "\n\nYou LOSE 2 Life Points.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 173; }
};

class Story198 : public Story::Base
{
public:
    Story198()
    {
        ID = 198;

        Text = "You hesitate, hands hovering over the wealth of spilled treasure. You are spoiled for choice. Simple riches would buy you a ship of your own, in which you could track down and challenge the foul Skarvench. On the the other hand, you cannot help noticing some special items among the treasure -- artefacts whose real value lies not in their monetary worth, but in the magical power they might posses.\n\nMandrigard snores, stirring in his sleep. He might awaken at any moment. You must decide.";

        Choices.clear();
        Choices.push_back(Choice::Base("Take items of simple monetary value", 274));
        Choices.push_back(Choice::Base("Favour items which look to be magical in nature", 293));

        Controls = Story::Controls::STANDARD;
    }
};

class Story199 : public Story::Base
{
public:
    Story199()
    {
        ID = 199;

        Text = "\"Can you hear me, shipmate?\n\nBlutz's face swims out of a murky void. Your first thought is: what's he doing under the sea? The next moment you sit bold upright, convulsing as you cough sea-water out of your lungs.\n\n\"We thought you were lost,\" says Oakley in a voice filled with wonder. \"Since you went down with that giant crab, we hadn't seen a sign of you. That was almost an hour ago. Then you came bobbing up near the boat and we hauled you in.\"\n\n\"It's a miracle you aren't drowned,\" says Grimes.\n\nYou look down to see your fingers clutched tightly around your MAGIC AMULET. It is the one thing you managed to hold on to; all your possessions are gone. You cannot remember how, but you guess that your last act before losing consciousness must have been to work a charm against drowning. That explains why you are not dead. But Grimes is still partly right, because it's a miracle that the current carried you back to your friends.\n\nThe crab is long gone, but it is still not safe to stay in the vicinity.";

        Choices.clear();
        Choices.push_back(Choice::Base("Carry on westwards on your present course", 47));
        Choices.push_back(Choice::Base("Steer north in the hope of striking the island chain", 66));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        player.Items.clear();

        Character::GET_ITEMS(player, {Item::MAGIC_AMULET});
    }
};

class Story200 : public Story::Base
{
public:
    std::string PreText = "";

    Story200()
    {
        ID = 200;

        Image = "images/filler1-green.png";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "You LOSE 4 Life Points.";

        Character::GAIN_LIFE(player, -4);

        if (player.Life > 0)
        {
            PreText += "\n\nSleep gradually gives way to awareness. Daylight bathes you, slowly warming the chill from your bones. Suddenly your eyes snap open. You have slept long past dawn and the sun is now high in the sky.. You rise and stretch, feeling curiously giddy and drained of strength. The others are the same. You remark on how haggard they look, bloodshot eyes staring from bloodless faces. You all look and feel as though you had been drugged.\n\n\"Something's bitten me on the neck...\" growls Oakley, gingerly touching the wound and examining the sticky smear of blood on his fingers.\n\n\"Me too,\" says Blutz.\n\nAll four of you have been bitten -- a double puncture mare, deep and raw. No mosquito could have made those bites. And now you notice something else: the raft and its sinister occupant have vanished during the night.";
        }
        else
        {
            PreText += "\n\n\"You died some time during the night.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 332; }
};

class Story201 : public Story::Base
{
public:
    Story201()
    {
        ID = 201;

        Text = "Your arms are tied. \"Take 'em to the ship,\" growls Skarvench to a couple of his men. \"I'm going to stock up on fresh victuals while we're here.\" You are bundled into the boat. The men assigned to guard you are the rat-faced quartermaster, Curshaw, and Porbuck, the burly first mate. Skarvench himself stays behind with the rest of the shore party to collect supplies while you are rowed back, bound, towards the Belle Dame. You must do something.";

        Choices.clear();
        Choices.push_back(Choice::Base("[CUNNING]", 372, Skill::Type::CUNNING));
        Choices.push_back(Choice::Base("[ROGUERY]", 391, Skill::Type::ROGUERY));
        Choices.push_back(Choice::Base("[BRAWLING]", 408, Skill::Type::BRAWLING));
        Choices.push_back(Choice::Base("You have none of those", 240));

        Controls = Story::Controls::STANDARD;
    }
};

class Story202 : public Story::Base
{
public:
    Story202()
    {
        ID = 202;

        Text = "Queen Titania will be visiting a number of Gloriannic colonies in the New World and is scheduled to finish her tour at Port Tudor, where she will reside until after the hurricane season. Since the Sidonians would dearly love to capture her, security for the trip has been made watertight. She will be accompanied by Dr Wild, the court sorcerer, aboard her flagship the Rose, and escorted by Admiral Lord Calidor with a fleet of twelve galleons.\n\n\"The flotilla's security is as unassailable as the Queen's own virtue,\" opines one of your informants. From what you have learned you'd be inclined to agree. And yet... Skarvench clearly has some trick up his sleeve.";

        Choices.clear();
        Choices.push_back(Choice::Base("Try to find out exactly what Skarvench has been up to recently", 278));
        Choices.push_back(Choice::Base("You more interested in the notorious pirate El Draque", 164));
        Choices.push_back(Choice::Base("Visit a chandler's to buy supplies", 12));
        Choices.push_back(Choice::Base("Get your magical treasures identified", 31));
        Choices.push_back(Choice::Base("Apply for a LETTER OF MARQUE", 409));
        Choices.push_back(Choice::Base("(Marathon) Pay a visit to Master Capstick", 69, Codeword::Type::MARATHON));
        Choices.push_back(Choice::Base("You have completed all your business in Leshand", 107));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::ROGUERY))
        {
            Choices[4].Destination = 50;
        }
        else
        {
            Choices[4].Destination = 409;
        }
    }
};

class Story203 : public Story::Base
{
public:
    std::string PreText = "";

    Story203()
    {
        ID = 203;

        Choices.clear();
        Choices.push_back(Choice::Base("Use a CORKSCREW and a SHIP IN A BOTTLE", 261, {Item::CORKSCREW, Item::SHIP_IN_BOTTLE}));
        Choices.push_back(Choice::Base("Use a DEED OF OWNERSHIP", 318, {Item::DEED_OF_OWNERSHIP}));
        Choices.push_back(Choice::Base("Buy a ship with DIAMONDs", 299, {Item::DIAMOND}));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Type = Story::Type::NORMAL;

        PreText = "The shark and the dolphin slowly sink, taking the strange boat with them. The waters close over them like thin black oil, and in a last pearly glimmer they are gone. Moonrise flickers just below the horizon. The wind soughs, ruffling white flecks on the waves.\n\n\"We'd have fared ill if we'd ventured into Neptune's realm,\" says Oakley with conviction. \"Better that we obtain a ship by more normal means.\"\n\nYou return to spend the night in Selenice. The next day you take stock of your remaining options.";

        if (!Character::VERIFY_ITEMS(player, {Item::Type::CORKSCREW, Item::Type::SHIP_IN_BOTTLE}) && !Character::VERIFY_ITEMS(player, {Item::Type::DEED_OF_OWNERSHIP}) && !Character::VERIFY_ITEMS(player, {Item::Type::DIAMOND}))
        {
            Type = Story::Type::DOOM;

            PreText += "\n\nYour cause is hopeless and the adventure ends here.";
        }

        Text = PreText.c_str();
    }
};

class Story204 : public Story::Base
{
public:
    Story204()
    {
        ID = 204;

        Text = "With the help of your comrades you make short work of the three ruffians.\n\nYou LOSE 1 Life Point.";

        Bye = "You retrieve the spectacles from the hands of one of those unconscious ruffians and hand them back to their owner.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -1);
    }

    int Continue(Character::Base &player) { return 223; }
};

class Story205 : public Story::Base
{
public:
    Story205()
    {
        ID = 205;

        Image = "images/filler4-green.png";

        Text = "The harbour is vast. You cannot see the wharfs, blurred by the distance and darkness. As your coracle proceeds, you pass a multitude of ships lying at anchor all around you. A huge hulk looms up, shaped rather like a massive cradle. \"What about that one?\" says Blutz, awestruck. \"You could fit an entire menagerie insider her!\"\n\n\"Too ponderous,\" you decide.\n\nNext you pass a sleek high-powered galley with notches for fifty deck-cannon. \"There's a ship built for heroes,\" avers Grimes. \"Notice the fine beam of the prow, carved to resemble a mouth. What wisdom might she utter, if that mouth could talk!\"\n\n\"A well-designed vessel, to be sure,\" you admit, \"but look at the timbers of the bowsprit. They are so weathered with age that they might give way, to the mortal detriment of any poor soul standing below when they fell.\"\n\n\"What about that one?\" suggests Oakley, pointing further across the bay.\n\n\"Bah, she is entirely clad in sheets of iron! She would be slow to turn -- and, see, despite those long spars of metal she has no masts on her deck! No, we must look further.\"\n\n\"There's our ship!\" yells Blutz in sudden excitement.\n\nYou look to see a tall-masted vessel painted all in black except for the blue lacquer adoring her prow. Her figurehead is a muscular stature in oak wearing a winged helmet on his brow. His arm, upraised with staff held high, seems to point to a destiny brimming with glory. You nod, reading the name blazoned in gold on the ship's escutcheon. \"Yes, she's the one for us. The CALYPSO.\n\nClimbing aboard, you raise the sails and take her out of the harbour under the watchful gaze of the colossus. Still standing astride the harbour mouth, he calls after you as you sail off: \"Mind you don't earn my ire like that other rogue that sailed her before you!\"\n\nThere's no telling what he means by that, but your only thought is for your new vessel. She cuts through the waves with matchless grace and speed, steady as a surgeon's saw. You stand proudly behind the mast, revelling in every wave and gust of salty spray. As dawn breaks, you see the familiar outline of Selenice harbour ahead.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::TAKE_SHIP(player, Ship::CALYPSO);
    }

    int Continue(Character::Base &player) { return 184; }
};

class Story206 : public Story::Base
{
public:
    std::string PreText = "";

    Story206()
    {
        ID = 206;

        Image = "images/marine-sergeant-green.png";

        Bye = "You survive to see victory.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Your call to arms is cut short by the marine sergeant, who coshes you with the butt of his pistol before discharging it at Grimes. In seconds a frenzied battle breaks out all along the ship. The marines fight with iron discipline, hearts brimming with patriotic fervour, but your scurvy mob of pirates have a still stronger motivation: the glitter of gold awaits them if they win, a hangman's noose if they lose.\n\n";

        auto DAMAGE = -8;

        if (Character::VERIFY_SKILL(player, Skill::Type::BRAWLING))
        {
            DAMAGE = -3;

            PreText += "[BRAWLING] ";
        }
        else
        {
            if (Character::VERIFY_SKILL_ANY(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::RUSTY_SWORD, Item::Type::CLEAVER, Item::Type::SHARKS_TOOTH_SWORD}))
            {
                DAMAGE = -2;

                PreText += "[SWORDPLAY] ";
            }

            if (Character::VERIFY_SKILL(player, Skill::Type::MARKSMANSHIP))
            {
                DAMAGE = -2;

                PreText += "[MARKSMANSHIP] ";
            }
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Points.";

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 225; }
};

class Story207 : public Story::Base
{
public:
    Story207()
    {
        ID = 207;

        Text = "Your obsessive search for the iceberg drives you to plot a course far off the familiar shipping lanes. At first, awed by your reputation as a mariner, the crew toil on without complaint. But the days draw by with no sight of land or other ships, and then grumbling begins. Initially it takes the form of simple discontent -- a spluttered curse when a man bites into an apple from the deck-barrel and finds it sour, or a surly rejoinder when orders are given. Oakley, Grimes and Blutz do their best to keep discipline, but the sun beats down day after day until the pitch bubbles in the seams and the deck is too hot to walk on in bare feet. Water begins to run low, and it is then that the grumbling begins to veer towards outright mutiny.";

        Choices.clear();
        Choices.push_back(Choice::Base("Continue searching for the iceberg in spite of the crew's reluctance", 97));
        Choices.push_back(Choice::Base("Abandon the search and return to Selenice", 396));

        Controls = Story::Controls::STANDARD;
    }
};

class Story208 : public Story::Base
{
public:
    Story208()
    {
        ID = 208;

        Text = "There is not enough wind to bring you up to the fog bank before the Moon Dog. You watch her descend until she is hovering above the fog, sails shimmering with occult energy. Ropes are dropped down from her rail, and hazily you make out the shapes of men descending on these ropes like a dozen web-spinning spiders.\n\n\"Not enough breeze for the sails,\" you groan. \"I'd give half my life for a single gust of that hurricane now!\"\n\nThe fog envelops your bows. \"We'll have to heave to, skipper,\" cautions Grimes. \"We might run smack into the Rose in this pea-souper.\"\n\nYou are forced to agree. Tense minutes pass. Straining your ears, you think you can hear muffled shouts from far off: \"The Queen! They've got the Queen!\" and \"Where's their ship?\"\n\nAs suddenly as it arose, the fog disperses. The Rose looms close ahead of you, and now you can see figures milling across her deck in panic. You look up to see Skarvench's flying ship appear as a gaunt shadow across the moon for a moment; then it disappears into a rack of cloud.\n\nSoldiers come rowing out from the Rose and clamber aboard waiting for permission. You find yourselves staring down the barrels of thirty muskets. \"What is this?\" you demand angrily. \"We're not your enemies. We came to save the Queen!\"\n\nAdmiral Calidor stares at you like a hawk. He is obviously in a state of anguish but he struggles to control it as he says flatly, \"The Queen has been kidnapped by your accomplices. You're going to tell me where they've taken her.\"\n\n\"I don't know!\" you yell back at him. \"They weren't our accomplices. I told you, we're on your side!\"\n\nYour arms are seized by soldiers and you are bundled into a rowboat. \"These pirates are all the same,\" mutters Calidor to his sergeant of marines. \"Distasteful though it is, we'll have to put them to torture.\"\n\nYou are a long time dying on the rack in the bowels of Calidor's ship. But what makes your death all the more bitter is that you are being punished for the crimes of your arch enemy, the evil Captain Skarvench.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story209 : public Story::Base
{
public:
    Story209()
    {
        ID = 209;

        Text = "The deck is deserted. Barrels and splintered booms lie scattered all around. Fog drifts through the torn rigging, reminding you of the slow unfolding of undersea plants. \"What happened to the crew? The soldiers guarding the Queen?\" whispers Blutz as he climbs over the rail behind you.\n\n\"Perhaps stunned by the storm,\" you reply, also in a whisper. \"They must have taken a fearful battering. Also they must be expecting trouble...\"\n\nThe end of a rope lashes down onto the deck. You glance up. A vast grey shadow is hovering overhead, buoyed up by nothing but mist and moonlight: the Moon Dog.";

        Choices.clear();
        Choices.push_back(Choice::Base("[AGILITY] Climb up the rope to the Moon Dog", 228, Skill::Type::AGILITY));
        Choices.push_back(Choice::Base("[CUNNING] Try out a plan", 247, Skill::Type::CUNNING));
        Choices.push_back(Choice::Base("Wait at the bottom of the rope until your enemies come to you", 266));

        Controls = Story::Controls::STANDARD;
    }
};

class Story210 : public Story::Base
{
public:
    Story210()
    {
        ID = 210;

        Text = "Hurriedly clutching your MAGIC AMULET and uttering an all-purpose good luck charm, you wait to see what effect it will have. Just as the cabin door is swinging open, the person outside gives a gasp of annoyance. \"Damn it...\" he mutters to himself, and you hear the rustle of oilskins as he pats his pockets, \"left my pipe in the galley.\"\n\nOnly when he has retraced his steps, vanishing off along the passage in the direction of the galley, do you expel your breath in a relieved sigh. A hurried inspection of the cabin uncovers a few items that might prove useful: a TOOLKIT, a BOOK OF CHARTS, and a CRUCIFIX. The last of these brings a wry smile to your lips. A thousand CRUCIFIXes would not be enough to save the souls of the black-hearted villains in Skarvench's crew.\n\nJust as you are about to leave the cabin, there is a little shriek from the bunk and something small and grey launches itself onto your back. The shock sends your heart thudding like a hammer, but it is only the MONKEY that serves as the ship's mascot. Mister Chatter, the crew call him. He seems keen to go with you -- and small wonder, given the cruelty with which he is treated by most of the pirates. You could let him perch on your shoulder. Maybe he would bring you luck, at that. On the other hand, he'd be an extra mouth to feed aboard the rowing-boat, and if he does not keep quiet then he could bring the whole crew down on you.";

        Bye = "Then, having spent long enough about fetching supplies, you hasten to rejoin your friends.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Take = {Item::TOOLKIT, Item::BOOK_OF_CHARTS, Item::CRUCIFIX, Item::MONKEY};

        Limit = 4;
    }

    int Continue(Character::Base &player) { return 172; }
};

class Story211 : public Story::Base
{
public:
    Story211()
    {
        ID = 211;

        Text = "Some distance along the shore you find a ladder of knotted vines dangling down from the clifftop. \"Looks like there are natives,\" observes Oakley unnecessarily. \"Perhaps we'd be wiser to go back to the boat and shove off.\"\n\nYour experience has been that not all islanders are hostile. It usually depends on the way they have been treated by the outsiders they've met. On the other hand, there are some who are unabashed cannibals and will attack with provocation if they see the chance of an easy meal.";

        Choices.clear();
        Choices.push_back(Choice::Base("Climb the vines", 249));
        Choices.push_back(Choice::Base("Return to the jollyboat and continue on your voyage", 116));

        Controls = Story::Controls::STANDARD;
    }
};

class Story212 : public Story::Base
{
public:
    Story212()
    {
        ID = 212;

        Text = "Grimoire Island is a strangely idyllic-looking place, with wide white beaches fringed by gently swaying palm trees. A balmy breeze blows refreshingly from the east. Birds the colour of precious gems watch your approach without fear.\n\n\"It's eerie,\" decides Grimes. \"Almost too perfect.\"\n\n\"Like it's been tended,\" says Blutz. \"You know, like somebody's garden back home.\"\n\n\"A demon's garden, if the native stories are to be believed,\" chips in Oakley. All three, like you, are in a strange mood: both allured and uneasy.";

        Choices.clear();
        Choices.push_back(Choice::Base("Go ashore", 118));
        Choices.push_back(Choice::Base("Row on towards the next island", 137));

        Controls = Story::Controls::STANDARD;
    }
};

class Story213 : public Story::Base
{
public:
    Story213()
    {
        ID = 213;

        Text = "Blutz reaches out towards what looks like a bunch of oranges. You snatch them out of his pudgy hand. \"That's strychnine fruit,\" you warn him. \"It's deadly poisonous.\" Oakley shows you a handful of berries he's picked, but you shake your head. \"Those too. Everything here looks delicious, but most are poison.\"\n\n\"The tower, then,\" says Grimes. \"Whoever lives there might give us food.\"\n\nBlutz looks worried. \"But what kind of person lives on an island surrounded by poisonous plants?\"\n\nIt's a good question.";

        Choices.clear();
        Choices.push_back(Choice::Base("Go to the tower", 194));
        Choices.push_back(Choice::Base("Put to sea at once", 137));

        Controls = Story::Controls::STANDARD;
    }
};

class Story214 : public Story::Base
{
public:
    std::string PreText = "";

    Story214()
    {
        ID = 214;

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_SKILL(player, Skill::Type::SEAFARING))
        {
            PreText = "Decide what to do next.";

            Choices.push_back(Choice::Base("Go to the tower", 252));
            Choices.push_back(Choice::Base("Put to sea at once", 24));
        }
        else
        {
            PreText = "You easily outmanoeuvre the warship and soon leave her far behind.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 16; }
};

class Story215 : public Story::Base
{
public:
    std::string PreText = "";

    Story215()
    {
        ID = 215;

        Bye = "You fight your way down the beach and hastily put to sea under a hail of thrown pebbles.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "You are outnumbered, but you have an advantage they do not have. Warfare in their society is rarely fatal, intended only as a ritual show of strength. They lack the murderous instincts of you 'civilized' men.\n\n";

        auto DAMAGE = -6;

        if (Character::VERIFY_SKILL_ANY(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::RUSTY_SWORD, Item::Type::CLEAVER, Item::Type::SHARKS_TOOTH_SWORD}))
        {
            DAMAGE = -2;

            PreText += "[SWORDPLAY] ";
        }
        else if (Character::VERIFY_SKILL(player, Skill::Type::BRAWLING))
        {
            DAMAGE = -3;

            PreText += "[BRAWLING] ";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Points.";

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 177; }
};

class Story216 : public Story::Base
{
public:
    Story216()
    {
        ID = 216;

        Text = "Oakley's head rocks back as he feels the sting of your knuckles across his cheek, cutting off his song before he can launch into another gloom-ridden verse. \"Quiet!\" you tell him with a hiss of righteous anger in your voice.\n\nHe glares back at you, bloodshot eyes wide in a drained and haggard face. He is shaking with fear as much as fury. \"Quiet?\" he sobs. \"Why? We're all going to Davy Jones's mess hall tonight, and it's his pet sharks as will be making their meal of us.\"\n\n\"Nonsense!\" You take hold of his shoulders and stare him straight in the eye. \"Listen to me: none of us is going to die. We can all come through this in one piece if we pull together. The worst threat we have to face isn't the sea, or the weather, or hunger, or thirst. It's ourselves. Our fear. If we give in to panic, then we're lost.\"\n\nOakley nods. \"You're right.\" He helps you bail water taking turns throughout the night and the following day.\n\nYou LOSE 1 Life Point.";

        Bye = "You grow weaker, but at least you have inspired a glimmer of hope in your little band.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -1);
    }

    int Continue(Character::Base &player) { return 273; }
};

class Story217 : public Story::Base
{
public:
    Story217()
    {
        ID = 217;

        Text = "Salt spray spits across the deck in billows, driven by high winds that stretch the sails hard against the rigging. \"It's a wonder she ain't broke up long since!\" says Blutz.\n\n\"She's a cursed ship,\" declares Oakley matter-of-factly. \"Such vessels have an unnatural resilience.\"\n\nHours pass, during which you are blown further into the west. You snatch a short sleep in the shelter of a tarpaulin, preferring not to venture below decks again. At last Grimes shakes you from a feverish dream to say, \"It's time we quit this ship matey.\"\n\nYou agree.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_SKILL(player, Skill::Type::CHARMS))
        {
            if (player.Items.size() > 0)
            {
                Choices.push_back(Choice::Base("Use an item", 255));
            }

            Choices.push_back(Choice::Base("Continue", 388));
        }
    }

    int Continue(Character::Base &player) { return 236; }
};

class Story218 : public Story::Base
{
public:
    Story218()
    {
        ID = 218;

        Text = "With sudden inspiration you snatch off your own belt and twist the metal of the buckle to make a hook. For a line, you get everyone to unlace their boots and tie the strings together. Tied to the end of an oar, this gives you a makeshift fishing rod. You also trick up some nets by fixing socks onto the other oar.\n\n\"What do we use for bait?\" asks Grimes.\n\n\"Ah.\" You give a delicate cough. \"Well, to be blunt... whatever our stomachs couldn't use from the last meal we ate.\"\n\nTheir perplexed frowns gradually change to disgust as they catch on to what you mean. \"Ugh, you must be joking says Blutz.\n\n\"Believe me, it's the best bait.You weren't going to use it for anything else, were you, Mister Blutz?\"\n\nOakley snorts with outrage. \"You expect us to fish using our own excrement? Revolting! Do we want to live like animals, or die like decent men?\"\n\nThere is a long pause as the rest of you turn to look at Oakley. He thinks, then gives a grim nod and says, \"Right, let's get on with it, then\"\n\nHours later you have caught just three small fishes. A meagre enough meal for one person, let alone four. But at least now you won't starve tonight.";

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 256; }
};

class Story219 : public Story::Base
{
public:
    std::string PreText = "";

    Story219()
    {
        ID = 219;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Despite his shrivelled frame and spindly limbs, Mortice fights with the savagery and strength of a madman. Hissing, clawing, snapping at you with his long teeth, he struggles desperately to force you back off his raft.\n\nAt last you manage to succeed in pinning him, but not without injury.\n\n";

        auto DAMAGE = -3;

        if (Character::VERIFY_SKILL(player, Skill::Type::BRAWLING))
        {
            DAMAGE = -1;

            PreText += "[BRAWLING] ";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Point(s).";

        if (player.Life > 0)
        {
            PreText += "\n\nYou press all your weight down on Mortice's arms while he writhes in your grasp. Even now he continues his stream of invective, calling on the very devils of hell s though they were his blood brothers.\n\n\"He's as strong as an old serpent,\" says Grimes, holding on to Mortice's legs. It takes three of you to keep him down. While you do, Blutz looks around the raft.\n\nHe soon discovers something lashed to the bottom of the raft, under the water. It is a large pine box. He drags this up and opens it, and at once a mouldering miasma rises out which causes him to gag. \"It's full of old bones,\" he chokes.\n\nEven as these words leave Blutz's lips, there is a mournful unearthly sigh and suddenly the three of you are wrestling empty air. Mortice has vanished like a ghost.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 295; }
};

class Story220 : public Story::Base
{
public:
    Story220()
    {
        ID = 220;

        Text = "The natives scatter, filled with fear, as the battle rages up and down the beach inside their village. Men's lifeblood spurts into the sand. Lusty battle-cries are replaced now by ragged gasps and terse grunts of pain as each blow takes its toll.\n\nYou are face to face with Skarvench, locked in mortal combat. His breath is a putrid gust in your face. Both of you bear a dozen wounds; your blood runs down to mingle in the gore-soaked sand underfoot. \"I'm sending you to hell -- he snarls through gritted teeth. His cutlass stabs up, and you feel it grate through your ribs as you are impaled.\n\n\"Then we'll go there together!\" you cry, responding with a killing blow which he fails to see until it is too late. The pair of you sag to your knees, locked in a final embrace like old friends. And you are filled with a fierce exultation as, even while your own life ebbs away, you see the face of your foe go stiff and white in death...";

        Type = Story::Type::DOOM;

        Controls = Story::Controls::STANDARD;
    }
};

class Story221 : public Story::Base
{
public:
    Story221()
    {
        ID = 221;

        Image = "images/filler2-green.png";

        Text = "A few judicious rounds bought in a dockside tavern soon sets tongues wagging. \"Aye, I've heard it's the Queen herself who'll be visiting next month,\" ventures a longshoreman. \"That's why security's been tightened up. It stands to reason, don't it. The governor don't want nothing to go wrong while she's here, or he might end up begging on the streets instead of living in splendour up at the fort.\"\n\nUnfortunately other ears have overheard your enquiries. As you leave the tavern, footsteps ring on the cobbled street behind you. Before you have time to turn, you feel the unpleasantly familiar touch of cold steel against your neck. \"I'm sure the governor will want to know about the keen interest you're taking in Her Majesty's visit,\" says a voice full of honeyed menace. \"Why don't you come and have a chat with him about it?\"\n\n\"Why bother the man?\" you reply. \"He has a lot to deal with at the moment.\"\n\nThe knife prices your skin. \"I wouldn't like to have to press the point,\" says the voice in the darkness behind you.\n\nYou give a gulp. \"In that case, lead on.\"";

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 126; }
};

class Story222 : public Story::Base
{
public:
    std::string PreText = "";

    Story222()
    {
        ID = 222;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "By the onset of the second night, severe gales are driving freezing rain down onto your unprotected heads. You huddle together for warmth, but it is still impossible to snatch more than a few minutes of fitful sleep.\n\nYou LOSE 4 Life Points owing to the bitter cold.";

        Character::GAIN_LIFE(player, -4);

        if (player.Life > 0)
        {
            PreText += "\n\nOne person had to remain awake at all times to bail water, and in fact this unending task is not as bad as trying to rest -- at least the activity keeps you warm and helps prevent you from getting cramp.\n\nThe dawn is grey and cheerless, marked by a greyish pearl-like glimmer beyond the eastern clouds. It might as well be dusk for all the solace it gives you. The rain settles into a persistent, chilling drizzle. \"At least we have fresh drinking water,\" you say, collecting it in your cupped hands. \"As long as the rain keeps up we don't die of thirst.\"\n\n\"I almost wish we would,\" moans Blutz miserable. \"Another night like that and I'll be praying for death.\"\n\n\"Shut your whining mouth,\" snaps Oakley. \"It's going to get a lot worse than this.\"";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::SEAFARING))
        {
            return 259;
        }
        else
        {
            return 7;
        }
    }
};

class Story223 : public Story::Base
{
public:
    Story223()
    {
        ID = 223;

        Text = "Putting his spectacles back on, the scholar gratefully shakes you by the hand. \"This is a place for gentlemen of fortune, not gentlemen of letters,\" you tell him. \"I recommend you head on to a lawful port as soon as possible.\"\n\nHe shakes his head. \"But I've travelled all the way from Glorianne in search of someone: the wizard William Wild.\"\n\nYou nod. \"I've heard of him. Why should you expect to find here?\"\n\n\"I'm told he sailed for the colonies with Queen Titania. I left after they did, but my ship must have made better headway because it seems the Queen is still at sea and won't reach the colonies for several weeks.\"\n\n\"It's as you say, but you're mistaken if you think they'll put into port here. Selenice is not under Gloriannic rule.\"\n\nHe flutters his hands impatiently. \"I know that. But it occurs to me that Dr Wild's half-brother, a man called Skarvench, might know where he's bound.\"\n\nThe others have come over to join you. \"So Skarvench is half-brother to the Queen's wizard!\" says Oakley with a whistle. \"No doubt such news portends mischief.\"\n\n\"Why do you want to find Wild?\" Blutz asks the scholar.\n\n\"He paid me to do some astronomical calculations for him. He wanted to know when a certain eclipse of the moon would occur, as apparently he had certain plans which would be disrupted if the eclipse happened to early. Well, I gave him the results, but after he sailed I double-checked my calculations and it turns out I made an error. I told Dr Wild the eclipse would be at two o'clock on midsummer night, but in fact it will be slightly earlier, at midnight.\"\n\nAssuring the scholar that you will deliver his message personally, you escort him to the harbour and put him aboard a ship bound for Glorianne.\n\nYou gained the codeword HORAL.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_CODEWORDS(player, {Codeword::Type::HORAL});
    }

    int Continue(Character::Base &player) { return 374; }
};

class Story224 : public Story::Base
{
public:
    Story224()
    {
        ID = 224;

        Image = "images/filler1-green.png";

        Text = "He said no man can use the key. Pointing to the lock in the middle of the chain, you try to make the MONKEY understand what you want it to do -- but to no avail. \"Go on, you little fleabag!\" you yell in exasperation, but its only reaction to this is to give itself a cursory scratch and go on squatting there on the edge of the coracle, blinking at you.\n\n\"Begging your pardon, skipper,\" says Blutz, \"but you can't order a MONKEY about like you would an ordinary seaman. You've got to talk more gentle, like.\"\n\n\"Gentle?\" you say, amazed.\n\n\"Aye,\" Blutz nods. \"It's a thing skippers know nothing about. Let me try.\" He turns to the MONKEY, \"Now then, Mister Chatter, be a good bloke and unlock the harbour chain so your shipmates can sail through.\"\n\nAnd blow you down if this doesn't do the trick. The MONKEY clambers along the chain and you hear the click of a key as its paws turn an invisible object in the lock. The chain falls aside and the MONKEY comes scurrying back, shrieking gleefully.\n\n\"Imagine if captains had to take such a tone with their crew,\" you mutter. \"A ship's deck would be as blooming genteel as a church!\"\n\n\"Don't worry, skipper,\" says Grimes as the coracle glides into the harbour. \"It might work a treat with MONKEYs, but sailors will always need a bit of yelling at.\"";

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 205; }
};

class Story225 : public Story::Base
{
public:
    Story225()
    {
        ID = 225;

        Text = "The surviving marines are rounded up and bound. Grimes is all for going aboard the ship and user her as your new vessel. Blutz soon points out the drawback in this idea: \"We'd be hunted down by the entire Gloriannic navy! That's going to make it rather hard to save the Gloriannic Queen, isn't it?\"\n\n\"The Queen be hanged!\" cries one of the crew. \"We've got treasure, and now that we've seized a warship it'll be easy to keep our coffers filled. I'm for a life of solid piracy. Forget revenge, abandon honour -- let rum and gold be our goals!\"\n\nDo you consent to this?";

        Choices.clear();
        Choices.push_back(Choice::Base("No! You still envisage yourself as the Queen's saviour and Skarvench's nemesis. Cut the warship adrift and sail the LADY OF SHALLOT back to Selenice", 16));
        Choices.push_back(Choice::Base("Yes! Forget about Skarvench", -225));

        Controls = Story::Controls::STANDARD;
    }
};

class Event225 : public Story::Base
{
public:
    Event225()
    {
        ID = -225;

        Text = "Your adventure ends here.\n\nYou forget about your quest for revenge on Skarvench.\n\nYou have chosen a life of piracy, abandoning honour.\n\nRum and gold are your only goals now.";

        Type = Story::Type::PIRACY;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story226 : public Story::Base
{
public:
    Story226()
    {
        ID = 226;

        Text = "Dropping to your knees, you draw a circle around you in the sand and usher your shipmates to stand within it. Then, holding forth the focus of your protection, you begin to recite: \"They return at evening, and swords are in their lips, but let them growl and wander up and down for their blood; they shall not be satisfied. Though a host should encamp against me, my heart shall not fear; when they come upon me to eat up my flesh they shall stumble and fall. For I will sing of power. Yea, in my refuge I will sing aloud in the morning..!\"\n\nAll through the night your ordeal continues. Your voice grows hoarse, and whenever you quaver in your chant one of the vampires lunges forward, trying to snatch you out of the circle. But at long last, just when all hope seems lost, a flicker of grey light trembles on the eastern horizon.\n\n\"The dawn!\" shouts Blutz. \"Thank God!\"\n\nThe vampires gnash their fangs and turn like a pack of dogs, skulking back towards their coffins. \"aye, it's sunrise and we must retreat,\" says El Draque in a voice of icy anger. \"But do not rifle my treasure by day, for he that does will suffer my curse. My vengeance will reach out for him beyond the grave.\"\n\nWit that, he drops back into the hole. When you venture over, emboldened by the spreading daylight, yo see the corpses all back in their boxes. Now you must decide how much you fear his parting threat.";

        Choices.clear();
        Choices.push_back(Choice::Base("Take the silver ingots that the corpses are lying on", 16, Choice::Type::GET_CODEWORD, Codeword::Type::MALEFIC));
        Choices.push_back(Choice::Base("Leave it alone", 396));

        Controls = Story::Controls::STANDARD;
    }
};

class Story227 : public Story::Base
{
public:
    Story227()
    {
        ID = 227;

        Text = "Your poor ship has taken all the damage she can stand. Listing hard over, her prow begins to sink beneath the waves. \"Man the lifeboats!\" shouts Oakley. \"Abandon ship!\"\n\nGrimes takes your arm. \"Skipper, all's lost now. There's nothing left for us but to save ourselves.\"\n\nYou hesitate. Honour demands that a captain go down with his ship, but that is not what roots you to the spot. Instead it is your bitter disappointment at failing to scupper your foe. Who knows what wickedness he will now wreak, and you are powerless to stop him.\n\nWhether or not you flee the sinking ship...";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story228 : public Story::Base
{
public:
    Story228()
    {
        ID = 228;

        Text = "Taking hold of the rope, you pull yourself up. Mist surrounds you, dampening your clothes. There is an eerie chill here, suspended in a miasmic white void. The moon shimmers above as though seen in a stagnant pond. The shouts of your men echo leadenly up through the gloom.\n\nThe rope stirs. You look up to see a shape descending out of the moonlit vapour towards you. It is Skarvench, hanging like a great black spider on its web. Let him come. You will show him that this is no mere fly he has to face.";

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 323; }
};

class Story229 : public Story::Base
{
public:
    Story229()
    {
        ID = 229;

        Image = "images/filler2-green.png";

        Text = "You know well that the art of concealment rests on distracting the attention. Even as the door starts to swing open, you reach across and unlatch the cabin porthole. Then, scattering a few maps and charts onto the floor from the table where they were lying, you take cover in a heap of oilskins behind the door.\n\nNot a moment too soon. The bald stocky figure of the sailmaster stands in the doorway, lantern in his hand. Seeing the open porthole he gives a growl of annoyance and rushes to close it, worried that salt spray could damage his precious navigation charts. Then he gathers up some papers, puts them under his arm, and crosses to Skarvench's cabin.\n\nYou emerge from your hiding place and peek across the passage. The door of Skarvench's cabin stands ajar, and you can hear him going over the charts with the sailmaster. Now is your chance. Seeing a TOOLKIT beside the door, you take it: your rowing-boat may very well need repairs. There is no time to look for other items. You sneak back along the passage and up on deck.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::TOOLKIT});
    }

    int Continue(Character::Base &player) { return 172; }
};

class Story230 : public Story::Base
{
public:
    Story230()
    {
        ID = 230;

        Text = "You find only a couple of small crabs which between them amount to barely more than a mouthful. Blutz gazes at them hungrily, flabby jowls sagging in dismay. \"Not worth dividing them up,\" he groans. \"Who's going to be the lucky one, then?\"\n\nAs usual, the others instinctively look to you for leadership. Your own stomach is growling as much as anyone's.";

        Choices.clear();
        Choices.push_back(Choice::Base("Award yourself the crabs", 268));
        Choices.push_back(Choice::Base("You can let one of the others have them", 287));

        Controls = Story::Controls::STANDARD;
    }
};

class Story231 : public Story::Base
{
public:
    std::string PreText = "";

    Story231()
    {
        ID = 231;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Your skin is loose on your bones and your tongue feels like a wad of burnt cotton. The urge to drink seawater is almost unbearable now. Your only respite from consciousness is not sleep, but dream-haunted delirium.\n\n";

        auto DAMAGE = -2;

        if (Character::VERIFY_SKILL(player, Skill::Type::SEAFARING))
        {
            DAMAGE = -1;

            PreText += "[SEAFARING] ";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Point(s).";

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 212; }
};

class Story232 : public Story::Base
{
public:
    Story232()
    {
        ID = 232;

        Text = "You gorge yourselves on ripe fruits and tasty nuts -- only to suffer severe stomach cramps just minutes later. Oakley rushes down the beach and gulps sea water until he vomits. The rest of you follow suit, but you are left dizzy and weak.\n\n\"Something must have been poisonous,\" groans Blutz. \"Maybe we ought to go to the tower. There might be someone there who'll give us food.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Go to the tower", 194));
        Choices.push_back(Choice::Base("Leave the island now", 137));

        Controls = Story::Controls::STANDARD;
    }
};

class Story233 : public Story::Base
{
public:
    Story233()
    {
        ID = 233;

        Text = "The four of you crouch down in the weird boat. No sooner have you settled yourselves than the two great fish slap the waters with their tails, drawing you out to sea. Darkness and frothy waves churn past. With spray in your eyes, the moon looks like a whirlpool in the firmament and their is no way to tell how far you've travelled when, at last, the boat drifts to a halt. You see that you are close to the entrance of a massive harbour. A long golden chain is stretched across the harbour mouth to block the vessels from entering or leaving.\n\nThe moon emerges from behind a cloud, flooding the scene in its timeless white glow. You give a gasp, for now you see that you had taken to be the pillars of the harbour gate are actually colossal legs stretching up far into the night sky. Craning your neck, you see the massive outline of a giant's shoulders against the moon-grazed clouds.\n\nThe giant stoops, showing a smile as wide as a galleon's beam in his face of smooth dark marble. \"Four wayfarers,\" he says in the tone of one who has noticed four curious insects under his nose. \"Mortals. What brings you to Neptune's gate?\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Say you seek a ship", 34));
        Choices.push_back(Choice::Base("Ask for his help in your quest", 53));
        Choices.push_back(Choice::Base("Tell him you want to return home", 72));

        Controls = Story::Controls::STANDARD;
    }
};

class Story234 : public Story::Base
{
public:
    Story234()
    {
        ID = 234;

        Text = "\"Quick,\" you say to Oakley over your shoulder, \"push me over and make like you're giving me a kick. And make it look convincing.\" He is taken aback at first, but then he catches on to your plan. As you feel him shove you from behind, you fling yourself down to sprawl in the sand. \"Ouch\" you grunt as you feel the toe of his boot. \"Not that convincing!\"\n\n\"We've caught this scurvy wretch,\" Oakley tells the natives with the help of sign-language.\n\nThe chief must have learned a few words off sailors who stopped here. \"Kill,\" he says. \"Burn alive over fire.\"\n\nOakley hesitates. \"Er...\"\n\n\"Oh yes. Er, the prisoner will be taken to Queen Titania, the, er, chief of Glorianne. Get it? She'll decide the proper punishment.\"\n\nThe natives are still keen to seize you, but Oakley keeps them off with warnings of dire reprisals if Queen Titania's wishes are not carried out.";

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 272; }
};

class Story235 : public Story::Base
{
public:
    Story235()
    {
        ID = 235;

        Text = "The storm rolls over you, tossing your jollyboat halfway to the clouds with each wave. The sea becomes thick with icy froth. The sky is a flickering lantern -- one moment blue-white and bright as daybreak, then blacker than the underworld in the thunderous space between lightning flashes.\n\nWretchedly sick, weak with exhaustion and hunger, the four of you struggle to keep the little craft from submerging. Oakley sings wildly into the sheets of rain as he bails water with cupped hands:\n\n\"Oh, the Coffin Lid heaves to and fro,\ntossed by storms and gales,\nWhat's that thunder now I hear:\nfour hearts thudding full o' fear?\nOr Death's bone fingers drawing near\nand banging in the nails?\"\n\nGrimes and Blutz both look to be near the end of their tether. Oakley's gallows song is not helping their nerves. Nor yours, for that matter.";

        Choices.clear();
        Choices.push_back(Choice::Base("Shut Oakley up and risk provoking a fight", 216));
        Choices.push_back(Choice::Base("Do nothing and let morale drain away entirely", 254));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORD(player, Codeword::Type::DETRUDE))
        {
            Character::REMOVE_CODEWORD(player, Codeword::Type::DETRUDE);

            Character::GET_CODEWORDS(player, {Codeword::Type::PECCANT});
        }
    }
};

class Story236 : public Story::Base
{
public:
    Story236()
    {
        ID = 236;

        Image = "images/filler3-green.png";

        Text = "Holding firm to your mystic AMULET, you pronounce the words of a blessing.\n\n\"Hey, it worked!\" exclaims Blutz, clambering cumbrously over the rail.\"Look, we're not trapped by the curse anymore.\"\n\nYou nod, allowing yourself a slight smile of self congratulation. \"Don't dawdle, though. The effect of the charm won't last forever.\"\n\nLowering yourselves down to the water, you get back into the jollyboat tethered there and row hastily away through the chopping waves. Behind you, the Larnassos fades until she is no more than a wavering patch of shadow, and then is swallowed entirely by the darkness. \"Good riddance!\" spits Grimes.";

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 136; }
};

class Story237 : public Story::Base
{
public:
    Story237()
    {
        ID = 237;

        Text = "\"Well, Mister Chatter,\" says Oakley, settling the little MONKEY on his knee and producing a pocket-knife, \"it's been an honour to sail with 'ee, but your shipmates are going to ask a favour of you now, and it's that most noble sacrifice a bloke can make.\"\n\nRich red sunset glints on the blade, and in a stroke the dead is done. \"Poor little beggar!\" sighs Blutz.\n\n\"Better than poor us, matey,\" says Oakley as he carves you each a hunk of meat. \"Four starving sailors cramped into a jollyboat leaves precious room for sentiment.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Eat the MONKEY", 256));
        Choices.push_back(Choice::Base("Do not eat the MONKEY (LOSE 1 Life Point)", 256, Choice::Type::LIFE, -1));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::LOSE_ITEMS(player, {Item::Type::MONKEY});
    }
};

class Story238 : public Story::Base
{
public:
    Story238()
    {
        ID = 238;

        Image = "images/vampire-green.png";

        Text = "Raising your sword, you leap aboard the raft. You intended only to warn Mortice, but instead of backing off he gives a murderous snarl and runs straight onto the sword, impaling himself through the heart. You look away quickly with a grimace of dismay. Still gripping the blade, you glance back at the others and start to say, \"There wasn't anything I could do. He just --\"\n\n\"Look out!\" Blutz screeches in warning, pointing past you. \"He's not dead!\"\n\nYour eyes jerk back to Mortice, who you now see to your horror is still moving. Twitching galvanically, he grins a blood-rimmed smile and coughs gore, then starts to pull himself along the sword blade towards you.";

        Choices.clear();
        Choices.push_back(Choice::Base("Flee back to the boat, letting go of your SWORD", 276, Choice::Type::LOSE_ITEMS, {Item::SWORD}));
        Choices.push_back(Choice::Base("Fight on", 314));

        Controls = Story::Controls::STANDARD;
    }
};

class Story239 : public Story::Base
{
public:
    Story239()
    {
        ID = 239;

        Image = "images/filler4-green.png";

        Text = "The captain listens to your tale with equal measures of horror disbelief. \"It's a hard tale to swallow,\" he says at last, \"but I've heard this fellow Skarvench is full of hubris.\"\n\n\"It's no mere pipedream,\" says Grimes. \"Skarvench is cunning and ruthless. If he's set his sights on such a prize, you can be sure he has a good plan.\"\n\nThe captain scratches his head. \"It is true that the Queen's flagship is bound for the colonies,\" he admits. \"But I only heard the news myself as I was about to set sail from Glorianne, so Skarvench must have spies in high places. I'd help if I could, but my vessel is only a merchantman and would fare badly against a fully-armed pirate ship.\"\n\nHe finally agrees to set you off in Port Selenice, where you have your best chance of enlisting aid against Skarvench. Then, wishing you well, he resumes his journey towards Leshand.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORD(player, Codeword::Type::CHANCERY))
        {
            return 406;
        }
        else
        {
            return 165;
        }
    }
};

class Story240 : public Story::Base
{
public:
    Story240()
    {
        ID = 240;

        Text = "You are dragged aboard the Belle Dame. Jeering, the pirates gather round and tie you and your friends to the rail. The burly mate, Porbuck, steps forward swinging a whip in his hand. His huge flabby face is creased into a ghoulish grin.\n\n\"While the cat's away, eh, Porbuck?\" says Oakley. He is trying to sound flippant, but his face is the curdled-milk colour of fear. \"Skarvench won't like it if you kill us before he gets back.\"\n\nPorbuck chortles as he raises the whip. \"Don't you go worryin', Oakley. You won't just die yet. Reckon you'll beg for it though...\"\n\nHours of agony pass before your flayed bodies are finally cast into the sea. By that time you gratefully accept the cool oblivion of death.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story241 : public Story::Base
{
public:
    Story241()
    {
        ID = 241;

        Text = "You raise your fists and step quickly forward, ready to give the demon-witch a sound thrashing if she doesn't lift her spell and allow you to leave the island. For her part, she gives you a disdainful smile and places her hands on her hips, tilting her chin back mockingly. \"Come, mortal,\" she says. \"plant your best punch. Then I'll take my turn, and we'll see who's left standing after that.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Take a swing at her as she's inviting you to", 271));
        Choices.push_back(Choice::Base("Grapple with her with an armlock", 290));
        Choices.push_back(Choice::Base("Lift her over your head for a body slam", 309));
        Choices.push_back(Choice::Base("Surrender before she gives you a beating you might not survive if you're afraid that you are outclassed", 119));

        Controls = Story::Controls::STANDARD;
    }
};

class Story242 : public Story::Base
{
public:
    Story242()
    {
        ID = 242;

        Text = "You sit up suddenly with a groan. Your chest feels as though you've been kicked by a horse, but by rights you ought to be dead.\n\nShaking your head to clear it, you look down and discover that Skarvench's bullet was deflected by the article hanging at your breast. Instead of hitting your heart, it glanced off the metal and only left a long red gash.\n\nGrimes' face comes into focus. \"How long have ?I been out cold?\" you ask him, each breath making you wince in pain.\n\n\"At least quarter of an hour, skipper.\"\n\nQuite a crowd has gathered around you, As you stagger groggily to your feat, you find you're still holding the CORKSCREW. \"A fat lot of good this did me.\"\n\nOakley cracks a grind, relieved to see you're alright. \"I dunno, you might've had his remaining eye out with it if you'd been a bit closer.\"\n\nAnd elderly pirate steps out of the crowd. You recognize him as a respected man in the disreputable community of Selenice. \"Skarvench broke the Brethren's law,\" he says. \"He's an outcast now. No port on the Carab will give him shelter.\"\n\nBlutz is nursing a lump on his head. His nostrils flare in rage as he cries, \"If Skarvench succeeds in abducting Queen Titania he'll be rich enough to buy his own port!\n\n\"He won't,\" you say in a voice laced with icy determination.";

        Choices.clear();
        Choices.push_back(Choice::Base("Take the CORKSCREW", 343, Choice::Type::GET_ITEMS, {Item::CORKSCREW}));
        Choices.push_back(Choice::Base("Leave it alone", 343));

        Controls = Story::Controls::STANDARD;
    }
};

class Story243 : public Story::Base
{
public:
    Story243()
    {
        ID = 243;

        Text = "A key that no one can see or touch? The ocean god's riddle leaves you baffled until you remember the hornpipe in your pocket. Putting it to your lips, you play a snatch of an old sea shanty. As you do, the chain unlocks itself, falling aside to admit your boat into the harbour.\n\n\"Well, son of a gun!\" says Blutz. \"It was a musical key that was needed, then.\"";

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 205; }
};

class Story244 : public Story::Base
{
public:
    Story244()
    {
        ID = 244;

        Text = "Clutching your LETTER OF MARQUE, you emerge into the sunshine with the happy air of scholars who have just been awarded their diploma. Outwardly you retain the weather-beaten faces and grimy clothes of common street ruffians, but the document in your hands proclaims otherwise. Now you are licensed privateers - proud sea warriors in the conflict with the rapacious kingdom of Sidonia!\n\n\"Now all we need is a ship,\" says Blutz.\n\nThe rest of you whirl and glare at him, the contended smiles wiped off your faces in an instant. Trust the fat oaf to bring you down to earth with a bump.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::LETTER_OF_MARQUE});
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORD(player, Codeword::Type::MARATHON))
        {
            return 69;
        }
        else
        {
            return 107;
        }
    }
};

class Story245 : public Story::Base
{
public:
    Story245()
    {
        ID = 245;

        Text = "El Draque raises his arms and comes forward to embrace you. It could almost be the gesture of one greeting a long-lost friend -- if not for the fangs that gleam like talons beneath his white lips.\n\nA seagull wheels high above in the cloudless indigo sky, its wings catching a last flicker of sunlight. You see one chance. Your sword flashes in the grey dusk too fast for the eye to follow. For an instant El Draque stands rooted to the spot, arms outstretched, not yet aware of what you've done. Then a torrent of mingled hate and anguish and disbelief washes across his pale contorted features as he looks down to see your SWORD hilt protruding from his chest. He falls and crumbles to a pile of ash, and as he does the other vampires slump to the ground also. A ghastly keening rises from their lips as they slowly dissolve, leaving nothing but a miasmal stench and dark patches in the sand.\n\nYou are about to retrieve your SWORD, but Blutz advises you to leave it where it is. \"I've heard vampires can reform themselves even from lifeless dust.\" he says with a shudder.";

        Bye = "Then hurriedly loading the silver ingots aboard the LADY OF SHALOTT, you set sail for Selenice.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::LOSE_ITEMS(player, {Item::Type::SWORD});
    }

    int Continue(Character::Base &player) { return 16; }
};

class Story246 : public Story::Base
{
public:
    Story246()
    {
        ID = 246;

        Text = "Without the lunar wind to fill her sails, the Moon Dog drops quickly. You hear her splash down some distance off your starboard bow.\n\n\"Now Skarvench is seaborne like us,\" says Oakley with a fierce smile. \"If not for this damned fog, we could give him a battle he'd not soon forget.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Use a THUNDERCLOUD FAN", 265, {Item::THUNDERCLOUD_FAN}));
        Choices.push_back(Choice::Base("[SPELLS] Disperse the fog", 284, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("Otherwise", 303));

        Controls = Story::Controls::STANDARD;
    }
};

class Story247 : public Story::Base
{
public:
    Story247()
    {
        ID = 247;

        Text = "Darting quickly over into the hold, you break open a travelling chest bearing the royal seal. You scatter the packed clothes and jewels that are inside until you find what you are looking for: one of the Queen's voluminous gowns. Pulling this on, you hurry back on deck, drawing amazed stares from your comrades.\n\n\"Good grief, skipper!\" says Oakley with a wry smile. \"You makes a bloomin' pretty queen, and no mistake!\"\n\n\"Get out of sight, all of you,\" you tell them. Then, lying in to wait behind the overturned water-barrel, you watch until the rope begins to stir. Someone is descending. You see him slide down the rope as loathsome as a great black spider -- Skarvench himself! Choking back the urge to attack him at once, you wait until he reaches the deck before pretending to stumble out of your hiding-place.\n\n\"Oho!\" he cries. \"The precious baggage herself! It's right handy of you to make my job so easy, yer majesty.\" So saying, he reaches out and hefts you over his shoulder. \"Whuf! You're a weighty lass. But a spell on biscuit an' water'll soon take some o' that ample flesh off your bones. That an' the cat, o' course!\"\n\nYou wait until he has carried you halfway up the rope. You may as well let the brigand wear himself out before you kill him. Now you are suspended in a weird misty void between sea and sky, with just the faint haze of moonshine to light your final confrontation. You wrest out of his grasp, seize the rope, and throw off your disguise.\n\n\"You!\" gasps Skarvench.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 323; }
};

class Story248 : public Story::Base
{
public:
    Story248()
    {
        ID = 248;

        Text = "There is a meaty smack as your fist connects with this solar plexus. He makes a soft sucking sound and falls like a fish out of water. Stooping, you deliver a punch to the jaw that lays him out cold. Freezing, you listen tensely but the conversation in Skarvench's cabin continues as before. Nobody heard anything. Still, you had better not tarry here any longer.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 172; }
};

class Story249 : public Story::Base
{
public:
    Story249()
    {
        ID = 249;

        Text = "Reaching the top of the cliffs, you stand atop a spar of rock which gives you a clear view of the interior of the Island. Lush jungle clings to the flanks of a sharply peaked mountain in the centre. The summit of the mountain is hidden by a haze of cloud. Nearer at hand you spy succulent fruits. From beyond the curtain of foliage comes the burgling of a brook.";

        Choices.clear();
        Choices.push_back(Choice::Base("Collect PROVISIONS", 306));
        Choices.push_back(Choice::Base("Explore the interior of the island", 325));
        Choices.push_back(Choice::Base("Return to the boat and resume your journey", 116));

        Controls = Story::Controls::STANDARD;
    }
};

class Story250 : public Story::Base
{
public:
    Story250()
    {
        ID = 250;

        Text = "\"This seems a bountiful enough place -- indeed, a very Eden,\" says Grimes. \"Why don't we tarry here a while, shipmates, and get our strengths back for the long haul to Port Leshand?\"\n\nBlutz casts another nervous glance towards the centre of the island. Rearing above the treetops is the high cone of the volcano, ashen smoke lying above it like a thunderhead. \"I'm not so sure.\" he says.";

        Choices.clear();
        Choices.push_back(Choice::Base("Spend a few more days here", 288));
        Choices.push_back(Choice::Base("Be on your way", 135));

        Controls = Story::Controls::STANDARD;
    }
};

class Story251 : public Story::Base
{
public:
    Story251()
    {
        ID = 251;

        Text = "She emerges from the shadows of the entrance: a stately figure with skin the colour of burnished oak and hair like a shower of green stars. Her clothing and accent are not those of a Carab native, but seem to evoke the mysteries of an ancient civilization. \"I am Ejada, witch-queen of this isle,\" she tells you. \"I demand tribute from all who come to my shores, but my demands are not excessive. All I'll take is the soul of one of you, to be sacrificed at dawn to my mother the Earth Goddess.\"\n\n\"Send your own soul to hell!\" yells Oakley, snatching up a rock and dashing forward. Ejada calmly sweeps her arm, knocking Oakley to the ground as though he'd run into a tree branch.\n\n\"Return here in the hour before dawn,\" Ejada goes on. \"By then you must have decided which of you will give up his soul.\n\nHelping Oakley to his feet, you return to find the jollyboat sunk deep into the sand of the beach. You try digging it up, but it only sinks deeper. \"That's that, then,\" sobs Blutz. \"The witch's magic has trapped us here. We'll have to choose who's to die!\"";

        Choices.push_back(Choice::Base("[SEAFARING] Make a raft", 308, Skill::Type::SEAFARING));
        Choices.push_back(Choice::Base("Go to her at dawn as she told you to", 327));
        Choices.push_back(Choice::Base("Try hiding from her", 346));

        Controls = Story::Controls::STANDARD;
    }
};

class Story252 : public Story::Base
{
public:
    Story252()
    {
        ID = 252;

        Image = "images/warship-green.png";

        Text = "The warship stands much taller than your own vessel, making your few cannon-shots largely ineffective. Your shells smack into the warship's strong oaken flanks with hardly more effect than grape-shot. If only you could score a hit on the enemy's rigging.\n\nThe warship does not return fire. Those mighty guns could easily blast you to kindling, but she is steering instead so as to pull alongside for a boarding action.";

        Choices.push_back(Choice::Base("Use [SPELLS]", 35, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("Use [AGILITY]", 54, Skill::Type::AGILITY));
        Choices.push_back(Choice::Base("Use a THUNDERCLOUD FAN", 263, {Item::THUNDERCLOUD_FAN}));
        Choices.push_back(Choice::Base("Use the BRONZE HELMET", 282, {Item::BRONZE_HELMET}));
        Choices.push_back(Choice::Base("Stand by to repel boarders", 73));

        Controls = Story::Controls::STANDARD;
    }
};

class Story253 : public Story::Base
{
public:
    Story253()
    {
        ID = 253;

        Text = "The islanders stare in horror at the red death's head daubed across your face. Several of them step forward with raised spears, angry defiance slowly replacing their initial shock. It is Grimes who realises the cause: \"Those other natives must be their enemies. And they think you're one of 'em.\"";

        Choices.push_back(Choice::Base("[MARKSMANSHIP] Shoot your way out of this", 196, Skill::Type::MARKSMANSHIP));
        Choices.push_back(Choice::Base("Try fighting your way through them back to the water", 215));
        Choices.push_back(Choice::Base("Resort to [CUNNING]", 234, Skill::Type::CUNNING));
        Choices.push_back(Choice::Base("Try wiping off the red dye and offering gifts to mollify them", 291));

        Controls = Story::Controls::STANDARD;
    }
};

class Story254 : public Story::Base
{
public:
    Story254()
    {
        ID = 254;

        Text = "Throughout a tempestuous night, Oakley screams verse after verse of his morbid dirge, vying with the thunder's roar until his voice is as hoarse as the croak of a dying man. You can tell from the looks on the others' faces that they have been infected by Oakley's mod. Desperation at your sorry plight has now been worn down to hopelessness and new horror.\n\n\"Dawn,\" says Grimes, nodding towards a dreary grey gleam beyond the soot-coloured clouds. \"I doubt we'll live to see another.\"\n\nThe day goes on, and you grow weaker.\n\nYou gained the codeword CHANCERY. You LOSE 1 Life Point.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_CODEWORDS(player, {Codeword::Type::CHANCERY});

        Character::GAIN_LIFE(player, -1);
    }

    int Continue(Character::Base &player) { return 273; }
};

class Story255 : public Story::Base
{
public:
    Story255()
    {
        ID = 255;

        Text = "Decide which item you will use.";

        Choices.clear();
        Choices.push_back(Choice::Base("Use a butcher's CLEAVER", 331, {Item::CLEAVER}));
        Choices.push_back(Choice::Base("Use a CRUCIFIX", 350, {Item::CRUCIFIX}));
        Choices.push_back(Choice::Base("[CUNNING] Use a TOOLKIT", 369, Skill::Type::CUNNING, {Item::TOOLKIT}));
        Choices.push_back(Choice::Base("You do not have any of these items", 388));

        Controls = Story::Controls::STANDARD;
    }
};

class Story256 : public Story::Base
{
public:
    Story256()
    {
        ID = 256;

        Text = "Throughout another night and day you are swept westwards by the strong sea current. Sometime after dusk, as night shrouds the vast expanse of water and closes walls of darkness around the tiny confines of your boat, you hear a voice hailing you: \"Ho there! Who is it? I hear your oars -- speak up!\"\n\nBlutz peers out into the darkness. \"I think I see him,\" he whispers to the rest of you. \"A lone figure on a raft. Must've been shipwrecked.\"\n\n\"Shall we row over and pick him up?\" says Grimes.\n\nPredictably, Oakley is against this. \"We have enough bad luck to go around as it is. Why add another hungry mouth to an already overcrowded boat?\"";

        Choices.push_back(Choice::Base("Row over to the man on the raft", 294));
        Choices.push_back(Choice::Base("Agree with Oakley that you should ignore him", 313));

        Controls = Story::Controls::STANDARD;
    }
};

class Story257 : public Story::Base
{
public:
    Story257()
    {
        ID = 257;

        Text = "The shot rings out in the night and a puff of gunsmoke drifts like silver fog in the moonlight. As the smoke clears you see to your astonishment has not fallen. He is just standing there with a ghastly bloodless grin, eyes blazing like a ship's lanterns. Then you notice something else -- the bullet didn't miss him. There is a gaping hole through his chest. For a long moment no-one moves a muscle. Silence gives the scene an air of unreality.\n\n\"He's not a living man!\" gasps Blutz at last. \"He's one of the undead!\"";

        Choices.push_back(Choice::Base("Launch a barehanded assault on Mortice", 219));
        Choices.push_back(Choice::Base("[SWORDPLAY] Attack him with a SWORD", 238, Choice::Type::SKILL_ANY, Skill::Type::SWORDPLAY, {Item::SWORD, Item::RUSTY_SWORD, Item::CLEAVER, Item::SHARKS_TOOTH_SWORD}));
        Choices.push_back(Choice::Base("Avoid a confrontation: Cut the line mooring his raft to the jollyboat", 276));

        Controls = Story::Controls::STANDARD;
    }
};

class Story258 : public Story::Base
{
public:
    Story258()
    {
        ID = 258;

        Text = "You arrive at Leshand harbour to find the town awash with troops. It is not long before you hear the news that has stirred up such panic. \"The nefarious buccaneer Skarvench has captured the Queen of Glorianne,\" a stevedore tells you as he unpacks the ship's cargo. \"He's demanding a million doubloons in ransom, otherwise, he'll make a gift of her to her arch-enemy the King of Sidonia.\"\n\n\"Woeful news!\" groans Oakley. \"The Sidonians will likely break her on the wheel, or tie her to an anchor and send her to sup with Davy Jones! If only we could have done something to prevent it.\"\n\nYou could have, but you frolicked too long in an island paradise. Now your part in history is at an end.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story259 : public Story::Base
{
public:
    Story259()
    {
        ID = 259;

        Text = "You are able to jury-rig a weather cloth using strips torn from everyone's clothing. When this is fitted around the boat it has the effect of raising the freeboard, helping to keep the water from sloshing over the sides. You also inspect the planking and make sure that any cracks where the boat is taking in water are plugged with wadding.\n\n\"Will we stay afloat through another storm like last night's though?\" asks Grimes when he sees you taking these measures.\n\nYou shrug. \"Pray for better weather.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 26; }
};

class Story260 : public Story::Base
{
public:
    Story260()
    {
        ID = 260;

        Text = "You reply with a discreet smile and draw the official aside, adopting the conspiratorial tone of one elegantly mannered knave to another. By promising him a lavish share of any treasure you take from Sidonian galleons, you finally manage to convince him to issue you with a LETTER OF MARQUE.\n\nYou gained the codeword MAMMON.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_CODEWORDS(player, {Codeword::Type::MAMMON});
    }

    int Continue(Character::Base &player) { return 244; }
};

class Story261 : public Story::Base
{
public:
    Story261()
    {
        ID = 261;

        Text = "You look at the CORKSCREW in your hand. \"Of course! This is how we'll get our ship.\"\n\nThe others watch you with rekindled concern. \"Maybe you ought to lie down for a bit, skipper?\" suggests Blutz. \"You took a nasty knock back there.\"\n\nIn answer you give only a triumphant laugh, setting out towards the harbour with a determined stride they are hard pressed to match. Now you see clearly that it was divine providence that guided your hand to the CORKSCREW -- the same divine providence that deflected the bullet and saved your life. The force of conviction bears you on like a gale until you stand on the quayside, a smile playing on your lips as you gaze at the lapping waves.\n\nThe others come up just as you are withdrawing the cork from the bottle. They gasp in astonishment to see a weird green vapour billow out, spreading to lie in a thick fog-bank beside the quay. A wind rises, stirs the fog, then dissipates it like a puff of steam.\n\nSomeone mutters an oath. Where the green fog hung moments before, a ship now lies -- moored -- a fine gilded galleon with a figurehead in the shape of a lion's head. Cannons fashioned to resemble leonine paws adorn her flanks. Her furled sails blaze like sunlit clouds against the azure of the sky.\n\n\"A magic ship..!\" breathes blutz. \"What'll we call her?\"\n\n\"She's the PROVIDENCE,\" you reply. \"Gentlemen, shall we go aboard?\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::TAKE_SHIP(player, Ship::PROVIDENCE);
    }

    int Continue(Character::Base &player) { return 184; }
};

class Story262 : public Story::Base
{
public:
    Story262()
    {
        ID = 262;

        Text = "The RING sparkles in the rich moonlight. The gold looks almost green, the jewelled eyes have a submarine glow. \"Who could doubt it is the very image of Leviathan, greatest of sea serpents?\" You are struck almost breathless in awe. \"See, it all but shines with power! I feel I have only to call upon the serpent by name, and he'll rise up from the depths and sweep this chain asunder.\"\n\nEvery sailor has heard the ancient myths of Leviathan, the sea monster born out of primordial chaos.\n\n\"As it says in the Book of Job: Iron he counts as straw, and brass as rotten wood,\" puts in Oakley.\n\nGrimes turns to you with a dour look. \"It is also said: \"If ever thou think to rouse him, consider the struggle that awaits thee and let it be.\" And in Isaiah is he not called \"the fleeing serpent, twisting serpent\"? Do not call him up from the deep, I pray you, or we are all dead men.\"";

        Choices.push_back(Choice::Base("Insist on using the magic RING", 281));
        Choices.push_back(Choice::Base("Do not use the RING", 72));

        Controls = Story::Controls::STANDARD;
    }
};

class Story263 : public Story::Base
{
public:
    Story263()
    {
        ID = 263;

        Text = "One sweep of the magic fan is enough to produce a powerful gale. The warship's sails snap taut and she is sent veering away with white-flecked billows surging high up around her heaving prow. It is as though the sea a cannon-shot from your bows is being churned up by a mighty storm, while the water around you has only a gentle swell. Your own canvas catches just a strong clear breeze that drives you safely away, while the warship is borne far astern in the grip of the storm.\n\nYou find the THUNDERCLOUD FAN has gone, vanishing once its power was expended.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::LOSE_ITEMS(player, {Item::Type::THUNDERCLOUD_FAN});
    }

    int Continue(Character::Base &player) { return 16; }
};

class Story264 : public Story::Base
{
public:
    Story264()
    {
        ID = 264;

        Text = "El Draque clutches you to him. You are powerless to resist; you feel like a sleepwalker.He presses his lips against your throat, and a moment of cold pain is followed by a spreading glow of warmth. Drowsiness clouds your mind as you spiral down into a whirlpool of dark oblivion. You will awaken into the half living world of the undead, cursed to roam the seas without a soul in search of human blood.\n\nYou failed to save the Queen. You failed to slay Skarvench. You failed even to earn yourself a clean quick death.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story265 : public Story::Base
{
public:
    Story265()
    {
        ID = 265;

        Image = "images/filler1-green.png";

        Text = "A single sweep of the fan summons a strong wind. The fog swirls and parts, swiftly dispersing into wispy tendrils. You now clearly sight both the crippled Rose and, closer to you, the Moon Dog. She is standing at two o'clock off your starboard bow, just in cannon range. You have the weather gauge, meaning that the wind is blowing from behind you towards the Moon Dog -- the ideal position for a sea battle.\n\n\"Now we have a choice,\" says Oakley. \"We can sail in to board her, or stand off and rake her with our guns. \"What's it to be, skipper?\"\n\nAs captain it is your decision.";

        Choices.push_back(Choice::Base("Steer in towards the Moon Dog", 322));
        Choices.push_back(Choice::Base("Unlimber your cannons", 341));

        Controls = Story::Controls::STANDARD;
    }
};

class Story266 : public Story::Base
{
public:
    std::string PreText = "";

    Story266()
    {
        ID = 266;

        Image = "images/doctor-mirabilis-green.png";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "A deck plank creaks behind you. You turn to see a thin scholarly-looking figure with a neat goatee beard. You have never met him before, but his arcanely patterned robes and peaked cap mark him out unmistakeably. His the Queen's court wizard, Dr Wild.\n\n\"You've been quite troublesome, so my brother tells me,\" he says in a mock-mild voice.\n\nYou look at the wand in his hand, already flickering with sorcerous energy. \"I've hardly got started yet,\" you tell him.\n\nYou were hoping to goad him into talking while you edged closer, but he is too wily for that. Instead of replying, he only smiles and gives an almost regretful shake on his head. Waving the wand, he conjures a phantasmal green harpoon out of thin air and hurls it at your chest.\n\n";

        if (Character::VERIFY_SKILL(player, Skill::Type::CHARMS))
        {
            PreText += "[CHARMS] You have magically deflected the harpoon.";
        }
        else
        {
            Character::GAIN_LIFE(player, -3);

            PreText += "The magic harpoon pierces your flesh. You LOSE 3 Life Points.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::SPELLS))
        {
            return 285;
        }
        else
        {
            return 304;
        }
    }
};

class Story267 : public Story::Base
{
public:
    std::string PreText = "";

    Story267()
    {
        ID = 267;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Type = Story::Type::NORMAL;

        PreText = "\"Well, if it ain't me prodigal orphans!\" chortles Skarvench, drawing his sword and pistol as he sees you break from the undergrowth. \"You ran off without collectin' your back pay, mates, so he's a little something on account, like.\" So saying, he levels his pistol and pulls the trigger.\n\nPain lances through your shoulder as the shot tears flesh and splinters bone. But sheer hatred of your foe drives you on. A red haze sparkles across your vision, and Skarvench's grinning face is like a painting in blood on the back of your eyes as you race forward with a savage snarl.";

        if (Character::VERIFY_SKILL(player, Skill::Type::MARKSMANSHIP) && Character::VERIFY_SKILL_ANY(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::RUSTY_SWORD, Item::Type::CLEAVER, Item::Type::SHARKS_TOOTH_SWORD}))
        {
            Character::GAIN_LIFE(player, -8);

            PreText += "\n\n[SWORDPLAY] [MARKSMANSHIP] You LOSE 8 Life Points.";
        }
        else
        {
            Type = Story::Type::DOOM;

            PreText += "\n\nYou sell your life dearly in a futile slaughter.";
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 23; }
};

class Story268 : public Story::Base
{
public:
    Story268()
    {
        ID = 268;

        Text = "Your companions look on with sour sidelong glances as you hungrily devour the crabs. You stare back at them defiantly until they turn away. After all, didn't they leave the decision to you? As leader, you must try to keep your strength up.\n\nYou RECOVER 1 Life Point and gained the codeword CHANCERY.";

        Choices.push_back(Choice::Base("Continue on your way", 116));
        Choices.push_back(Choice::Base("Explore the island", 211));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, 1);

        Character::GET_CODEWORDS(player, {Codeword::Type::CHANCERY});
    }
};

class Story269 : public Story::Base
{
public:
    Story269()
    {
        ID = 269;

        Text = "\"In God's name, the devil's caught up with us!\" says Oakley with a gasp of horror as the four of you return to the shore.\n\nYou were bringing up the rear and are still pushing your way out of the undergrowth. Hearing this oath, you hurry to catch up and see what it is that has stopped Oakley and the others dead in their tracks. When you do, it is as though the chill wind of a midwinter night had blown for an instant through the sweltering heat of this tropical jungle. For, out at sea but coming nearer by the minute, lies Skarvench's ship: the dreaded Belle Dame. Drenched in the blood-red light of sunset, it is a sight that closes icy fingers of fear around your heart.\n\n\"They're making anchorage outside the cove,\" says Grimes, shielding his gaze against the low sun. \"It's too shallow for them to bring her right in, lucky for us. They won't know we're here yet. Maybe we'll have a chance of slipping away under cover of darkness.\"\n\nYou rub your jaw, mulling over the other options. Despite your hatred of Skarvench -- and yes, you admit it: your fear of him - you are curious to know why he's come here. \"We could haul the jollyboat up into the jungle and hide it,\" you suggest. \"Then if Skarvench sends a party ashore, we can spy on them.\"\n\n\"Foolishness,\" avers Oakley. \"I agree with hiding the boat, but then we should go deep into the jungle and lie low until Skarvench has left. Let's stay clear of him and his cronies.\"\n\nWhat will you do?";

        Choices.push_back(Choice::Base("Try to get off the island after dark", 307));
        Choices.push_back(Choice::Base("Spy on Skarvench's shore party", 326));
        Choices.push_back(Choice::Base("Stay out of sight until they're long gone", 288));

        Controls = Story::Controls::STANDARD;
    }
};

class Story270 : public Story::Base
{
public:
    Story270()
    {
        ID = 270;

        Text = "Drawing your PISTOL, you shoot one of the natives dead just as he is raising his spear to thrust at you.\n\nThe loud bang startles the other natives. They rush back a few paces, screeching in astonishment. When they see blood spreading from the corpse of the native you shot, they start to make a weird moaning sound and tremble with fright.\n\n\"It seems they've never seen firearms before,\" grunts Oakley. \"Trouble is, you just used your one shot.\"\n\n\"They don't know that, do they,\" you reply. \"Come on, everyone -- let's get down to the beach. Don't rush unduly, but don't dawdle either.\"\n\nYou gained the codeword FETISH.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_CODEWORDS(player, {Codeword::Type::FETISH});
    }

    int Continue(Character::Base &player) { return 400; }
};

class Story271 : public Story::Base
{
public:
    std::string PreText = "";

    Story271()
    {
        ID = 271;

        Choices.clear();
        Choices.push_back(Choice::Base("[SPELLS] Try using a WAND", 384, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("[MARKSMANSHIP] Use a PISTOL", 317, Skill::Type::MARKSMANSHIP));
        Choices.push_back(Choice::Base("Make a run for it", 5));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Your fist comes up and smashes into Ejada's jaw with agonizing force. Agonizing to you, that is. As you reel back, clutching your knuckles and groaning with pain, she laughs languidly and sweeps her arm out, dashing you to the ground without apparent effort.\n\n";

        auto DAMAGE = -4;

        if (Character::VERIFY_ITEMS(player, {Item::Type::FEATHER_SHIELD}))
        {
            DAMAGE = -2;

            PreText += "[Item: FEATHER SHIELD] ";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Point(s).";

        if (player.Life > 0)
        {
            PreText += "\n\nYou take stock of your situation. Hand-to-hand combat with her is futile as punching an oak tree.";
        }

        Text = PreText.c_str();
    }
};

class Story272 : public Story::Base
{
public:
    Story272()
    {
        ID = 272;

        Text = "The natives bring you baked root-bread, fruit and gourds full of fresh water. You can TAKE enough PROVISIONS for two meals.\n\nThey also take a look at your battered craft and help to patch up any damage, demonstrating amazing skill with no tools other than bamboo and wooden leaves.\n\nWith the help of sign language, the chief explains to you that not many ocean-going vessels visit this island. If you were to stay here you might be marooned for months. On the other hand, he offers to escort you southwards to the main shipping-lane, where you might meet up with a ship bound for civilization. You soon realise that this would not be a free service, however. He expects a gift of some kind.";

        Choices.clear();
        Choices.push_back(Choice::Base("Give the chief a gift in return for being escorted south", 310));
        Choices.push_back(Choice::Base("Head on towards Leshand without his help", 177));
        Choices.push_back(Choice::Base("Stay on the island and wait for rescue", 348));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Take = {Item::PROVISIONS, Item::PROVISIONS};

        Limit = 2;

        if (Character::VERIFY_ITEMS(player, {Item::Type::BOOK_OF_CHARTS}))
        {
            Choices[2].Destination = 329;
        }
        else
        {
            Choices[2].Destination = 348;
        }
    }
};

class Story273 : public Story::Base
{
public:
    Story273()
    {
        ID = 273;

        Text = "Towards sunset the storm finally blows over, leaving the clouds in the west lying like blots of blood across the steel rim of the sea.\n\nThe four of you are by now slumped in the bottom of the boat, as limp as corpses on a trestle. Your lips are black and blistered, your flesh fish-white and swollen with sores. Blutz gnaws his knuckle until it bleeds, jut to feel moisture on his tongue. After looking up at the sky Grimes starts to shiver, either from dread of the onrushing night or because he is in the first stages for fever.\n\nA shadow shimmers against the last light of day. A ship's sails show purple-black against the red haze. \"We're saved!\" gasps Oakley, raising his hands to hail the ship. \"Ahoy there!\"";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_SKILL(player, Skill::Type::FOLKLORE))
        {
            Choices.push_back(Choice::Base("Call out to the ship through the gathering dusk", 311));
            Choices.push_back(Choice::Base("Advise Oakley to keep quiet until she's passed", 330));
        }
    }

    int Continue(Character::Base &player) { return 292; }
};

class Story274 : public Story::Base
{
public:
    Story274()
    {
        ID = 274;

        Image = "images/filler2-green.png";

        Text = "You select a number of DIAMONDs, each the size of a walnut.\n\n\"They're worth a queen's ransom!\" gasps Blutz as he sees you gather the jewels together.\n\n\"Perhaps that's what we should call the ship we're going to buy them with,\" you reply smiling. \"THE QUEEN's RANSOM.\"\n\nLeaving Mandrigard to sleep over his still-lavish treasure hoard, you tiptoe out of the cabin and ascend to the deck.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Take = {Item::DIAMOND, Item::DIAMOND, Item::DIAMOND};

        Limit = 3;
    }

    int Continue(Character::Base &player) { return 217; }
};

class Story275 : public Story::Base
{
public:
    Story275()
    {
        ID = 275;

        Text = "Hunger saps your strength. You spend the night half in slumber and half in a dead faint. Cold sweat soaks your clothes. Even sunrise fails to warm the chill out of your bones, and as you crouch at the back of the boat shivering you realise you are running a fever.\n\nYou LOSE 1 Life Point.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -1);
    }

    int Continue(Character::Base &player) { return 256; }
};

class Story276 : public Story::Base
{
public:
    Story276()
    {
        ID = 276;

        Text = "Casting off, you row away from the raft with all haste. It dwindles into the distance until it is visible only as a moonlit speck far to stern. Mortice is still to be seen jumping in rage, appearing like a guttering candle-flame in the distant darkness. His last curse comes like a sight of wind across the water: \"El Draque drink your blood, you swabs...\" and then there is silence and unbroken night.\n\nAt last you deem it safe to sleep. Tomorrow you pray you will sight another vessel. How much longer can you survive otherwise?";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 332; }
};

class Story277 : public Story::Base
{
public:
    Story277()
    {
        ID = 277;

        Text = "\"A pretty sunrise,\" says Oakley painfully through swollen lips. \"It'll likely be the last we see in this life.\"\n\nGrimes nods. \"It's warm enough where we're going, my merry lads.\"\n\nYou give a grunt of disapproval. \"Don't tempt the Devil with your grim jokes, Mister Grimes. He might think you're wishing out loud, and come to collect you personally. We're bound for a better harbour than that, I think. Hellfire isn't for honest scoundrels like us, but for rank fiends of Skarvench's cut.\"\n\nYou LOSE 2 Life Points.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -2);
    }

    int Continue(Character::Base &player) { return 120; }
};

class Story278 : public Story::Base
{
public:
    Story278()
    {
        ID = 278;

        Text = "You have always made sure of nurturing a network of paid informers in large towns such as Leshand, and now your foresight reaps dividends. You soon discover that Skarvench recently collected all outstanding debts and redeemed his treasures for hard cash. The evidence points to some sort of ambitious project for which he will need every bit of finance that he can muster.\n\n\"I've heard he's engaged a shipwright in Port Selenice,\" one of your informants tells you. \"A special commission it was, for a ship to be called the Moon Dog. Got a lot of odd features.\"\n\n\"Such as?\"\n\nHe leans closer, dropping his voice to a whisper. \"Gun ports along the keel! And other things, even weirder than that. Perhaps ol' Skarvench has gone mad -- but heaven help us all if so, for a mad dog is no nicer than a sane one.\"\n\nAs you turn away, the informant snatches at your sleeve. \"Here, what about my pay?\"\n\nYou tug away from his grip. \"For that tittle-tattle you've just told me? It's common knowledge that I could've had from any gossip in town. That's not what I pay you for, and you know it.\"\n\nIgnoring his grumbles, you walk away. There are other rumours you might look into.";

        Choices.clear();
        Choices.push_back(Choice::Base("Look into rumours concerning El Draque", 164));
        Choices.push_back(Choice::Base("Look into rumours concerning Queen Titania", 202));
        Choices.push_back(Choice::Base("Go shopping", 12));
        Choices.push_back(Choice::Base("Find someone who can identify magical items", 31));
        Choices.push_back(Choice::Base("Apply for a LETTER OF MARQUE", 409));
        Choices.push_back(Choice::Base("(Marathon) Pay a visit to Master Capstick", 69, Codeword::Type::MARATHON));
        Choices.push_back(Choice::Base("You have completed all your business in Leshand", 107));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::ROGUERY))
        {
            Choices[4].Destination = 50;
        }
        else
        {
            Choices[4].Destination = 409;
        }
    }
};

class Story279 : public Story::Base
{
public:
    Story279()
    {
        ID = 279;

        Text = "\"I got it fair and square, by the law of the sea,\" snorts Mandrigard. \"Took it from a marble hall atop an island cliff, and no hand was raised against me and my merry lads. But as we went -- not a man Jack of us able to straighten his back under the weight of loot, mind you -- and old fool of a priest called after us with a curse. He told us we'd know no rest sailing the ocean's breadth for ever more, and never able to find port nor set foot ashore so long as our hands were tainted with the theft of sacred treasures.\"\n\nHe pauses draining his wine-cup yet again. It occurs to you that you have not seen him refill it from the jug, but it never seems empty.\n\nRain rattles on the shutters across the cabin window. The ship's timbers groan and sigh as she sails on before the wind.";

        Choices.clear();
        Choices.push_back(Choice::Base("Ask Mandrigard anything else", 46));
        Choices.push_back(Choice::Base("Explore the rest of his ship", 65));

        Controls = Story::Controls::STANDARD;
    }
};

class Story280 : public Story::Base
{
public:
    Story280()
    {
        ID = 280;

        Text = "Leading your comrades out of town, you walk to a secluded cove along the beach. \"What have we come here for?\" asks Blutz. \"Is it a smugglers' cove?\"\n\nGrimes nods approvingly. \"A good idea, if so. Any smugglers who try to avoid the port levy in Selenice can hardly go whining to the Brethren if we seize their contraband.\"\n\n\"No, there aren't any smugglers,\" you say. \"But if I'm right, it's here we'll get our ship.\" You wait at the fringe of the beach with sea foam at your feet. Sunset first sets the sky afire, then drains it of colour. Finally, raising the CONCH-SHELL HORN to your lips, you blow a low note. It resounds out into the velvet dusk, rolling eerily across the water.\n\nYou lower the horn, but it continues to sound. The note gets deeper and louder. It is throbbing in your hands now, pulsing with magical energy. \"It's going to explode!\" shrieks Blutz in sudden alarm. \"Get rid of it, skipper!\" Before you can stop him, he has snatched the horn and lobbed it far out into the waves.\n\nThe sound continues to build under the water, like the deepest rumbling note of a submerged organ. You avert your eyes, hands pressed to your ears, as a titanic blast sends a waterspout gushing into the air. Droplets of brine shower down around you. You look back out to sea. Something has bobbed up from the sea bed and is coming towards you: a coracle formed of a giant half-shell drawn by a shark and a dolphin. These strange steeds are tethered to the coracle with seaweed fronds, like horses pulling a carriage. \"Climb aboard,\" says the shark in a sharp voice. \"We'll take you to Neptune's harbour.\"\n\nThe dolphin has a softer tone: \"But beware, as you must find your own vessel for the journey back.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Board the coracle", 233));
        Choices.push_back(Choice::Base("Refuse", 203));

        Controls = Story::Controls::STANDARD;
    }
};

class Story281 : public Story::Base
{
public:
    Story281()
    {
        ID = 281;

        Text = "Despite Grimes' earnest entreaties, you decide to call upon the power of Leviathan. The decision alone is enough. As you raise the hand bearing the ring -- even before you can speak the serpent's name -- you sense something dark and monstrous rising from the illimitable depths. Waves rear like mountains to blot out the sky. The wind shrieks in fear and flees in all directions.\n\nLeviathan rises out of the water. His body is a tower of bronze scales, each the size of a shield, green with brine stain. Phosphorescent venom drips from his gaping jaws in a torrent of liquid white fire. Dank poisonous vapour curls up from the black caves of his nostrils.\n\nYou realise your mistake at once -- you could never hope to command an entity so fearsome. As you cower in the boat, you see one more thing that strikes you full of mortal terror; on the face of the colossus there is now a look of fear. Even he will be hard-pressed to stand against Leviathan, and in their titanic battle four tiny mortals will be trodden underfoot, sent plunging into the ocean depths. You have brought your own doom upon you.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story282 : public Story::Base
{
public:
    Story282()
    {
        ID = 282;

        Text = "The instant you place the HELMET on your brow, your mind becomes a maelstrom of bloody battle-images. All manner of martial tricks, tactics and harsh killing-lore are now second nature to you. You are as tough, wily and fearless as any Spartan warrior.\n\nFor the duration of just one battle you acquire the [BRAWLING] and [SWORDPLAY] skills.\n\nDon't give up the ship!";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        player.TemporarySkills.clear();

        if (!Character::HAS_SKILL(player, Skill::Type::BRAWLING))
        {
            player.TemporarySkills.push_back(Skill::BRAWLING);
        }

        if (!Character::HAS_SKILL(player, Skill::Type::SWORDPLAY))
        {
            player.TemporarySkills.push_back(Skill::SWORDPLAY);
        }
    }

    int Continue(Character::Base &player) { return 73; }
};

class Story283 : public Story::Base
{
public:
    Story283()
    {
        ID = 283;

        Image = "images/filler3-green.png";

        Text = "The words have hardly left your lips when he gives an exultant shriek of laughter and launches himself up the side, scaling towards the rail with the speed of a spider running up a wall. Behind him, the two oarsmen throw off their cowls and also begin to climb. You see faces pale as candlewax gleaming in the lantern-light, and long sharp teeth bared in naked bloodlust.\n\nThen an even more horrific sight at last draws a cry of fear from your lips, as a dozen other figures erupt out of the black water and start to make their way up the side of the ship. These are more grotesque than the first three, with ravaged faces of bare bone and grave-mould- Barnacles crust their tarnished breastplates and their once-fine coats hang about them like tattered shrouds.\n\n\"All hands on deck!\" you manage to call out, at last freeing yourself from the paralysis of terror as the first of the monsters reaches the rail. \"We're being boarded by vampires!\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 321; }
};

class Story284 : public Story::Base
{
public:
    Story284()
    {
        ID = 284;

        Text = "A steady wind arises quickly in answer to your magical summons. It is not so strong -- you dare not tamper with elements too much -- but it is enough for your purposes. The fog swirls nd breaks apart, swiftly dispersing into wispy tendrils. You now have a clear view of both the crippled Rose and, nearer to you, Skarvench's ship the Moon Dog. She is standing at two o'clock off your starboard bow, just within cannon range. You have the weather gauge, meaning that the wind is blowing from behind you towards the Moon Dog -- the ideal position for a sea battle.\n\n\"Now we have a choice,\" says Oakley. \"We can sail in for boarding, or stand off and rake her with our guns. What's it to be skipper?\"\n\nA snap decision is needed.";

        Choices.clear();
        Choices.push_back(Choice::Base("Steer in towards the Moon Dog", 322));
        Choices.push_back(Choice::Base("Unlimber your cannons", 341));

        Controls = Story::Controls::STANDARD;
    }
};

class Story285 : public Story::Base
{
public:
    Story285()
    {
        ID = 285;

        Text = "\"You would match your magic against mine?\" sneers Wild. \"You fool -- didn't the hurricane I summoned give you any inkling of my power?\"\n\n\"It was impressive,\" you admit. \"More than I could achieve at least with any hope of controlling it. But I think you're bluffing, Doctor; I think that hurricane took most of your power. That and the fog. Now we're evenly matched.\"\n\nA web of fiery tendrils shoots from your wand, igniting Wild's robes. As the flames lick up to engulf him, he gives a single scream like nothing you've ever heard from a human throat, then stumbles back against the rail and falls into the sea.\n\n\"Don't congratulate yourself too soon.\" You whirl to see an elderly aristocratic-looking man standing in the companion-way with sword and pistol. It can only be Admiral Calidor, commander of the Queen's navy. \"Well, don't just stand there,\" he continues. \"I heard enough to guess you're on our side, whoever you are; now's your chance to prove it. Stand by to repel boarders!\"\n\nHe gestures, and you look up to see Skarvench and his pirates sliding down out of the mist like spiders on their webs. Marines rush up on deck to give battle. Calidor himself closes with the lumbering figure of Porbuck.\n\nThe fight rages all around you, but you stride oblivious across the deck. There is only one foe you must face -- and now you see him, looming out of the eerie mist, and all your hatred wells up in a mighty roar: \"Skarvench\"\n\n\"Ah, mate,\" he says with a strange smile. \"Ready to die, are ye?\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 171; }
};

class Story286 : public Story::Base
{
public:
    Story286()
    {
        ID = 286;

        Text = "Your SWORD flashes out, taking his life before he knows it. With hands pressed to his pierced heart, mouth opening and closing like a fish out of water, he sinks to the floor and expires in silence. You waste no pity on him. He has done the evil Skarvench's every bidding without a qualm for all these years, happy to collude in wickedness even if not bold enough to do wicked deeds of his own. You turn away from the body and hurry up on deck.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 172; }
};

class Story287 : public Story::Base
{
public:
    Story287()
    {
        ID = 287;

        Text = "You decide to let Blutz eat the crabs. He is the least sturdy of the four of you, and even a meagre meal will help keep his spirits up. As Blutz tucks in, deftly cracking the shells on a rock and shredding the tough flesh with his teeth, Grimes catches your eye and nods sagely. He agrees with your judgement.";

        Choices.clear();
        Choices.push_back(Choice::Base("Go exploring", 211));
        Choices.push_back(Choice::Base("Get back in the boat and head on to the next island", 116));

        Controls = Story::Controls::STANDARD;
    }
};

class Story288 : public Story::Base
{
public:
    std::string PreText = "";

    Story288()
    {
        ID = 288;

        Image = "images/filler3-green.png";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "You spend nearly a week on the island, sustained by nature's bounty and an ample supply of fresh rainwater draining down off the slopes of the volcano.\n\n";

        if (Character::VERIFY_ANY_SKILLS(player, {Skill::Type::WILDERNESS_LORE, Skill::Type::MARKSMANSHIP}))
        {
            if (Character::VERIFY_SKILL(player, Skill::Type::WILDERNESS_LORE))
            {
                PreText += "[WILDERNESS LORE] ";
            }

            if (Character::VERIFY_SKILL(player, Skill::Type::MARKSMANSHIP))
            {
                PreText += "[MARKSMANSHIP] ";
            }

            PreText += "You supplement your diet with game and make a full recovery.";

            player.Life = player.MAX_LIFE_LIMIT;
        }
        else
        {
            PreText += "You are not able to supplement your diet with game but you still subsist comfortably enough as you are by gathering nuts and berries.";

            Character::GAIN_LIFE(player, 1);
        }

        PreText += "\n\nAt last, by common consent, you decide if it is time to move on. The volcano is producing occasional ominous growls from deep in the earth, and you have no desire to still be here when it finally erupts. Climbing aboard your boat, the four of you resume your arduous voyage towards Port Leshand.";

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 135; }
};

class Story289 : public Story::Base
{
public:
    Story289()
    {
        ID = 289;

        Image = "images/map-jollyboat-green.png";

        Text = "In the glimmering predawn, as your little boat drifts gently on across the still ocean, you have your first chance to take stock of your situation. You must judge every factor with great care from now on: even the smallest mistake could spell disaster, and you will need every scrap of luck and cleverness if you are to make it to civilized lands alive.\n\nFirst, your companions on the voyage. Grimes, lanky and lantern-jawed, is a lugubrious fellow but despite his habit of expecting the worst he is a good man to have aboard, being neither timid nor quarrelsome. Oakley is tough and smart but abrasive -- a possible challenge to your leadership, if you fail to assert yourself. All the same, you have been in enough tough scrapes together in the past to know that you can count on him too. Blutz is the weak link of the group; a timid, clumsy little scuttlebutt of a man. But you know that he can be clever and resourceful when he has to be.\n\nThe three of them look at you and Oakley says, \"Well, where shall we point our prow?\"\n\n(You can take look at the map 'The Voyage of the Jollyboat' on the MAP SCREEN)";

        Choices.clear();
        Choices.push_back(Choice::Base("Steer straight for Port Leshand", 2));
        Choices.push_back(Choice::Base("Steer a course through the Smoking Islands", 21));
        Choices.push_back(Choice::Base("Steer south of the islands, keeping well clear of them", 40));

        Controls = Story::Controls::STANDARD;
    }
};

class Story290 : public Story::Base
{
public:
    std::string PreText = "";

    Story290()
    {
        ID = 290;

        Choices.clear();
        Choices.push_back(Choice::Base("Try a straightforward punch", 271));
        Choices.push_back(Choice::Base("... or a body slam", 309));
        Choices.push_back(Choice::Base("Use [SPELLS]", 384, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("Use [MARKSMANSHIP]", 317, Skill::Type::MARKSMANSHIP));
        Choices.push_back(Choice::Base("Maybe you should just beat a hasty retreat", 5));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Closing with your foe, you seize her at wrist and elbow and try to bend her arm around behind her back. You have used the selfsame hold on some of the nastiest bullies to sail the seven seas, and you remember one fellow in particular -- a scar-faced gorilla called Gutshredder Turnbull -- weeping like a baby as he begged you to let go.\n\nAgainst Ejada, the armlock is useless. You might as well be trying to break the branch of an oak tree. After a brief tussle, she flings you to the ground with a painful jolt. She gives a scornful laugh.\n\nYou LOSE 2 Life Points.";

        Character::GAIN_LIFE(player, -2);

        if (player.Life > 0)
        {
            PreText += "\n\nYou leap ready to renew the attack. But how can you overcome a foe with seemingly limitless strength?";
        }

        Text = PreText.c_str();
    }
};

class Story291 : public Story::Base
{
public:
    std::string PreText = "";

    Story291()
    {
        ID = 291;

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        PreText = "They will accept any of the following: a SWORD, a PISTOL, a MAGIC WAND, a MAGIC AMULET, a SHIP IN A BOTTLE, a CONCH-SHELL HORN, a BAT-SHAPED TALISMAN, or a BLACK KITE.";

        auto count = 0;

        std::vector<Item::Base> bribe = {Item::SWORD, Item::PISTOL, Item::MAGIC_WAND, Item::MAGIC_AMULET, Item::SHIP_IN_BOTTLE, Item::CONCH_SHELL_HORN, Item::BAT_SHAPED_TALISMAN, Item::BLACK_KITE};

        for (auto i = 0; i < bribe.size(); i++)
        {
            count += Item::COUNT_TYPES(player.Items, bribe[i].Type);
        }

        if (count >= 1)
        {
            Choices.push_back(Choice::Base("Give them a gift", 272, Choice::Type::BRIBE, bribe, 1));
        }
        else
        {
            PreText += "\n\nBut you are unable to part with such items.";
        }

        Choices.push_back(Choice::Base("You cannot or refuse to give anything: Their mood starts to turn nasty", 215));

        Text = PreText.c_str();
    }
};

class Story292 : public Story::Base
{
public:
    Story292()
    {
        ID = 292;

        Text = "A dim flicker of memory makes you shudder. Watching the tall black sails against the sunset, you are reminded of an ancient mariner's legend that tells of the doomed Captain Mandrigard, master of a vessel called the Larnassos. After stealing the sacred treasures of the Temple of Dionysus, he was cursed never to set foot on shore again \"while his hand was still sullied with theft.\". According to myth, his crew found some way to escape the curse but Mandrigard himself never did, and he still sails the seven seas to this day. Anyone who sets foot aboard the Larnassos now is cursed to stay on for ever.";

        Choices.clear();
        Choices.push_back(Choice::Base("Hail the ship", 311));
        Choices.push_back(Choice::Base("Let her go by in the dusk", 330));

        Controls = Story::Controls::STANDARD;
    }
};

class Story293 : public Story::Base
{
public:
    Story293()
    {
        ID = 293;

        Image = "images/filler1-green.png";

        Text = "You have soon gathered a small pile of items that catch your eye. These include a CONCH-SHELL HORN, an ancient BRONZE HELMET, a ring in the form of a dragon, a fan with the shape and colouring of a thunder cloud.\n\n\"Yes, any of this lot could well be magical,\" agrees Oakley, scrutinizing your selection. Like you, he has the practiced adventurer's instinct for such things. \"How many shall we take?\"\n\nAfter a brief conference, you decide to take only two items. By pirates' code you should not steal from the captain of a vessel that has shown you hospitality. But weighed against that is the fact that Mandrigard knowingly lured you into the same curse that has trapped him here.\n\n\"Sometimes I hanker for the old-fashioned days of piracy,\" complains Blutz, \"when we'd count plain wealth as treasure and didn't look for a patina of magic to tart it up.\" He is looking longingly at a DIAMOND the size of a walnut which lies on the captain's table.\n\nSo the items to choose from are: a DIAMOND, a CONCH-SHELL HORN, a BRONZE HELMET, a DRAGON RING, and a THUNDERCLOUD FAN.";

        Bye = "Then you hurry out of the cabin before Mandrigard wakes up";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Take = {Item::DIAMOND, Item::CONCH_SHELL_HORN, Item::BRONZE_HELMET, Item::DRAGON_RING, Item::THUNDERCLOUD_FAN};

        Limit = 2;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::FOLKLORE))
        {
            return 139;
        }
        else
        {
            return 217;
        }
    }
};

class Story294 : public Story::Base
{
public:
    Story294()
    {
        ID = 294;

        Text = "You row nearer, watching as the raft and its occupant slowly take shape out of the gloom. He is an old man, thin and wizened as a bent stick, whose eyes shine with a pale moon-coloured light. Dark crusted stains in his beard make you wonder if he has resorted to drinking salt water, until you notice the full bucket and long box of provisions beside him on the raft.\n\nHis mouth cracks open in a long-toothed cackle. \"The fates be praised! Here am I adrift, poor old Timmy Mortice, an' here come four stalwarts to rescue me. 'Tis a miracle! Come aboard and share my water, mates, an' let's swap our stories.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Start by telling him how you come be in your present state", 29));
        Choices.push_back(Choice::Base("Begin by asking him about himself", 48));

        Controls = Story::Controls::STANDARD;
    }
};

class Story295 : public Story::Base
{
public:
    Story295()
    {
        ID = 295;

        Text = "The box is filled with yellow bones and tatters of wet rag. Choking back your disgust, you reach in to rummage amongst these until you discover a few items of treasure. There is a BAT-SHAPED TALISMAN, a RUSTY SWORD, and a DIAMOND almost as big as a walnut.\n\nBlutz is still staring around nervously. \"I don't get it,\" he says. \"What happened to the old codger?\"\n\nOakley lifts the skull out of the box and gazes at it for a moment, then throws it far off into the darkness. You see it gleam in the moonlight, then there is a splash. \"Gone for good, I reckon,\" says Oakley. \"Let's help ourselves to some of the food he had.\"\n\nGrimes shakes his head. \"It's gone off. The water too.\"\n\nYou push past him, but he is right. Mortice's provisions are now rancid and mould-covered, showing every sign of being months old. The water in the barrel is no more than stagnant green murk.\n\nReturning to your boat, you jettison the raft and row a good distance before finally settling down for the night.\n\n\"We're going to have to pray a ship comes along tomorrow,\" says Oakley as you drift off to sleep. \"I don't think we can hold out much longer.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Take = {Item::BAT_SHAPED_TALISMAN, Item::RUSTY_SWORD, Item::DIAMOND};

        Limit = 3;
    }

    int Continue(Character::Base &player) { return 332; }
};

class Story296 : public Story::Base
{
public:
    std::string PreText = "";

    Story296()
    {
        ID = 296;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Inspired by your example, your friends lay about them with gusto as the natives charge to the attack with spears and clubs. The fighting rages fiercely and, although sicked at the need for bloodshed, you soon realise that it must continue until you have defeated or driven off all the natives. If you tried to retreat down the ladder while there were still natives on the clifftops, they could easily pick you off by dropping rocks.\n\nAfter a short and brutal exchange of blows, most of the natives lie senseless and the remainder are fleeing in terror.\n\n";

        auto DAMAGE = -4;

        if (Character::VERIFY_SKILL_ANY(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::RUSTY_SWORD, Item::Type::CLEAVER, Item::Type::SHARKS_TOOTH_SWORD}))
        {
            DAMAGE = -2;

            PreText += "[SWORDPLAY] ";
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Point(s).";

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 116; }
};

class Story297 : public Story::Base
{
public:
    Story297()
    {
        ID = 297;

        Text = "You settle on a cheap dive close to the shanty town as the best place to find news of Skarvench. There, under a luridly painted sign depicting a man hung upside-down, the evil pirate captain has whiled away many an hour ashore in gambling and rum-soaked revelry.\n\nRaucous laughter issues through the open door, but the whole tavern goes silent for a moment as you step inside. Dozens of ugly faces turn to stare as you saunter across the sawdust-strewn planks of the floor.\n\n\"Like an angle passing,\" you remark to your friends, recalling the old superstition.\n\n\"Aye,\" mutters Grimes under his breath, \"the Angel of Death. Let's scarper, mates. This is no place to loiter in. It's a den of vicious sea-rats.\"\n\nSlowly the babble of drunken chatter returns, but many sullen eyes remain fixed on you.";

        Choices.clear();
        Choices.push_back(Choice::Base("Stay here despite the danger", 146));
        Choices.push_back(Choice::Base("Leave to seek out rumours concerning El Draque", 183));
        Choices.push_back(Choice::Base("Seek out rumours concerning Queen Titania", 221));
        Choices.push_back(Choice::Base("You done listening to rumours", 392));

        Controls = Story::Controls::STANDARD;
    }
};

class Story298 : public Story::Base
{
public:
    Story298()
    {
        ID = 298;

        Text = "There is nothing you can do to evade capture. Dragged back in hemp bonds to the Belle Dame, you are hauled up on deck and tossed like sacrificial offerings in front of Skarvench. In the stark moonlight, his black beard and white face make him look the very picture of Satan himself. \"Bilge-rotten blasted fiend!\" you yell at him. \"You can't force honest men to live a villain's life!\"\n\nHe scowls and spits. \"Aye, you're right mate. Honest toil's what you four thrive on, ain't it? You aren't buccaneer material -- I see that now. Well, I'll give you honest toil- How'd ye like scrape the barnacles off the hull, for starters?\"\n\nLashed to ropes, the four of you are swung overboard and dragged back and forth along the keel of the ship. Soon the flesh is ragged on your bruised bones, and brine floods into your anguished lungs. Darkness closes over you for the last time. It is the end.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story299 : public Story::Base
{
public:
    Story299()
    {
        ID = 299;

        Text = "How many DIAMONDs are you willing to spend to buy a ship?";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        Choices.push_back(Choice::Base("Spend 3 DIAMONDs", 337, Choice::Type::PAY_WITH, {Item::DIAMOND}, 3));
        Choices.push_back(Choice::Base("Spend 2 DIAMONDs", 356, Choice::Type::PAY_WITH, {Item::DIAMOND}, 2));

        if (Item::COUNT_TYPES(player.Items, Item::Type::DIAMOND) < 1)
        {
            Choices.push_back(Choice::Base("You refuse or cannot pay", 375));
        }
        else
        {
            Choices.push_back(Choice::Base("Spend 1 DIAMOND", 375, Choice::Type::PAY_WITH, {Item::DIAMOND}, 1));
        }
    }
};

class Story300 : public Story::Base
{
public:
    Story300()
    {
        ID = 300;

        Text = "Somehow you have to get a bigger ship, as your current one is no match for Skarvench's heavily-armed galleon. Sitting in your cabin aboard the LADY OF SHALOTT, you mull over the options open to you.";

        Choices.clear();
        Choices.push_back(Choice::Base("(Raven) Look for El Draque's treasure", 319, Codeword::Type::RAVEN));
        Choices.push_back(Choice::Base("(August) Sail in search of the ship frozen in ice", 338, Codeword::Type::AUGUST));
        Choices.push_back(Choice::Base("Make some money from plain dishonest piracy", 357));

        Controls = Story::Controls::STANDARD;
    }
};

class Story301 : public Story::Base
{
public:
    Story301()
    {
        ID = 301;

        Text = "On returning to Port Selenice you go straight to Master Kemp's shipyard, where your treasure secures you a fair-sized galleon in place of your small sloop. You check her out from stern to stern, and despite finding a few faults you have a good instinct about her. Patting one of the cannons, you say. \"This is the ship for us. \"What's she called, Master Kemp?\"\n\n\"My friend,\" he replies, \"she is the SHIVERED TIMBER.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::TAKE_SHIP(player, Ship::SHIVERED_TIMBER);
    }

    int Continue(Character::Base &player) { return 184; }
};

class Story302 : public Story::Base
{
public:
    Story302()
    {
        ID = 302;

        Text = "He looks you long and hard in the eyes, then turns away with a snarl and a muttered oath. \"Davy Jones's teeth! This one's will is too strong.\" He glances back up at you, but the earlier mask of pleasantry is now entirely peeled away to reveal a look of pure murderous hatred. \"Very well. We cannot come up uninvited. But be warned, you frail thing of daylight and warm blood: do not touch my treasure. For if you do, I promise you a curse that will harry you into the grave and haunt you even beyond it. This I swear, or my name's not El Draque\"\n\nThey melt away into the mist -- the tall figure, the boat, and the two oarsmen, all faded to nothing. By dawn you're not even sure it ever happened. But when you start to order the treasure brought aboard, you remember El Draque's parting words. Maybe it was a dream -- but can't a ghost in a dream lay curses just as easily?";

        Choices.clear();
        Choices.push_back(Choice::Base("Load the treasure aboard first before sailing", 16, Choice::Type::GET_CODEWORD, Codeword::Type::MALEFIC));
        Choices.push_back(Choice::Base("Sail without taking the treasure", 396));

        Controls = Story::Controls::STANDARD;
    }
};

class Story303 : public Story::Base
{
public:
    Story303()
    {
        ID = 303;

        Text = "\"The Rose is at the centre of Skarvench's web,\" you realise. \"That's where we'll find him.\"\n\nYou cannot safely take your ship on into the fog. Instead, you take a small party in one of the cutters and begin to row as quickly as possible towards the centre of the fogbank. \"It seems to be issuing from the Rose herself,\" says Oakley. \"And I've never seen fog so thick. I can barely see Blutz sitting in the stern back there, and he's not easy to miss!\"\n\n\"Stow that personal talk, if you please, Mister Oakley!\" protests Blutz from the back of the boat. Despite the grim danger you are facing, every man in the cutter allows himself a chuckle.\n\n\"Mister Blutz's girth is entirely a natural phenomenon,\" says the ever sober-minded Grimes. \"I can't say the same for this fog. And moonlight is returning: the Moon Dog will be airborne again by now. Let's hope we're in time.\"\n\nThe Rose looms ahead. You catch hold of her access ladder and secure your cutter, then lead the way up.";

        Choices.clear();
        Choices.push_back(Choice::Base("Use the BRONZE HELMET", 190, {Item::BRONZE_HELMET}));
        Choices.push_back(Choice::Base("Go without wearing the BRONZE HELMET", 209));

        Controls = Story::Controls::STANDARD;
    }
};

class Story304 : public Story::Base
{
public:
    Story304()
    {
        ID = 304;

        Text = "A shot cracks out through the mist-shrouded deck, splintering the wand in Wild's hand. You and he both turn, equally amazed, as a tall figure steps out of the companion-way hatch. He holds a smoking pistol, and from his aristocratic manner you guess he must be Admiral Lord Calidor, commander of the Queen's navy. \"Wild,\" he says curtly, \"your twig's split.\" He must know he's just made the luckiest shot in history, but with typical Gloriannic aplomb he shows no sign of it.\n\n\"Admiral,\" begins Wild in a wheedling voice, \"this pirate villain --\"\n\n\"Forget it, Wild,\" says Calidor, reloading his pistol. \"I'm wise to your game.\" A squad of marines pour past him onto the deck. \"Sergeant, Dr Wild is to be placed under arrest on a charge of high treason.\"\n\nSudden Wild's facade of genteel urbanity crumbles. Howling in rage, he whips out a dagger and throws it. It catches you in the arm and you stagger back with a grunt of surprise rather than pain.\n\nYou LOSE 1 Life Point.";

        Bye = "Wild turns and leaps overboard into the leas. Whether it is suicide or whether he has a plan of escape, you may never know. You have more pressing concerns. Swarming down the rope from the Moon Dog, baying like phantoms taking human form out of the mist, come Skarvench and his men. Calidor and his marines stand ready for a battle-royal, but you press ahead of them, lunging towards Skarvench as he lands on the deck. Now you will settle your feud once and for all.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -1);
    }

    int Continue(Character::Base &player) { return 171; }
};

class Story305 : public Story::Base
{
public:
    Story305()
    {
        ID = 305;

        Text = "You step forward smartly and take him by the elbow. \"Ah, Mister Fitzhugh,\" you say. \"Come along, the cap'n wants us on deck. We're to steer a course for Glorianne.\"\n\nHe starts to follow you up the companion-way steps, but casts a dubious look back towards Skarvench's cabin. \"Eh? Glorianne? But that's a journey of months! He said nothing to me of this.\"\n\nYou shrug. \"We've got to get the Queen, haven't we?\"\n\nFitzhugh hesitates. He's not sure what to think. As he starts back towards Skarvench's cabin to check your story, you settle the matter by coshing him over the back of the neck. He slumps to the floor, and you hurry away to join your comrades.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 172; }
};

class Story306 : public Story::Base
{
public:
    Story306()
    {
        ID = 306;

        Text = "You need to venture only a little way into the jungle to collect armfuls of fruit and nuts. You also drink from a freshwater stream until your bellies are stretched like topgallants in a high wind. \"Phew!\" says Oakley, rolling back on the grass. \"That was the sweetest drop I ever tasted, mates. But now I reckon we ought to be getting on our way.\"\n\nYou RECEIVE three meals' worth of PROVISIONS.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_ITEMS(player, {Item::PROVISIONS, Item::PROVISIONS, Item::PROVISIONS});
    }

    int Continue(Character::Base &player) { return 344; }
};

class Story307 : public Story::Base
{
public:
    Story307()
    {
        ID = 307;

        Text = "Clouds cover the sharp silver horns of the moon as, with muffled oars, you pull out of the cove and row beneath the black bows of Skarvench's anchored vessel.\n\n\"Like tiptoeing past the face of a sleeping dragon,\" whispers Oakley with characteristic grim humour.\n\n\"Oh no,\" says Blutz suddenly, \"I'm going to -- ACHOOOO!\"\n\nSilently cursing this stroke of bad luck, the four of you crouch low in the boat and pray that the lookout on deck didn't hear the sneeze. But those prayers go unheeded. You can see the man's face appear at the rail, peering out into the darkness. A glance up at the sky assures you that fate really has no mercy: the moon is about to emerge from behind a cloud. When it does, the lookout cannot miss spotting you.";

        Choices.clear();
        Choices.push_back(Choice::Base("[SWORDPLAY] Try something", 364, Choice::Type::SKILL_ANY, Skill::Type::SWORDPLAY, {Item::SWORD, Item::RUSTY_SWORD, Item::CLEAVER, Item::SHARKS_TOOTH_SWORD}));
        Choices.push_back(Choice::Base("Otherwise", 383));

        Controls = Story::Controls::STANDARD;
    }
};

class Story308 : public Story::Base
{
public:
    Story308()
    {
        ID = 308;

        Text = "With the help of others you put together a makeshift raft, even rigging a rough sail from interwoven palm leaves. You have to work fast, knowing that you have only the space of a single night, and you are not sure the raft will hold together long enough for you to reach the next island.";

        Choices.clear();
        Choices.push_back(Choice::Base("Put to sea on the raft", 137));
        Choices.push_back(Choice::Base("Hide in the jungle", 346));
        Choices.push_back(Choice::Base("Go to the witch's place at dawn", 327));

        Controls = Story::Controls::STANDARD;
    }
};

class Story309 : public Story::Base
{
public:
    Story309()
    {
        ID = 309;

        Text = "Ejada twists in your grasp, fighting back with a strength that seems incredible for a person with her slimly supple frame. It is like holding on a python. But at last you succeed in getting her in a firm grip and dragging her off her feet. As you lift her up above your head, you are surprised to notice green roots trailing from the soles of her bare feet. Now that those roots have been tugged out of the ground they are withering fast -- and at the same time you can feel Ejada getting weaker. Her mightily pounding blows fade to soft slaps, her roars of anger become faint moans as she cries for quarter.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 157; }
};

class Story310 : public Story::Base
{
public:
    std::string PreText = "";

    Story310()
    {
        ID = 310;

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        PreText = "You must give the chief one of these items: a SWORD, a PISTOL, a MAGIC WAND, a MAGIC AMULET, a SHIP IN A BOTTLE, a CONCH-SHELL HORN, a BAT-SHAPED TALISMAN, a BLACK KITE or all your MONEY.";

        auto count = 0;

        std::vector<Item::Base> bribe = {Item::SWORD, Item::PISTOL, Item::MAGIC_WAND, Item::MAGIC_AMULET, Item::CONCH_SHELL_HORN, Item::BAT_SHAPED_TALISMAN, Item::BLACK_KITE};

        for (auto i = 0; i < bribe.size(); i++)
        {
            count += Item::COUNT_TYPES(player.Items, bribe[i].Type);
        }

        if (count >= 1)
        {
            Choices.push_back(Choice::Base("Give the chief a gift", -310, Choice::Type::BRIBE, bribe, 1));
        }
        else
        {
            PreText += "\n\nBut you are unable to part with such items.";
        }

        if (player.Money > 0)
        {
            Choices.push_back(Choice::Base("Give him ALL of Your MONEY", -310, Choice::Type::LOSE_MONEY, player.Money));
        }

        Choices.push_back(Choice::Base("You cannot or refuse to give anything: You must choose again", 272));

        Text = PreText.c_str();
    }
};

class Event310 : public Story::Base
{
public:
    Event310()
    {
        Title = "Down Among the Dead Men: 310";

        ID = -310;

        Text = "Then, with two well-stocked canoes accompanying you, you strike south from Pandanus Island. After only a few days, you are delighted to see a ship appear on the eastern horizon. Gradually taking shape out of the morning haze, she draws closer until you can make out her comely gilded figurehead and the name painted across her bows: the Jewel of Heaven. Grimes is more interested in the colours she's flying. \"A Gloriannic ship, by God's grace! We're saved!\"\n\nBidding farewell to the islanders who have brought you this far, you are grateful to be taken aboard the Jewel of Heaven. Even so, Blutz speaks for you all as he watches your little craft, now abandoned, go drifting off across the swell. \"She brought us through it against all the odds, mates. You can never say more for any vessel.\"\n\nAnd, to the bewilderment of the sailors, you raise your arms to salute the ramshackle craft bobbing off into the distance.";

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 370; }
};

class Story311 : public Story::Base
{
public:
    Story311()
    {
        ID = 311;

        Image = "images/larnassos-green.png";

        Text = "The ship's prow looms overhead, her tall sails standing like the shadows of midnight against the greying sky. After a long moment during which you begin to fear she is but a drifting ghost-ship, a figure appears at the rail and calls down to you, \"Come board, strangers.\"\n\nA rope ladder is flung down. You look at your companions. They seem to share your unease, but what choice is there? If you stay in the foundering jollyboat your chance of survival is scant. Grabbing the saying ladder, you ascend until you are level with the rail. The vessel's captain is standing there. He holds out his hand to help you aboard, but something in his eager haunted gaze makes you flinch.\n\n\"Come on deck!\" he insists. \"Here's my hand.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("[AGILITY] Try some trickery", 353, Skill::Type::AGILITY));
        Choices.push_back(Choice::Base("Go aboard", 422));
        Choices.push_back(Choice::Base("Climb back down to the jollyboat and shove off", 330));

        Controls = Story::Controls::STANDARD;
    }
};

class Story312 : public Story::Base
{
public:
    Story312()
    {
        ID = 312;

        Image = "images/filler1-green.png";

        Text = "A look of grim resignation comes into your eyes. You lift your wand to the sky as though about to conduct a symphony of the elements. The others see this and take a step back, suddenly alarmed at the aura of power surrounding their friend.\"Are are you going to do?\" asks Oakley.\n\n\"We're under a curse,\" you tell him simply. \"I mean to call the one who laid the curse.\"\n\nSo saying, you begin to chant the words of a summoning spell. Cold green light glows at the tip of your wand. As your incantation grows in strength, the heavens flash and growl in stern reply, discharging mighty thunderbolts through the turbid clouds. The masts are limned in a sharp unearthly glare. The deck pitches wildly as the ship is swirled and swung by a gale that dredges up waves thirty feet high. Roaring winds blast the rain down onto you in freezing sheets as the full fury of the storm writhes within the fetters of your spell. A pillar of lightning drops into the sea less than a cannon-shot away, sizzling white fire blazing through the wet darkness, prompting looks of panic on the faces of your friends.\n\n\"For God's sake, stop!\" screams Oakley above the noise of the storm. \"You're brining the wrath of Heaven down on us.\"\n\nSuddenly the wind drops. The thunderclouds, piled up like black fortresses in the sky, quieten their rumbling. The rain falls as before in a light gossamer spray. No not as before; this is not rain. It has a sweet heady taste and stains the deck with mauve rivulets. Blutz tilts up his face to the sky and gives a cry of wonder: \"Lads, 'tis raining wine!\"\n\nA throaty feral roar makes you whirl. Across the deck you behold an imposing robed figure, standing in an ivy-twined chariot drawn by four giant panthers. He has skin like gold and eyes of jewelled brilliance, and ringlets of blue hair frame his broad face. It was the panthers' roar you heard, but ow the figure speaks, and his voice is no less wild or daunting: \"You summoned me.\"\n\nYou drop to your knees, glancing back over your shoulder to hiss at the others. \"Bow down as if he was the father of all the ship's captains - and sharpish, shipmates. This is the god Dionysus.\"";

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 59; }
};

class Story313 : public Story::Base
{
public:
    Story313()
    {
        ID = 313;

        Text = "Muffling your oars, you row off under the cover of darkness. Even so, the man on the raft hears you. \"Avast there!\" he cries hoarsely. \"Don't leave me! Come back!\"\n\nAt long last these pleas are swallowed up by distance. You look around the boat. Each of your companions has a glum shamefaced look. \"What could we have done for him, anyhow?\" says Oakley.\n\nBlutz nods readily at this. \"That's right. He's probably no worse off than we are. The current is making most of our headway, not rowing -- a raft's almost as good as a boat in these waters.\"\n\"And in any case we had nothing to share with him but misfortune,\" mutters Grimes.\n\nYou too feel a twinge of regret, but not because you have any pity for the man on the raft. It is only that you just realised he might have had food and drink that he could share with the four of you.\"";

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 332; }
};

class Story314 : public Story::Base
{
public:
    std::string PreText = "";

    Story314()
    {
        ID = 314;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "Mortice's nails are sharp, ragged, and caked with grave-clod. He rakes them across your throat, drawing a spurt of blood.\n\nYou LOSE 2 Life Points.";

        Character::GAIN_LIFE(player, -2);

        if (player.Life > 0)
        {
            PreText += "\n\nHe seizes you and hefts you off your feet. You are helpless in his grasp; he has the strength of six men. Giving vent to a spine-chilling roar, he swings you over his head and throws you into the sea.\n\nOakley has lost no time in cutting the rope that moored the raft to the jollyboat. Blutz meanwhile has grabbed one of the oars and now thrusts it towards you. Floundering to the surface, you spit out a mouthful of seawater and stretch your hands towards the oar.";

            if (Character::VERIFY_SKILL(player, Skill::Type::SEAFARING))
            {
                PreText += "\n\n[SEAFARING] You get back aboard the jollyboat without letting go of your SWORD.";
            }
            else
            {
                PreText += "\n\nBut you are not that good a swimmer and are forced to drop the SWORD to save your life.";

                Character::LOSE_ITEMS(player, {Item::Type::SWORD});
            }
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 276; }
};

class Story315 : public Story::Base
{
public:
    Story315()
    {
        ID = 315;

        Text = "You draw the fan from your sleeve and wave it. Skarvench stares, a cruel laugh shivering his tall frame. \"Showin' yourself for the limp-wrist you are, eh, ye slippery swab? Or is it that you're finding things gettin' too hot for you? By Garn, I'll give you hot. I'll roast your gizzard before the sun rises on another day!\"\n\nYou lower the fan. There is a change in the air: a sudden taste of something on the wind. Skarvench senses it too. His seafaring instincts are second to none, and recognition freezes his ugly smirk. He turns, looking out to sea, sniffing the breeze. \"Hurricane!\" he whispers, aghast.\n\nThe sky turns from blue to a dingy sulphurous yellow, bruised by livid blotches of cloud. Out to sea, the waves froth and churn as a storm wind comes sweeping in like a giant's fist. You see it strike the Belle Dame where she lies at anchor, snapping her sails taut and bucking her to and fro like a toy.\n\n\"To the boat!\" screams Skarvench. \"This wind will reef us if we don't put out to sea.\" As he and his men scurry to their rowboat, he pauses just long enough to turn and shake his fist. \"You'll be sorry! Aye, you'll beg for death afore I'm through with ye!\"\n\nHis words are drowned out by the wind. As the storm sweeps on, bearing the Belle before it, you notice that the THUNDERCLOAD FAN has vanished. Deciding that you had better be long gone by the time Skarvench returns here, you put out to sea in your ramshackle vessel.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::LOSE_ITEMS(player, {Item::Type::THUNDERCLOUD_FAN});
    }

    int Continue(Character::Base &player) { return 177; }
};

class Story316 : public Story::Base
{
public:
    Story316()
    {
        ID = 316;

        Text = "Doctor Scriptor chuckles softly to himself as he inspects the HORN. You cannot help thinking that he really is a rather weird old cove, but certainly no one can beat him when it comes to identifying magic treasures.\n\n\"Oh ho, this is a fine prize,\" he declares. \"The Horn of Poseidon. Go down to the shore and blow it, so the tale goes, and a phantom boat will arise out of the waves and take you to the god's gate. But it also said that no mortal can see or touch the key that will open that gate. Now, as to my fee...\n\nHe demands a doubloon for what he's told you so far. Alternatively you can also sell him the HORN for 20 doubloons.";

        Choices.clear();
        Choices.push_back(Choice::Base("Pay Scriptor 1 doubloon", -316, Choice::Type::LOSE_MONEY, 1));
        Choices.push_back(Choice::Base("Sell him the CONCH-SHELL HORN", -316, Choice::Type::SELL, {Item::CONCH_SHELL_HORN}, 20));
        Choices.push_back(Choice::Base("You refuse to pay", 392));

        Controls = Story::Controls::STANDARD;
    }
};

class Event316 : public Story::Base
{
public:
    Event316()
    {
        Title = "Down Among the Dead Men: 316";

        ID = -316;

        Text = "Ask Doctor Scriptor to identify some items for you.";

        Choices.clear();
        Choices.push_back(Choice::Base("Ask to identify the DRAGON RING", 373, {Item::DRAGON_RING}));
        Choices.push_back(Choice::Base("... the BRONZE HELMET", 354, {Item::BRONZE_HELMET}));
        Choices.push_back(Choice::Base("... the BAT-SHAPED TALISMAN", 335, {Item::BAT_SHAPED_TALISMAN}));
        Choices.push_back(Choice::Base("Leave", 392));

        Controls = Story::Controls::STANDARD;
    }
};

class Story317 : public Story::Base
{
public:
    std::string PreText = "";

    Story317()
    {
        ID = 317;

        Image = "images/filler4-green.png";

        Choices.clear();
        Choices.push_back(Choice::Base("Now use [BRAWLING]", 241, Skill::Type::BRAWLING));
        Choices.push_back(Choice::Base("[SPELLS] Use a WAND", 384, Skill::Type::SPELLS));
        Choices.push_back(Choice::Base("Turn and flee", 5));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "The bullet hits Ejada square between the eyes but has no more effect than if you'd fired it into the bole of an oak tree. She winces and says with a confident smile, \"Your best shot? Try mine.\"\n\nShe lunges forward, her fingers driving up to the pit of your stomach with sickening force.\n\n";

        auto DAMAGE = -4;

        if (Character::VERIFY_ITEMS(player, {Item::Type::FEATHER_SHIELD}))
        {
            PreText += "[Item: FEATHER SHIELD] The SHIELD deflects some of the damage. ";

            DAMAGE = -2;
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Point(s)";

        Text = PreText.c_str();
    }
};

class Story318 : public Story::Base
{
public:
    Story318()
    {
        ID = 318;

        Text = "You present the deed of ownership to the harbour master and he leads you along the quay in the direction of a sterling galleon whose proud figurine juts imposingly against the sun. \"Why, she's magnificent!\" says Blutz, starting up the gangplank- \"We'll soon blast Skarvench out of the water in this beauty, shipmates.\"\n\n\"Avast there, ye fat swab!\" snarls a man from the deck, shaking his fist. \"Get off me gangplank afore ye breaks it!\"\n\nThe harbour master had gone striding on ahead. Hearing the commotion, he comes back and tugs your sleeve, pointing to a much smaller vessel at the end of the dockside. \"No,\" he says, \"that is your ship.\"\n\nYou look her up and down without enthusiasm. She sits slightly lopsided in the water, and her few guns show patches of rust. You cannot imagine a small sloop like that tackling Skarvench's mighty galleon.\n\nOakley pats you on the shoulder. \"Buck up, skipper. We'll just have to make the best of her.\"\n\nYou nod in agreement and go aboard to inspect your first command: the LADY OF SHALLOT.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::TAKE_SHIP(player, Ship::LADY_OF_SHALOTT);
    }

    int Continue(Character::Base &player) { return 300; }
};

class Story319 : public Story::Base
{
public:
    Story319()
    {
        ID = 319;

        Text = "With your companions' help, you examine the sea charts and plot your course. Where will you steer?";

        Choices.clear();
        Choices.push_back(Choice::Base("Steer to Tortoise Island", 186));
        Choices.push_back(Choice::Base("To Port Leshand", 339));
        Choices.push_back(Choice::Base("To Crossbones Island", 358));

        Controls = Story::Controls::STANDARD;
    }
};

class Story320 : public Story::Base
{
public:
    Story320()
    {
        ID = 320;

        Text = "Selenice is a veritable haven for pirates, and a large and experienced crew flocks to your cause. Some have heard of your exploits and are eager to join the quest for gold and glory. Others, having learned of your hatred of Skarvench take grim pleasure in joining the battle against him; they, like you, have old scores to settle.\n\nWhile you are signing on the last few crewmen, Blutz comes bustling along the dock full of urgent news. \"I met a bloke in a tavern,\" he manages to pant out, leaning on a stanchion to recover his breath. \"He was employed as a pilot to steer Queen Titania's convoy past the Smoking Islands. He told me the convoy's heading for Port Tudor where they'll sit out the hurricane season.\"\n\n\"The hurricane season!\" scoffs Oakley. \"The hurricane's not due for a month.\"\n\nBlutz shakes his head. \"This bloke I was talking to said they think it's going to hit early this year. Apparently the Queen's wizard cast a horoscope and he's sure of it.\"\n\nGrimes grabs you by the shoulder. \"Skipper, you know what this means. If Skarvench intends to go through with his attack on the Queen's convoy, he'll have to do it before they reach Port Tudor.\"\n\n\"By thunder, you're right! All hands to their posts -- we sail for Port Tudor, and there isn't a moment to lose!\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 138; }
};

class Story321 : public Story::Base
{
public:
    std::string PreText = "";

    Story321()
    {
        ID = 321;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "The vampires come at you in a crazed rush, knowing no fear in their longing to taste your warm rich blood. They feel no pain either, taking the blow of your valiant sailors as though they were stings of gnats. For a moment you feel a stab of hopelessness, shrinking back as the tide of defeat threatens to engulf you, but then you see the grim desperate faces of your brave lads as they battle the monsters. Your passion wells up in a great roar that thunders across the deck. \"This is my ship, by hell and high water, and I'll suffer a thousand deaths before I'll allow a bunch of bloodsucking lubbers to wrest her from me!\"\n\nYour example inspires the crew to fresh efforts and they lay about them with their sabres, chopping bloodless limbs from undead bodies. And still the vampires come, all undaunted by this macabre butchery...\n\n";

        auto DAMAGE = -8;

        if (Character::VERIFY_SKILL_ANY(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::RUSTY_SWORD, Item::Type::CLEAVER, Item::Type::SHARKS_TOOTH_SWORD}))
        {
            DAMAGE = -4;

            PreText += "[SWORDPLAY] ";
        }
        else if (Character::VERIFY_ANY_SKILLS(player, {Skill::Type::BRAWLING, Skill::Type::MARKSMANSHIP}))
        {
            DAMAGE = -6;

            if (Character::VERIFY_SKILL(player, Skill::Type::BRAWLING))
            {
                PreText += "[BRAWLING] ";
            }
            else
            {
                PreText += "[MARKSMANSHIP] ";
            }
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Points.";

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 340; }
};

class Story322 : public Story::Base
{
public:
    Story322()
    {
        ID = 322;

        Text = "Cannonballs whistle out of the night, splintering timber and crushing bones. You see one of your crewmen give a short cry and go sailing out of the rigging to his doom. A shell goes thundering past only paces from where you're standing, but you remain ice cool as you close in on your foe.\n\nYour ship SUFFERS 1 damage.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        Character::DAMAGE_SHIP(player, 1);

        if (Character::CHECK_SHIP(player))
        {
            Choices.push_back(Choice::Base("Stay to windward of the Moon Dog", 379));
            Choices.push_back(Choice::Base("Sail to her lee side", 360));
        }
    }

    int Continue(Character::Base &player) { return 227; }
};

class Story323 : public Story::Base
{
public:
    std::string PreText = "";

    Story323()
    {
        ID = 323;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "\"I don't know how you escaped my bullet,\" growls Skarvench, \"but this time I'm going to make sure of the matter. I'll chop off your head and stick it on a marline-spike to look at as I go to sleep each night!\"\n\nYou give him no answer. Clutching hold of the rope with one hand, you save your strength for the most desperate struggle of your life.\n\n";

        auto DAMAGE = -5;

        if (Character::VERIFY_SKILL(player, Skill::Type::BRAWLING))
        {
            DAMAGE = -3;

            PreText += "[BRAWLING] ";
        }
        else
        {
            if (Character::VERIFY_SKILL_ANY(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::RUSTY_SWORD, Item::Type::CLEAVER, Item::Type::SHARKS_TOOTH_SWORD}))
            {
                DAMAGE = -2;

                PreText += "[SWORDPLAY] ";
            }
            else
            {
                DAMAGE = -2;

                PreText += "[MARKSMANSHIP] ";
            }
        }

        Character::GAIN_LIFE(player, DAMAGE);

        PreText += "You LOSE " + std::to_string(-DAMAGE) + " Life Points.";

        Text = PreText.c_str();

        player.TemporarySkills.clear();
    }

    int Continue(Character::Base &player) { return 342; }
};

class Story324 : public Story::Base
{
public:
    Story324()
    {
        ID = 324;

        Text = "Skarvench stands over you. You see his face as though it was reflected in a pool of blood. His voice roars and surges in your ears: \"...among the dead men...\"\n\nThe image clouds and clots, then the red haze turns to blackness as your grip on life gives way. You have met your doom at the hands of your arch-foe, and now there is no one to stop him.";

        Type = Story::Type::DOOM;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }
};

class Story325 : public Story::Base
{
public:
    Story325()
    {
        ID = 325;

        Image = "images/carvings-green.png";

        Text = "Making your way towards the sound of running water, you push the thick undergrowth aside to discover a sparkling stream. After slaking your thirst you follow the stream inland until you come to a clearing where an ancient stone monolith stands surrounded by creepers and green-filtered sunlight. Tiny gnats flit about like motes of golden dust as you inquisitively scrape away the moss covering the monolith so as to examine its carvings. Although weathered, some of the carvings can still be made out, although none of you has any idea what they represent.\n\nThe forest is full of errie sounds. Blutz looks about nervously. \"Shouldn't we be getting back to the boat?\" he says.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 344; }
};

class Story326 : public Story::Base
{
public:
    Story326()
    {
        ID = 326;

        Image = "images/filler3-green.png";

        Text = "You hide the jollyboat and lie in wait until the next morning, when Skarvench comes ashore in a rowboat with five other men: his quartermaster -- the whippet-thin villain named Curshaw, his lumbering first mate Porbuck, Borograve the master gunner, and two seamen carrying spades.\n\nYou crouch in the cover of the bushes and watch this sinister band making their way purposefully through the trees, with Skarvench striding ahead, pacing out distances and from time to time referring to a map he is carrying. Blutz gives a muffled gasp. \"They've come to dig up some treasure!\" he realises.\n\nOakley narrows his eyes. It is all he can do not to leap up from your hiding place and charge at Skarvench, so filled with hatred are his memories. But much as you year for revenge on the evil pirate captain, you know that to attack him now in your weakened state would mean almost certain death. It would be wiser to bide your time.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_ITEMS(player, {Item::Type::MONKEY}))
        {
            Choices.push_back(Choice::Base("Stay in hiding and spy on Skarvench", 4));
            Choices.push_back(Choice::Base("Give the go-ahead to attack him", 267));
        }
    }

    int Continue(Character::Base &player) { return 99; }
};

class Story327 : public Story::Base
{
public:
    Story327()
    {
        ID = 327;

        Text = "Ejada stands in front of her palace and surveys you with a haughty eye. In her gilded finery and bejewelled head-dress, with her limbs like a statue's .and her star sapphire gaze, she looks every inch a goddess.\n\nShe raises a flint knife. \"My mother the Earth is thirsty for a mortal soul. Which of you shall I send to her?\"\n\nThis is the moment of truth.";

        Choices.clear();
        Choices.push_back(Choice::Base("Make a run for it", 5));
        Choices.push_back(Choice::Base("Fight her", 365));
        Choices.push_back(Choice::Base("Let each offer a portion of their soul", 119));
        Choices.push_back(Choice::Base("[SPELLS] Use magic against her", 384, Skill::Type::SPELLS));

        Controls = Story::Controls::STANDARD;
    }
};

class Story328 : public Story::Base
{
public:
    Story328()
    {
        ID = 328;

        Text = "After a hard-fought battle you finally get in a killing blow. To your amazement, Ejada does not fall like any mortal opponent. Instead she gives a deep groan and sags forward like a puppet with its strings cut. Green sap spurts from the wound you've made above her heart, and her long virid tresses wither like plucked blooms.\"Blow me down if she wasn't some sort o' plant!\" says Grimes, touching her cheek. \"Feels like wood rather than flesh.\"\n\nYou shrug and sheathe your sword. \"She did say she was the Earth Goddess's daughter.\"\n\nA hasty exploration of Ejada's palace soon uncovers several treasures: a MAGIC WAND, a HEALING POTION, a SHIP IN A BOTTLE, and a BLACK KITE. The potion can be drunk once at any time to restore your Life Points score to normal. The other items may or may not come in handy later.";

        Bye = "Returning to the boat, you put to see without further delay.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Take = {Item::MAGIC_WAND, Item::HEALING_POTION, Item::SHIP_IN_BOTTLE, Item::BLACK_KITE};

        Limit = 4;
    }

    int Continue(Character::Base &player) { return 137; }
};

class Story329 : public Story::Base
{
public:
    Story329()
    {
        ID = 329;

        Controls = Story::Controls::NONE;
    }

    int Background(Character::Base &player)
    {
        if (Character::VERIFY_CODEWORD(player, Codeword::Type::PROSPERO))
        {
            Character::REMOVE_CODEWORD(player, Codeword::Type::PROSPERO);

            return 348;
        }
        else
        {
            return 30;
        }
    }
};

class Story330 : public Story::Base
{
public:
    Story330()
    {
        ID = 330;

        Text = "With sails towering against the darkling sky, the ship sails past on her endless voyage. Seemingly she casts a deep bone-racking chill in her wake, and all of you shiver as you watch her fade into the night.\n\n\"A backwards blessing on this cold,\" mutters Grimes through chattering teeth. \"Let's head south, mates. Better a slow journey in warmer waters than to be flung up to scrape the icy hull of heaven.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Agree with the plan to turn south", 135));
        Choices.push_back(Choice::Base("Insist on pressing westwards", 349));

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
            Choices[1].Destination = 349;
        }
    }
};

class Story331 : public Story::Base
{
public:
    std::string PreText = "";

    Story331()
    {
        ID = 331;

        Bye = "Don't look so sick, mate,\" says Oakley to Blutz. \"All the best pirates are wearing hooks these days.\"\n\nChuckling bleakly at this, you clamber back down to the jollyboat tethered alongside and start to row away.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "You raise the CLEAVER, a grim look setting your features like stone. \"Who's to be first?\" you ask.\n\nBlutz's lip trembles. He looks like a large timid hamster when he says, \"Eh? What do you mean?\"\n\n\"It's obvious mate,\" puts i Grimes, nodding towards the water tank full of decomposed hands. \"The only way off this island is to sacrifice a hand.\"\n\nOakley nods. \"That's what the sailors must've done. I don't know if it was the pain and loss that cancelled out their guilt. Maybe it was just a way of getting around the letter of the curse - y'know, chopping off the hand that did the fateful deed. Who's to say? But I see a tank full o' hands and no bodies to go with them, so they must've got away, mustn't they\"\n\nEach of you in turn submits to the CLEAVER, depositing your severed hand in the water tank with the others. It is a gruesome sacrifice, but your only way of circumventing the curse.\n\nYou LOSE 1 Life Point.";

        Character::GAIN_LIFE(player, -1);

        if (player.Life > 0)
        {
            if (Character::VERIFY_SKILL(player, Skill::Type::AGILITY))
            {
                Character::LOSE_SKILLS(player, {Skill::Type::AGILITY});

                PreText += "\n\nYour [AGILITY] skill is LOST.";
            }
        }

        Text = PreText.c_str();

        player.TemporarySkills.clear();
    }

    int Continue(Character::Base &player) { return 136; }
};

class Story332 : public Story::Base
{
public:
    Story332()
    {
        ID = 332;

        Text = "After so long at sea you would have expected to sight a ship by now. A nasty suspicion begins to obsess your thoughts: that you have drifted far south of the main trade route, and that you now have no hope of being picked up. Talking it over the others, you find that Grimes and Oakley are for turning north, possibly in the hope of reaching the Smoking Islands. There you could forage for food and water. Blutz thinks you should stick to your present course. \"Ships are scarce because the hurricane season starts in a month or so\", he reasons, \"but I still say that if we keep heading west we'll be picked up soon.\"\n\nOakley snorts impatiently. \"The hurricane isn't due for at least eight weeks! No, the reason we've not seen a ship is because we're too far south.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Steer northwards", 135));
        Choices.push_back(Choice::Base("Stay on a westbound course", 351));

        Controls = Story::Controls::STANDARD;
    }
};

class Story333 : public Story::Base
{
public:
    Story333()
    {
        ID = 333;

        Text = "The smooth steely outlines and the cloudy blue colour of the iceberg tell you that it is old ice, which will have lost its salt content over the years and should be safe to drink.";

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 352; }
};

class Story334 : public Story::Base
{
public:
    Story334()
    {
        ID = 334;

        Text = "Is it sixth sense or wishful thinking that guides your fingers to the TALISMAN? You can only guess at its power, but you mutter a silent plea, invoking the TALISMAN's magic to come to your aid now.\n\nA shadow falls across the beach, as though a cloud covered the sun. The shadow deepens. The sailors -- all of them hardened veterans of the sea -- lookup up at the sky with faces like frightened children. The sound that escapes their lips is the voice of fear, born of the most primitive terror of all. The dark.\n\nA black wing of shadow draws across the face of the sun. The day is plunged into night. In the confusion, you race off along the beach and put out to sea in your small vessel. Skarvench's bellows of rage roll across the water behind you, but his men are too terrified to follow his orders. Knowing that the pirates will search for you between here and Leshand, you set a southerly course. As the eclipse passes and the daylight comes trickling back, the island is already far behind.\n\nYou notice that the BAT-SHAPED TALISMAN has vanished.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::LOSE_ITEMS(player, {Item::Type::BAT_SHAPED_TALISMAN});
    }

    int Continue(Character::Base &player) { return 367; }
};

class Story335 : public Story::Base
{
public:
    Story335()
    {
        ID = 335;

        Image = "images/filler2-green.png";

        Text = "Doctor Scriptor examines the TALISMAN for several minutes before giving his opinion. \"This is the likeness of the Bat of Night, a mythic creature. Under my spy-glass it displays a greenish tinge, indicating that some magic still remains. Possibly its power would work once. Twice at most.\"\n\n\"To do what?\" asks Blutz.\n\n\"Your guess is as good as mine,\" replies Scriptor blandly. \"Perhaps it helps you to see in the dark? Now, my fee for the assessment is one doubloon, as you very well know.\"\n\nHe hands you back the TALISMAN.";

        Choices.clear();
        Choices.push_back(Choice::Base("Pay Scriptor 1 doubloon", -335, Choice::Type::LOSE_MONEY, 1));
        Choices.push_back(Choice::Base("You refuse to pay", 392));

        Controls = Story::Controls::STANDARD;
    }
};

class Event335 : public Story::Base
{
public:
    Event335()
    {
        Title = "Down Among the Dead Men: 335";

        ID = -335;

        Image = "images/filler2-green.png";

        Text = "Ask Doctor Scriptor to identify some items for you.";

        Choices.clear();
        Choices.push_back(Choice::Base("Ask to identify the DRAGON RING", 373, {Item::DRAGON_RING}));
        Choices.push_back(Choice::Base("... the BRONZE HELMET", 354, {Item::BRONZE_HELMET}));
        Choices.push_back(Choice::Base("... the CONCH-SHELL HORN", 316, {Item::CONCH_SHELL_HORN}));
        Choices.push_back(Choice::Base("Leave", 392));

        Controls = Story::Controls::STANDARD;
    }
};

class Story336 : public Story::Base
{
public:
    Story336()
    {
        ID = 336;

        Image = "images/cutlass-green.png";

        Text = "The pedlar is a thin fellow with a pigtail and a silver ring on his ear. On his shoulder crouches a weasel which is attached to wrist by a length of twine. As you approach, the pedlar whisks the tarpaulin off his cart and begins describing the jumble of items he has, tossing each aside and grabbing another almost as quickly as he can reel off the prices.\n\n\"Steady on, matey,\" grumbles Oakley. \"I can hardly keep up. What were you askin' for this here cutlass, now?\"";

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::STREETWISE))
        {
            return 393;
        }
        else
        {
            return 410;
        }
    }
};

class Story337 : public Story::Base
{
public:
    Story337()
    {
        ID = 337;

        Text = "Master Kemp the shipbuilder is delighted to provide you with a magnificent warship fitted with eighty cannons. \"She is the METEOR,\" he says. \"I built her for a customer some months ago, but sadly he was apprehended in Port Worshen before he could take delivery. Now he's to be seen on Execution dock -- food for rooks, God help his soul -- and his fine is yours.\"\n\n\"Perhaps we should change the name?\" suggests Oakley. \"METEOR was the original owner's choice, not ours.\"";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::TAKE_SHIP(player, Ship::METEOR);

        Choices.clear();

        if (!Character::VERIFY_SKILL(player, Skill::Type::FOLKLORE))
        {
            Choices.push_back(Choice::Base("Change the vessel's name", 411));
            Choices.push_back(Choice::Base("Leave it as it is", 184));
        }
    }

    int Continue(Character::Base &player) { return 394; }
};

class Story338 : public Story::Base
{
public:
    Story338()
    {
        ID = 338;

        Text = "You have little enough to go on -- just a hazarded guess at the iceberg's last position, and your best estimate of how far the prevailing current might have carried it by now. It is going to be like looking for a needle in a haystack, as your comrades are swift to point out.\n\n\"But when that proverbial needle is made of gold, so to speak, and has a diamond set into it,\" you reply to their objections, \"surely then the task's worth attempting?\"";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_SKILL(player, Skill::Type::SEAFARING))
        {
            Choices.push_back(Choice::Base("Steer due south", 378));
            Choices.push_back(Choice::Base("Steer towards the south-west", 56));
            Choices.push_back(Choice::Base("... or south-east", 207));
            Choices.push_back(Choice::Base("Abandon your plan to search for the iceberg and try your hand at piracy instead", 357));
        }
    }

    int Continue(Character::Base &player) { return 359; }
};

class Story339 : public Story::Base
{
public:
    Story339()
    {
        ID = 339;

        Text = "You sign on a small crew. A good following wind carries you to Leshand in six days. Disappointment awaits you there, however, as no-one has any idea where El Draque's treasure lies buried. \"Sure, an' if I knew,\" says one old tar you speak to, \"would I not be after fetchin' it meself?\"\n\nAt these words, his drinking companions all cross themselves, and mouths that are more accustomed to hard swearing mumble a swift prayer. \"Don't pay any heed to old Bunratty's talk!\" cries another man. \"Anyone who went seeking El Draque's treasure might as well pawn their souls to the Devil on the day they set sail.\" ´Blutz is quite discomfited by all this, and you are surprised to see as you leave the inn that even Grimes and Oakley are wide-eyed and pale. \"Come on, skipper,\" urges Oakley. \"It's pretty clear there's something eerie about this El Draque. Why, he's supposed to be dead and gone but a lot of folk still seem mortally afraid of him for all that!\"\n\n\"Let's put to sea and try a little piracy,\" suggests Grimes. \"We'd soon have enough put by to get ourselves a decent warship.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Insist on continuing the hunt for El Draque's treasure", 377));
        Choices.push_back(Choice::Base("Agree to Grimes' suggestion", 357));

        Controls = Story::Controls::STANDARD;
    }
};

class Story340 : public Story::Base
{
public:
    Story340()
    {
        ID = 340;

        Text = "Several limbs lie like dead fishes across the deck -- not just those of the vampires, but also some torn from their sockets of your poor sailors, who now lie screaming as their lifeblood gushes across the planks.\n\nThree of the vampires still stand, but your spirited defence of your vessel has cowed them. They crouch back against the rail. Then keeping their eyes fixed on you, they drop to their knees with a hideous mewling sound to lick up some of the spilled blood. \"Merciful God...\" croaks Grimes. Although not a squeamish man, he turns away and retches with disgust.\n\nThe remaining vampires rise and face you across the carnage. Of all the crew only yourself, Grimes, Oakley and Blutz are still standing -- and the fight has gone out of you at the sight of such horrors. For their part, the vampires make no move but only stare at you and lick their gore-spattered lips. At last their leader speaks. He is a pallid but unblemished creature with eyes like old ice. \"I am El Draque. Never have I been bested, but tonight I will concede you've fought me to a stand off. We'll go and leave you in peace, but I'll add this warning. Do not touch the treasure in our coffins, or you'll carry my curse for the rest of your days.\"\n\nHe drops back over the side with the other two. There is no splash, nor any sign of them when you go to the rail to look. There is just the swirling fog. The fallen vampires dissolve from the deck into a miasmic murk which only disperses with the sunrise. You take stock of the dead and injured among your crew, then hold a council with your officers to decide whether to take the treasure or not.";

        Choices.clear();
        Choices.push_back(Choice::Base("Take the treasure", 16, Choice::Type::GET_CODEWORD, Codeword::Type::MALEFIC));
        Choices.push_back(Choice::Base("Leave it alone", 396));

        Controls = Story::Controls::STANDARD;
    }
};

class Story341 : public Story::Base
{
public:
    Story341()
    {
        ID = 341;

        Text = "The Moon Dog manoeuvres slowly nearer, pushing against the wind. She is taking damage all the time from your cannons , but the wind causes your own ship to heel over slightly , so that most of your shots strike the enemy's hull rather than the sails. You have not yet crippled the Moon Dog, and now she is turning for a broadside.";

        Choices.clear();
        Choices.push_back(Choice::Base("Stand and take it", 19));
        Choices.push_back(Choice::Base("Pull astern of the enemy for boarding", 38));
        Choices.push_back(Choice::Base("Move off out of range of their cannons", 57));

        Controls = Story::Controls::STANDARD;
    }
};

class Story342 : public Story::Base
{
public:
    Story342()
    {
        ID = 342;

        Image = "images/filler1-green.png";

        Text = "Skarvench utters a single cry like the croak of a carrion bird, then goes plunging down to his death on the deck below. You climb back down not a moment too soon, for the rope is suddenly jerked out of your hands and goes coiling up into the mist.\n\n\"They've had enough, now their captain's dead,\" says Grimes as you watch the outlines of the Moon Dog recede up into the sky.\n\n\"I'd have liked to get that Curshaw -- and Porbuck as well,\" mutters Oakley. \"I've still got scores to settle with those two.\"\n\nYou clasp their arms and nod towards the broken body of Skarvench lying on the deck. \"Don't be downcast, lads. Tomorrow's another day, and no doubt we'll catch up with those villains sooner or later, but we've done sterling work tonight!\"\n\n\"Indeed you have,\" says an aristocratic voice. You turn to see a tall distinguished-looking Gloriannic gentleman who can only be Admiral Calidor, commander of the Queen's navy. Behind him are a squad of royal marines. \"If you hadn't shown up,\" he continues, \"who knows if we could have been able to cope with those pirates. We've only just managed to subdue their accomplice, the sorcerer William Wild.\"\n\n\"My lord,\" you say, bowing, \"they were after the Queen herself.\"\n\nCalidor smiles. \"I know. And, speaking of the Queen...\"";

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 427; }
};

class Story343 : public Story::Base
{
public:
    std::string PreText = "";

    Story343()
    {
        ID = 343;

        Image = "images/filler2-green.png";

        Choices.clear();
        Choices.push_back(Choice::Base("Use both CORKSCREW and SHIP IN A BOTTLE", 261, {Item::CORKSCREW, Item::SHIP_IN_BOTTLE}));
        Choices.push_back(Choice::Base("Use the CONCH-SHELL HORN", 280, {Item::CONCH_SHELL_HORN}));
        Choices.push_back(Choice::Base("Use DEED OF OWNERSHIP given to you by Master Capstick", 318, {Item::DEED_OF_OWNERSHIP}));
        Choices.push_back(Choice::Base("Pay with DIAMONDs", 299, {Item::DIAMOND}));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Type = Story::Type::NORMAL;

        PreText = "You make your way outside, where there are more onlookers attracted by news of the shooting. \"Are you the one Skarvench shot?\" asks an old man, seeing the blood on your chest.\n\n\"Aye,\" you say, and you tell him the tale of your lucky escape. He looks at the article that saved your life. \"A valuable investment. I must buy one myself.\"\n\nBlutz chips in: \"Listen, old man, did you see where Skarvench went?\"\n\n\"Less of the 'old' if you please, fatty,\" says the old man bristling. \"And to answer your query, he and his men went of chortling their way down this very street in the direction of the waterfront.\"\n\nOakley cries out an oath. \"They'll have set sail! We need a ship of our own.\"";

        if (!Character::VERIFY_ITEMS(player, {Item::Type::CORKSCREW, Item::Type::SHIP_IN_BOTTLE}) && !Character::VERIFY_ITEMS_ANY(player, {Item::CONCH_SHELL_HORN, Item::DEED_OF_OWNERSHIP, Item::DIAMOND}))
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

class Story344 : public Story::Base
{
public:
    Story344()
    {
        ID = 344;

        Image = "images/filler3-green.png";

        Text = "You return to the cliffs to find a dozen islanders standing at the top of the vine ladder. They wear grass skirts and each has a red skull-like mask painted across his face. \"That's how the island got its name,\" mutters Oakley out of the corner of his mouth.\n\n\"Maybe so,\" whispers Grimes. \"Or maybe they're headhunters.\"\n\nYou approach cautiously, uncertain of the islanders' intentions. They watch you in silence and then one of them bares his lips in a ferocious grin. Blutz gives a small moan and goes weak at the knees, and you catch his arm to give him support. To your horror, the islander's front teeth are filed to sharp points!";

        Choices.clear();
        Choices.push_back(Choice::Base("Try to fight your way past them", 363));
        Choices.push_back(Choice::Base("Offer them gifts", 382));
        Choices.push_back(Choice::Base("Ignore them and just start to descend the ladder", 400));

        Controls = Story::Controls::STANDARD;
    }
};

class Story345 : public Story::Base
{
public:
    Story345()
    {
        ID = 345;

        Text = "The cutters are hard on your stern, and your sorry little band are all too weakened by the privation to outrun them. Realising this, you tell your friends to steer in close to the shoreline -- where earlier, beneath the crystal-clear water, you noticed the jagged outline of submerged rocks.\n\nIt is a gamble. You might run onto the rocks yourselves. But to fall into Skarvench's hands would be even more certain disaster. Luckily your jollyboat passes safely over the reef, but when the pursuing cutters reach it there is a harsh scraping sound followed by a telltale splintering. The pirates' jeering shouts turn to cries of alarm.\n\nYou look back. As you guessed, the cutters were overladen. Lying lower in the water than your jollyboat, they have run aground. The pirates shake their fists, but they have no hope of catching you now. The Belle Dame must remain at anchor till the tide turns, while you row on throughout the night.";

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 135; }
};

class Story346 : public Story::Base
{
public:
    Story346()
    {
        ID = 346;

        Text = "You hide deep in the woods. As the silvery gleam of the predawn sky fills the shadows between the leaves, you suddenly hear an imperious command shouted from far off. It is the voice of the witch. At her order, the palm bend to seize the four of you and you are passed from branch to branch through the forest to be deposited roughly on the ground in front of the palace.\n\nYou LOSE 1 Life Point.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -1);
    }

    int Continue(Character::Base &player) { return 327; }
};

class Story347 : public Story::Base
{
public:
    Story347()
    {
        ID = 347;

        Text = "No sooner has night fallen than an uncanny chill closes around you. An unspoken fear impels all of you to stagger back from the hole you have dug. You watch aghast as a shimmering mist forms in the air above the boxes. Then looming shadows are thrown against the mist -- as suddenly as if blinds had been thrown up on an open window -- and a host of pale ragged figures come shambling forward. Some have skin of tallow, others are ravaged by grave-mould. Spots of rust mark their armour, and their coats hang about them like decaying shrouds.\n\nThe foremost of this frightful throng steps forth. His face is the colour of clay, making his acid blue eyes all the more startling. Baring his sharp teeth in a macabre grin, he issues his greeting in a rasping voice. \"So there are still a few who'd dare to steal from El Draque. I admire your brass, my lads. And now, let's spill a little blood and drink a gory toast to the last day of your lives, and then mayhap I'll let you join my jolly band.\"";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_SKILL(player, Skill::Type::CHARMS) && !Character::VERIFY_ITEMS(player, {Item::Type::CRUCIFIX}))
        {
            Choices.push_back(Choice::Base("[SWORDPLAY] Use a SWORD", 245, Choice::Type::SKILL_ANY, Skill::Type::SWORDPLAY, {Item::SWORD, Item::RUSTY_SWORD, Item::CLEAVER, Item::SHARKS_TOOTH_SWORD}));
            Choices.push_back(Choice::Base("Otherwise", 264));
        }
    }

    int Continue(Character::Base &player) { return 226; }
};

class Story348 : public Story::Base
{
public:
    Story348()
    {
        ID = 348;

        Text = "Each day the natives bring you food and water, treating you like honoured guests. By night you sing under the stars; by day you doze in warm sea breezes. Life is full of ease and contentment. Only one thought mars your pleasure at this regal luxury: that somewhere out there across the broad seas, Skarvench still lives to work his evil ways.\n\nAlmost a month goes by. At last a ship appears on the horizon. By now rest and good food have stored your strength and you leap to your feet, waving palm leaves and yelling at the top of your lungs. The ship diverts here course and a rowboat is sent to fetch you from ashore.\n\nThe captain, a Gloriannic merchant named Quintal, greets you heartily as you come board. Handing you mugs of ale, he tells you his ship is bound for Leshand. Although Leshand was your original objective, you know that time is now of the essence if you're to have nay chance of foiling Skarvench's scheme to abduct Queen Titania.\n\nYou RECOVER all lost Life Points.";

        Choices.clear();
        Choices.push_back(Choice::Base("Confide in Captain Quintal", 239));
        Choices.push_back(Choice::Base("Keep quiet and allow him to take you to Leshand as planned", 258));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        player.Life = player.MAX_LIFE_LIMIT;
    }
};

class Story349 : public Story::Base
{
public:
    Story349()
    {
        ID = 349;

        Text = "A shrieking gale rises out of the east to blow you onward, but at least there is an end to the numbing rain that has pestered you for so much of the voyage. Making good headway through high frothing waves, your worst hardship becomes nausea at being hurled up and down in your flimsy craft. Even so, hunger gnaws at your insides and your longing for food and water becomes overwhelming.\n\nYou LOSE 1 Life Point.";

        Choices.clear();
        Choices.push_back(Choice::Base("Eat the monkey (if you are heartless or desperate enough)", 368, Choice::Type::LOSE_ITEMS, {Item::MONKEY}));
        Choices.push_back(Choice::Base("Leave it alone", 387));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -1);
    }
};

class Story350 : public Story::Base
{
public:
    Story350()
    {
        ID = 350;

        Text = "Your fervent prayers go unanswered. As the four of you kneel there on the deck, heads reverently bowed, Blutz gives a sudden sob. \"God's abandoned us, shipmates!\" he weeps. \"We're cursed.\"\n\n\"Aye,\" cracks a voice through the gusting wind. \"Cursed to sail adrift under a heedless heaven for all eternity!\"\n\nYou turn, shocked to see Mandrigard standing on the poopdeck, his turban lost, hair flying wildly and robes snapping about him. Rain streaks his colourless face. He stumps forward, his whalebone leg creaking the deck timbers under his weight. A grog bottle is in his hand, and he sloshes its contents as he laughs at you: \"Prayer, is it you're at? Ah, you poor fools, haven't you yet guessed the truth? This is purgatory, mates! There's no praying your way out of this mess. Here there's no living or dying, no rest, no atonement, nor answer to your orisons! This is how it'll be, now and forever, aboard the damned ship Larnassos!\n\nHis screaming laughter rises to the cloud-filled sky, and with a feeling of mounting horror you realise he is right. You have brought the curse upon your heads. Now you will sail the seas throughout eternity.";

        Type = Story::Type::DOOM;

        Controls = Story::Controls::STANDARD;
    }
};

class Story351 : public Story::Base
{
public:
    std::string PreText = "";

    Story351()
    {
        ID = 351;

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        PreText = "The sun stares balefully down from a sky of burnished steel, leeching your strength. To prevent your brains being cooked in your skulls, you soak strips of torn cloth in the sea and wrap them round your brows. The brine dries to hard salt which chafes your many sores, but by now you are past caring.\n\nYou LOSE 1 Life Point.";

        Character::GAIN_LIFE(player, -1);

        Choices.clear();

        if (player.Life > 0)
        {
            PreText += "\n\nAfter what seems an endless time, Oakley gives a surprised shout and lunges desperately for something floating in the water beside the boat. Fumbling in a frenzy of excitement, he finally gets a firm hold on the object and hefts it up for you all to see.\n\n\"A coconut!\" says Blutz. \"But is it safe to eat? Floating out here in mid-ocean, I mean. How did it get there?\"\n\n\"Jetsam,\" says Oakley with conviction.\n\nBlutz scratches his fat jowls. \"Er... but I heard this legend of Domdaniel, which is the place under the sea where the drowned sailors live. This coconut might have floated up from one of their groves. That would make it dead men's food, you see, and not for us.\"\n\n\"Pah! You fat fool!\" gasps Oakley.\n\nGrimes and Oakley intend to eat the coconut whether it is safe or not. Blutz protests that even if it was dropped off a ship, it might have gone rotten.";

            if (!Character::VERIFY_SKILL(player, Skill::Type::WILDERNESS_LORE))
            {
                Choices.push_back(Choice::Base("Eat some of the cocunuts", 389, Choice::Type::GET_CODEWORD, Codeword::Type::COCONUTS));
                Choices.push_back(Choice::Base("Leave it alone", 389));
            }
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 158; }
};

class Story352 : public Story::Base
{
public:
    Story352()
    {
        ID = 352;

        Text = "The outlines of the ship become clearer as you approach the iceberg. She is a fine gilded galleon, her sails hanging like cerements, wreaths of frost along her flanks and spikes ice amid the rigging. Though apparently quite old and of exotic origin, it seems that the ice has kept the touch of time from harming her. You can even make out the name painted on the prow, the letters distorted and shimmering as though seen through a lens. Blutz (who is an educated man among pirates, having once drowned a school-teacher) reads it: \"The Octavius. Wonder how long she's been ice-bound, eh mates?\"\n\nComing alongside the ice-floe, Oakley leaps ashore and hammers a spike for the mooring roper. \"Years perhaps. But let's not linger here, it's chilly enough to make a brass monkey drop its balls. We'll just collect water and be off.\"\n\n\"But will it be safe?\" says Blutz again. \"Surely an iceberg is just frozen sea-water. You can't drink it.\"\n\nYou gained the codeword AUGUST.";

        Choices.clear();
        Choices.push_back(Choice::Base("Collect some ice", 425));
        Choices.push_back(Choice::Base("Agree with Blutz", 371));

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GET_CODEWORDS(player, {Codeword::Type::AUGUST});
    }
};

class Story353 : public Story::Base
{
public:
    Story353()
    {
        ID = 353;

        Image = "images/filler2-green.png";

        Text = "Perhaps it is the warning of a sixth sense, perhaps just a groundless fear, but you suddenly how that not all the riches of the Sidonian Main could tempt you to set foot on that eerily silent deck. Ignoring the captain's outstretched hand, you leap up onto the rail and from there jump to the rigging, making your way with catlike grace until you are astride the yardarm.\n\nCaptain Mandrigard takes out his sabre and shake it at you. \"Blast ye, come down from here, ye damned monkey!\" he roars. But you see that he won't be coming up in pursuit of you. Not with his wooden leg.\n\nSeizing the pulleys that support the ship's cutter, or sailing boat, you swing it out over the side and then sever the ropes. The cutter falls with a splash and, as your friends scramble aboard it, you give the captain a dashing salute. \"Thank you, sir, for the fine new boat; please keep our old jollyboat in exchange. But now I must bid you adieu.\"\n\nMandrigard spits curses that would bring a blush to the Devil himself, but there is nothing he can do. Scrambling down the side of the ship, you join the others in the cutter. \"This is more like it,\" says Blutz appreciatively, slapping the firm timbers. \"She won't sink under us in a hurry!\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::REMOVE_CODEWORD(player, Codeword::Type::PECCANT);
        Character::REMOVE_CODEWORD(player, Codeword::Type::DETRUDE);
    }

    int Continue(Character::Base &player) { return 330; }
};

class Story354 : public Story::Base
{
public:
    Story354()
    {
        ID = 354;

        Image = "images/filler2-green.png";

        Text = "\"This was the helmet of Spartan king,\" decides Scriptor after turning the object over in his hands. \"Despite the millennia that have passed since Sparta's heyday, their name is still a byword for stern martial prowess. I would conclude, therefore, that donning the helm would confer some skill at arms.\"\n\nHe demands a doubloon for what he's told you so far. Alternatively you can sell the helmet to Scriptor for his collection -- he'll pay you 15 doubloons for it.";

        Choices.clear();
        Choices.push_back(Choice::Base("Pay Scriptor 1 doubloon", -354, Choice::Type::LOSE_MONEY, 1));
        Choices.push_back(Choice::Base("Sell him the BRONZE HELMET", -354, Choice::Type::SELL, {Item::BRONZE_HELMET}, 15));
        Choices.push_back(Choice::Base("You refuse to pay", 392));

        Controls = Story::Controls::STANDARD;
    }
};

class Event354 : public Story::Base
{
public:
    Event354()
    {
        Title = "Down Among the Dead Men: 354";

        ID = -354;

        Image = "images/filler2-green.png";

        Text = "Ask Doctor Scriptor to identify some items for you.";

        Choices.clear();
        Choices.push_back(Choice::Base("Ask to identify the DRAGON RING", 373, {Item::DRAGON_RING}));
        Choices.push_back(Choice::Base("... the CONCH-SHELL HORN", 316, {Item::CONCH_SHELL_HORN}));
        Choices.push_back(Choice::Base("... the BAT-SHAPED TALISMAN", 335, {Item::BAT_SHAPED_TALISMAN}));
        Choices.push_back(Choice::Base("Leave", 392));

        Controls = Story::Controls::STANDARD;
    }
};

class Story355 : public Story::Base
{
public:
    Story355()
    {
        ID = 355;

        Text = "Ducking under the low rafters, you cross the sawdust-strewn taproom and seat yourselves in an alcove. At a table nearby sits a blind old man sipping brandy from a wide saucer-shaped cup. Raucous laughter pulls your gaze to the bar, where three ruffians are amusing themselves at the expense of a gentleman in shabby scholastic robes. One of the ruffians has taken the man's spectacles and is jokingly trying them on, ignoring his short-sighted attempts to grab them back.";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_SKILL(player, Skill::Type::STREETWISE))
        {
            Choices.push_back(Choice::Base("Talk to the blind man", 33));
            Choices.push_back(Choice::Base("Step in to help the scholar", 52));
            Choices.push_back(Choice::Base("Leave to visit the shipyard", 374));
        }
    }

    int Continue(Character::Base &player) { return 71; }
};

class Story356 : public Story::Base
{
public:
    Story356()
    {
        ID = 356;

        Text = "No sooner has he set eyes on your diamonds than the shipbuilder rushes out from his office to take care of your needs personally. Showing you around the shipyard, he points to a fine new vessel that is just in the last stages of caulking. \"She will be ready to float within a week,\" he declares. \"You have only to specify the name and figurehead of your choice.\"\n\nYou stand with hands on hips, beaming at the ship. It feels like love at first sight. \"Name her the QUEEN's RANSOM,\" you say exultantly.\n\nOakley nods. \"Aye, and make the figurehead a comely mermaid, if you will, Master Shipbuilder.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::TAKE_SHIP(player, Ship::QUEENS_RANSOM);
    }

    int Continue(Character::Base &player) { return 184; }
};

class Story357 : public Story::Base
{
public:
    Story357()
    {
        ID = 357;

        Text = "After signing up a small crew, you spend the next few weeks plying the main shipping.lanes in search of spoils. You succeed in waylaying a couple of Sidonian merchantmen, but they prove to have little of worth in their hold. After tallying the profits and deducting each crewman's share, Blutz comes to you. \"At this rate it'll take us months to earn enough for a decent warship, Cap'n,\" he says.\n\nYou gnaw your lip -- the only outward sign that you are concerned. Other than that, your face remains an impassive granite mask. Gazing dead ahead, you say, \"You've a suggestion, Mister Blutz?\"\n\n\"Aye, Cap'n. I know you won't like it, seein' as how you hail from Glorianne yourself, but if we didn't just confine ourselves to Sidonian ships -- that is, if we was to plunder Gloriannic vessels too -- we'd earn what we need in half the time.\"\n\nIt is your judgement call. What order will you give?";

        Choices.clear();
        Choices.push_back(Choice::Base("Give the order to continue preying only on Sidonian ships", 376));
        Choices.push_back(Choice::Base("Order to attack both Sidonian and Gloriannic ships from now on", 395));
        Choices.push_back(Choice::Base("Order to reduce the crew's share of the plunder", 412));

        Controls = Story::Controls::STANDARD;
    }
};

class Story358 : public Story::Base
{
public:
    Story358()
    {
        ID = 358;

        Text = "Signing on a small crew, you set sail. A strong following wind allows you to make good headway, and you reach the island in under three weeks. There your luck runs out, however, for there is no hint of treasure. Cursing blue fire, you have your men scour the beach and the hinterland for signs -carvings in the bark of a tree, piled stones, skeletons laid in a line, and all the other marks pirates use. But it is all in vain. At last Oakley and the others come to you in your cabin. \"The tide's against us, so to speak, skipper. If we don't put about and return to Selenice right away, Skarvench will have done the deed and we'll have lost our chance.\"\n\nYou swear under your breath, but you know Oakley is right. Reluctantly you sail the LADY OF SHALOTT back to Selenice.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 396; }
};

class Story359 : public Story::Base
{
public:
    Story359()
    {
        ID = 359;

        Text = "A combination of relentless determination and unsurpassed navigation skills drives you inexorably towards your goal. At any hour of the day or night you are to be seen upon the poopdeck, taking estimates of the wind and sea currents or using a cross-staff to measure the stars. The crew know of your near legendary status as a master mariner and dare not question your judgement, even though you are steering the ship far off familiar sailing routes.\n\nFinally your perseverance is rewarded with a cry of \"Ice ho!\" from the crow's nest. You race up from your cabin and give a great roar of triumph as you catch sight of the low blue hump of an iceberg dead ahead.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 414; }
};

class Story360 : public Story::Base
{
public:
    std::string PreText = "";

    Story360()
    {
        ID = 360;

        Image = "images/filler1-green.png";

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        if (Character::VERIFY_SKILL(player, Skill::Type::SEAFARING))
        {
            PreText = "[SEAFARING] You managed to avoid the cannon-fire.";
        }
        else
        {
            PreText = "You are clipped by cannon-fire.\n\nYour ship SUFFERS 1 damage.";

            Character::DAMAGE_SHIP(player, 1);
        }

        Choices.clear();

        if (Character::CHECK_SHIP(player))
        {
            PreText += " Decide what to do next.";

            Choices.push_back(Choice::Base("Steer directly in towards the Moon Dog", 398));
            Choices.push_back(Choice::Base("Heave to and let the wind carry her past you", 415));
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 227; }
};

class Story361 : public Story::Base
{
public:
    Story361()
    {
        ID = 361;

        Text = "Skarvench opens his mouth, but the only sound that issues forth is a stifled croak. Teetering from a mortal wound, he falls to the deck and lies still.\n\nSeeing the death of their leader, the pirates lose heart for the battle and are soon rounded up. As their muskets are confiscated, Oakley comes over and takes you by the arm. \"You all right, skipper?\" he asks with a look of concern. \"You look in a bad way.\"\n\n\"If you think I look bad, Mister Oakley,\" you reply with a smile of weary triumph, \"you ought to take a look at the other bloke.\"";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 427; }
};

class Story362 : public Story::Base
{
public:
    std::string PreText = "";

    Story362()
    {
        ID = 362;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Background(Character::Base &player)
    {
        if (!Character::VERIFY_ITEMS_ANY(player, {Item::POCKET_WATCH, Item::CRUCIFIX, Item::MAGIC_AMULET}))
        {
            return 324;
        }
        else
        {

            return -1;
        }
    }

    void Event(Character::Base &player)
    {
        PreText = "";

        if (Character::VERIFY_ITEMS(player, {Item::Type::POCKET_WATCH}))
        {
            PreText += "[Item: POCKET-WATCH] ";
        }

        if (Character::VERIFY_ITEMS(player, {Item::Type::CRUCIFIX}))
        {
            PreText += "[Item: CRUCIFIX] ";
        }

        if (Character::VERIFY_ITEMS(player, {Item::Type::MAGIC_AMULET}))
        {
            PreText += "[Item: MAGIC AMULET] ";
        }

        Character::GAIN_LIFE(player, -3);

        PreText += "You LOSE 3 Life Points.";

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player) { return 242; }
};

class Story363 : public Story::Base
{
public:
    Story363()
    {
        ID = 363;

        Text = "Decide what to do next";

        Choices.clear();
        Choices.push_back(Choice::Base("Employ [SWORDPLAY]", 296, Choice::Type::SKILL_ANY, Skill::Type::SWORDPLAY, {Item::SWORD, Item::RUSTY_SWORD, Item::CLEAVER, Item::SHARKS_TOOTH_SWORD}));
        Choices.push_back(Choice::Base("... or [BRAWLING]", 296, Skill::Type::BRAWLING));
        Choices.push_back(Choice::Base("Use [MARKSMANSHIP]", 270, Skill::Type::MARKSMANSHIP));
        Choices.push_back(Choice::Base("Otherwise", 5));

        Controls = Story::Controls::STANDARD;
    }
};

class Story364 : public Story::Base
{
public:
    Story364()
    {
        ID = 364;

        Text = "Drastic situations call for drastic remedies. Using a last-ditch trick taught to you years ago by your father, you hurl your sword at the lookout. It strikes true, penetrating his heart and killing him instantly. He tumbles from the deck without a sound, hitting the water with a limp splash.\"Well aimed,\" says Grimes in a hushed tone of admiration. \"You got him before he could raise the alarm.\"\n\nYou nod, regretting the loss of your sword.\n\nRowing on, you do not relax until the ship has dropped out of sight over the horizon to your stern.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 135; }
};

class Story365 : public Story::Base
{
public:
    std::string PreText = "";

    Story365()
    {
        ID = 365;

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Choices.clear();

        if (!Character::VERIFY_SKILL_ANY(player, Skill::Type::SWORDPLAY, {Item::Type::SWORD, Item::Type::CLEAVER, Item::Type::RUSTY_SWORD, Item::Type::SHARKS_TOOTH_SWORD}) && !Character::VERIFY_SKILL(player, Skill::Type::MARKSMANSHIP))
        {
            PreText = "You cannot defend yourself from her strong blows. You LOSE 3 Life Points.";

            Character::GAIN_LIFE(player, -3);

            Choices.push_back(Choice::Base("[SPELLS] Use a WAND", 384));
            Choices.push_back(Choice::Base("Make a run for it", 5));
        }
        else
        {
            PreText = "You are able to defend yourself against her strong blows.";

            Choices.push_back(Choice::Base("[SWORDPLAY] Use a SHARK's TOOTH SWORD", 402, Skill::Type::SWORDPLAY, {Item::SHARKS_TOOTH_SWORD}));
            Choices.push_back(Choice::Base("[SWORDPLAY] Use an ordinary SWORD", 419, Choice::Type::SKILL_ANY, Skill::Type::SWORDPLAY, {Item::SWORD, Item::RUSTY_SWORD, Item::CLEAVER}));
            Choices.push_back(Choice::Base("[MARKSMANSHIP] Use a PISTOL", 317, Skill::Type::MARKSMANSHIP));
            Choices.push_back(Choice::Base("Resort to [BRAWLING]", 241, Skill::Type::MARKSMANSHIP));
        }

        Text = PreText.c_str();
    }
};

class Story366 : public Story::Base
{
public:
    Story366()
    {
        ID = 366;

        Image = "images/filler4-green.png";

        Text = "The fog thickens about the ship, smudging the outlines of the bay and covering the stars in a filmy veil. From the marshy ground of the shore comes a green unhealthy glow, just visible between the drifting palls of mist. Blutz gazes this eerie phosphorescence and says through chattering, \"Will o' wisps. Spirits of men who droned at sea and were washed up here.\"\n\nYou are due to take the first watch, with Blutz relieving you at eight bells. It strikes you that his nerves may not stand at midnight vigil, and maybe it would be better if he exchanged watches with you.";

        Choices.clear();
        Choices.push_back(Choice::Base("Let Blutz take the midnight watch", 112));
        Choices.push_back(Choice::Base("Take the midnight watch yourself", 131));

        Controls = Story::Controls::STANDARD;
    }
};

class Story367 : public Story::Base
{
public:
    std::string PreText = "";

    bool HAS_FOOD = false;

    Story367()
    {
        ID = 367;

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        HAS_FOOD = false;

        PreText = "As you go south you begin to strike the warm east current marking the main shipping lane. \"Here we have a chance of rescue,\" declares Oakley. His tone is confident enough -- an attempt to inspire good cheer -- but the rigors of the voyage are again taking their toll.\n\nYou LOSE 1 Life Point.";

        Character::GAIN_LIFE(player, -1);

        if (player.Life > 0)
        {
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
        }

        Text = PreText.c_str();
    }

    int Continue(Character::Base &player)
    {
        if (HAS_FOOD)
        {
            return 106;
        }
        else
        {
            return 125;
        }
    }
};

class Story368 : public Story::Base
{
public:
    Story368()
    {
        ID = 368;

        Text = "\"Poor little fellow, it seems unfair after he's been with us so long,\" bleats Blutz.\n\nYou agree in principle, but seamen soon learn that practical necessities must outweigh sentiment. \"We could eat you instead if you'd rather spare the MONKEY, Mister Blutz.\"\n\n\"Aye,\" says Grimes, jabbing him good-naturedly in the ribs. \"And you'd make a better meal too. Wouldn't he, mates?\"\n\nIn the event, despite the shedding of a maudlin tear or two, it is the MONKEY who ends up on your plates. The meal is cold and gristly, but better than nothing.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 405; }
};

class Story369 : public Story::Base
{
public:
    Story369()
    {
        ID = 369;

        Text = "You reach into the toolkit and rummage around for a hacksaw. Your reasoning is that the curse prevents you from leaving the deck of the Larnassos. Very well, then you'll take the deck with you when you go -- or part of it, at any rate. Sawing around the outline of your footprints, you give your astonished companions a knowing wink and then climb over the rail. The foot-shaped pieces of plank which you've cut out remain clinging to the soles of your shoes, stuck fast by the magic of the curse.\n\n\"Well, blow me!\" mutters Grimes. Taking the hacksaw, he too saws out his patch of the deck, and the others follow suit. Soon the four of you are climbing back down to the jollyboat tethered alongside.\n\nYou may have cleverly circumvented the exact letter of the curse, but do not be too quick to pat yourself on the back. The wooden soles will stay on your feet for ever as an uncanny reminder of your narrow escape. They make a noisy clattering when you walk which will hinder any attempt you might make at stealth.\n\nYou row away from the Larnassos until she is swallowed by distance and darkness.\n\nYour [ROGUERY] skill is LOST.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::LOSE_SKILLS(player, {Skill::Type::ROGUERY});
    }

    int Continue(Character::Base &player) { return 136; }
};

class Story370 : public Story::Base
{
public:
    Story370()
    {
        ID = 370;

        Text = "The captain of the Jewel of Heaven is a bluff good-natured man who roars at his crew with gusto. For their part they seem devoted to him -- and perhaps a little overawed by his forceful nature and matchless knowledge of the sea. You spend several pleasant evenings sitting in his cabin, where the rum flows free after a good supper. \"Hark to that!\" he is wont to say, listening to the water lapping against the hull. \"Did you ever hear a mother with babe in arms sing such a sweet lullaby? Ah, the sweet sighing of the sea -- it's a sound to seal the hushed casket of a man's soul, my merry lads!\"\n\n\"Here aboard your fine ship, I'm happy to agree,\" laughs Oakley. \"When we were drifting in our boat, though, the sea sang us a more mournful tune!\"\n\nThe captain is glad to have educated company, and you can strike up conversations on various topics.";

        Choices.clear();
        Choices.push_back(Choice::Base("Ask for his opinion on pirates", 390));
        Choices.push_back(Choice::Base("Ask about the war between Glorianne and Sidonia", 380));
        Choices.push_back(Choice::Base("Ask about Queen Titania's visit to the New World colonies", 403));
        Choices.push_back(Choice::Base("Ask for information about Port Leshand", 420));

        Controls = Story::Controls::STANDARD;
    }
};

class Story371 : public Story::Base
{
public:
    Story371()
    {
        ID = 371;

        Text = "What secrets, you muse to yourself, lie locked aboard the ice-bound vessel? It is a mystery that may never be answered. Even a full ship's company armed with picks would take weeks to hack her out of the ice.\n\nYou veer away from the iceberg, soon losing it far astern. The hideous incessant sun continues to sap your strength by day. By night you lie groaning in the gravid cold.\n\nYou LOSE 2 LIfe Points.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::GAIN_LIFE(player, -2);
    }

    int Continue(Character::Base &player) { return 424; }
};

class Story372 : public Story::Base
{
public:
    Story372()
    {
        ID = 372;

        Text = "You are STRIPPED of ALL your POSSESSIONS and bundled into the ship's hold to await Skarvench's return. The hatch closes, leaving you in darkness. You can hear rats scurrying about. \"Help untie these bonds,\" you tell the others. \"Then we wait.\"\n\nAfter several hours you hear Skarvench come board. Feet clump down, creaking the timbers around the hatch over your heads. You hear a voice say, \"Does 'e want 'em up on deck now?\"\n\n\"Not yet,\" replies another man. \"We're to get under way first. Cap'n's keen to reach Selenice an' see if the moonsails 'ave arrived.\"\n\nThe ship moves slowly as the anchor cable is winched in. Then you hear the pirates break into song as they hoist the sails and begin to steer out of the bay.\n\nSuddenly there is a jolt and the ship lurches to one side. This is your chance. Hastily forcing the hatch, you emerge on deck to find that the ship has run aground on a reef. \"I knew those alterations I made to the charts would pay off,\" you tell the others with a crafty smile.\n\nSlipping over the side, you swim away unnoticed in the confusion.. Once back at the shore, you lose no time getting your little vessel and putting to sea under cover of the dusk.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::LOSE_POSSESSIONS(player);
    }

    int Continue(Character::Base &player) { return 177; }
};

class Story373 : public Story::Base
{
public:
    Story373()
    {
        ID = 373;

        Text = "Scriptor looks closely at the ring through his jeweller's lens, then hands it back to you with a frown. \"This is a very dangerous item indeed,\" he explains. \"It is cursed, and will bring disaster on anyone who tries to use it.\"\n\n\"How do you use it?\" wonders Blutz, reaching for the ring.\n\nYou snatch it back. \"We don't.\"\n\nOakley gives the doctor a shrewd look. \"This wouldn't just be your way of getting us to sell the ring cheap, would it, Doc?\" he mutters.\n\nScriptor splutters with outrage. \"Certainly not! I want nothing to do with it. In fact, I shall not even ask my usual fee of one doubloon for the consultation, since it is unlucky to seek profit from a cursed item.\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Ask to identify the BAT-SHAPED TALISMAN", 335, {Item::BAT_SHAPED_TALISMAN}));
        Choices.push_back(Choice::Base("... the BRONZE HELMET", 354, {Item::BRONZE_HELMET}));
        Choices.push_back(Choice::Base("... the CONCH-SHELL HORN", 316, {Item::CONCH_SHELL_HORN}));
        Choices.push_back(Choice::Base("It's time you were on your way", 392));

        Controls = Story::Controls::STANDARD;
    }
};

class Story374 : public Story::Base
{
public:
    Story374()
    {
        ID = 374;

        Image = "images/master-kemp-green.png";

        Text = "You make your way to the eastern edge of town and along the boardwalk into the shipyard. Labourers scurry to and from ignoring you, for it is their busiest season with the hurricane just a month away. A dozen ships lie here careened -- raised up on dry land and tilted on one side so that repairs or routine maintenance can be carried out. The new vessels stand in stocks further back from the water's edge, in varying degrees of construction. You see stacks of oak planks which are used for the hulls, and long straight pine poles that will become the masts.\n\nThe Master Shipbuilder, Kemp, emerges from his workshop and comes hurrying over. He is a spare-framed fellow with grey mutton-chop whiskers around a face coloured red by harsh coast winds and nips of brandy wine. \"Greetings,\" he says. He is on the point of shaking hands when he remembers that his fingers are tarry from caulking the new ships. \"Ah well. How can I help?\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Tell him you want to buy a ship", 43));
        Choices.push_back(Choice::Base("Enquire whether he has done any work for Skarvench recently", 63));
        Choices.push_back(Choice::Base("Ask him about the ship Cold Grue", 82));

        Controls = Story::Controls::STANDARD;
    }
};

class Story375 : public Story::Base
{
public:
    Story375()
    {
        ID = 375;

        Text = "The shipbuilder shows you a small sloop with ten cannon. \"Is that all you can sell us?\" protests Grimes. \"She's hardly a suitable vessel for hard piracy.\"\n\nThe shipbuilder shrugs. \"This is the best I can offer for the price. Her previous owner ran her up and down the SIdonian Main trading in various goods -- the cannons were only installed as a defensive measure against piracy, ironically enough,\" Seeing your disgruntled expression, he adds, \"She does still have a small consignment of salt aboard. It was still in the hold when she came into my hands. I'll throw that in for free.\"\n\n\"Salt? Most generous of you. Still, she'll have to do.\" And, so saying, you take possession of the LADY OF SHALOTT.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    void Event(Character::Base &player)
    {
        Character::TAKE_SHIP(player, Ship::LADY_OF_SHALOTT);
    }

    int Continue(Character::Base &player) { return 300; }
};

class Story376 : public Story::Base
{
public:
    Story376()
    {
        ID = 376;

        Text = "The next few days see an upswing in your fortunes as treasure ships, anxious to be well clear of the region before the onset of the hurricane season, come sailing to your clutches like fish into a net. You board three well-laden galleons and carry off a fine haul in gold coins, jewelled trinkets and rich sea-coloured silks.\n\nYou pace to and fro as Blutz's quill scrapes on the pages of the account book, tracing the growth of your riches. At last he looks up with a sigh, sets aside his quill and cracks his knuckles. You, Grimes and Oakley leap forward like three expectant fathers waiting for midwife's news. \"Well?\"\n\n\"We've enough loot to buy us one of the finest warships on the Carab Sea,\" declares Blutz with a broad grin.\n\n\"Excellent news,\" You race up on deck. \"Hoist the mainsail! Helmsman, five points to starboard! We've bound for home.\"\n\nA cry from the crow's nest warns of a dark cloud on your horizon of hope. \"A Gloriannic warship in sight off the port bow!\" calls the lookout. \"She's raising signals. The order is for us to heave to and prepare to be boarded.\"\n\n\"Brandy and bilge-water!\" swears Grimes, joining you on the poopdeck. \"What's it to be, cap'n -- do we let those lubbers come aboard, or give 'em a run for their money?\"";

        Choices.clear();
        Choices.push_back(Choice::Base("Drop sail and allow the warship to come alongside", 24));
        Choices.push_back(Choice::Base("Try outrunning her", 214));
        Choices.push_back(Choice::Base("Turn and make a fight of it", 252));

        Controls = Story::Controls::STANDARD;
    }
};

class Story377 : public Story::Base
{
public:
    Story377()
    {
        ID = 377;

        Text = "The search for clues becomes an obsession, driving you to sleepless nights and foolhardy risks. You begin to frequent the roughest taverns of Leshand -- places where a careless word can get your throat cut. Hardened villains scowl at your urgent questioning, but you soon discover that the name of El Draque seals all lips. \"But he's dead,\" you protest, \"hanged at sea more than a month ago.\"\n\nThey watch you in silence until one old sailor summons the courage to speak. \"Then how come I seen him on the deck of his vessel not one week since, drenched in moonlight and shrieking fit to burst?\"\n\nAnother seizes you by the collar. \"The grave's not more than a temporary berth for El Draque. But no one will be saying that of you, if you keep on poking your nose about!\"\n\nYou are finally forced to set sail back to Selenice empty handed.";

        Choices.clear();

        Controls = Story::Controls::STANDARD;
    }

    int Continue(Character::Base &player) { return 396; }
};

class Story378 : public Story::Base
{
public:
    Story378()
    {
        ID = 378;

        Text = "Your obsessive search for the iceberg drives you to steer course far off the known shipping lanes. At first, in awe of your reputation as a mariner, the crew toil on without complaint. But then the days draw by with no sight of land or other ships, and the grumbling begins. To begin with it takes the form of simple discontent -- a spluttered curse when a man bites into an apple from the deck-barrel and finds it rotten, or a surly rejoinder when orders are given. Oakley, Grimes and Blutz do their best to keep discipline, but the sun beats down day after day until the pitch bubbles in the seams and the sails blaze too bright to look at. Water begins to run low, and it is then that the grumbling begins to veer towards outright mutiny.";

        Choices.clear();
        Choices.push_back(Choice::Base("Press on regardless to the west", 56));
        Choices.push_back(Choice::Base("... or east of your current position", 93));
        Choices.push_back(Choice::Base("Abandon the search and return to Selenice", 396));

        Controls = Story::Controls::STANDARD;
    }
};

class Story379 : public Story::Base
{
public:
    Story379()
    {
        ID = 379;

        Text = "More flashes show from the Moon Dog's guns, but these shells go booming harmlessly beyond your bows, hissing to the deep below. You are now almost within grappling distance of the enemy ship.";

        Choices.clear();
        Choices.push_back(Choice::Base("Ram her at full sail", 25));
        Choices.push_back(Choice::Base("Close alongside for boarding", 415));

        Controls = Story::Controls::STANDARD;
    }
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
auto story160 = Story160();
auto story161 = Story161();
auto story162 = Story162();
auto story163 = Story163();
auto story164 = Story164();
auto story165 = Story165();
auto story166 = Story166();
auto story167 = Story167();
auto event167 = Event167();
auto story168 = Story168();
auto story169 = Story169();
auto story170 = Story170();
auto story171 = Story171();
auto story172 = Story172();
auto story173 = Story173();
auto story174 = Story174();
auto story175 = Story175();
auto story176 = Story176();
auto story177 = Story177();
auto story178 = Story178();
auto story179 = Story179();
auto story180 = Story180();
auto story181 = Story181();
auto story182 = Story182();
auto story183 = Story183();
auto story184 = Story184();
auto story185 = Story185();
auto story186 = Story186();
auto story187 = Story187();
auto story188 = Story188();
auto story189 = Story189();
auto story190 = Story190();
auto story191 = Story191();
auto story192 = Story192();
auto story193 = Story193();
auto story194 = Story194();
auto story195 = Story195();
auto story196 = Story196();
auto story197 = Story197();
auto story198 = Story198();
auto story199 = Story199();
auto story200 = Story200();
auto story201 = Story201();
auto story202 = Story202();
auto story203 = Story203();
auto story204 = Story204();
auto story205 = Story205();
auto story206 = Story206();
auto story207 = Story207();
auto story208 = Story208();
auto story209 = Story209();
auto story210 = Story210();
auto story211 = Story211();
auto story212 = Story212();
auto story213 = Story213();
auto story214 = Story214();
auto story215 = Story215();
auto story216 = Story216();
auto story217 = Story217();
auto story218 = Story218();
auto story219 = Story219();
auto story220 = Story220();
auto story221 = Story221();
auto story222 = Story222();
auto story223 = Story223();
auto story224 = Story224();
auto story225 = Story225();
auto event225 = Event225();
auto story226 = Story226();
auto story227 = Story227();
auto story228 = Story228();
auto story229 = Story229();
auto story230 = Story230();
auto story231 = Story231();
auto story232 = Story232();
auto story233 = Story233();
auto story234 = Story234();
auto story235 = Story235();
auto story236 = Story236();
auto story237 = Story237();
auto story238 = Story238();
auto story239 = Story239();
auto story240 = Story240();
auto story241 = Story241();
auto story242 = Story242();
auto story243 = Story243();
auto story244 = Story244();
auto story245 = Story245();
auto story246 = Story246();
auto story247 = Story247();
auto story248 = Story248();
auto story249 = Story249();
auto story250 = Story250();
auto story251 = Story251();
auto story252 = Story252();
auto story253 = Story253();
auto story254 = Story254();
auto story255 = Story255();
auto story256 = Story256();
auto story257 = Story257();
auto story258 = Story258();
auto story259 = Story259();
auto story260 = Story260();
auto story261 = Story261();
auto story262 = Story262();
auto story263 = Story263();
auto story264 = Story264();
auto story265 = Story265();
auto story266 = Story266();
auto story267 = Story267();
auto story268 = Story268();
auto story269 = Story269();
auto story270 = Story270();
auto story271 = Story271();
auto story272 = Story272();
auto story273 = Story273();
auto story274 = Story274();
auto story275 = Story275();
auto story276 = Story276();
auto story277 = Story277();
auto story278 = Story278();
auto story279 = Story279();
auto story280 = Story280();
auto story281 = Story281();
auto story282 = Story282();
auto story283 = Story283();
auto story284 = Story284();
auto story285 = Story285();
auto story286 = Story286();
auto story287 = Story287();
auto story288 = Story288();
auto story289 = Story289();
auto story290 = Story290();
auto story291 = Story291();
auto story292 = Story292();
auto story293 = Story293();
auto story294 = Story294();
auto story295 = Story295();
auto story296 = Story296();
auto story297 = Story297();
auto story298 = Story298();
auto story299 = Story299();
auto story300 = Story300();
auto story301 = Story301();
auto story302 = Story302();
auto story303 = Story303();
auto story304 = Story304();
auto story305 = Story305();
auto story306 = Story306();
auto story307 = Story307();
auto story308 = Story308();
auto story309 = Story309();
auto story310 = Story310();
auto event310 = Event310();
auto story311 = Story311();
auto story312 = Story312();
auto story313 = Story313();
auto story314 = Story314();
auto story315 = Story315();
auto story316 = Story316();
auto event316 = Event316();
auto story317 = Story317();
auto story318 = Story318();
auto story319 = Story319();
auto story320 = Story320();
auto story321 = Story321();
auto story322 = Story322();
auto story323 = Story323();
auto story324 = Story324();
auto story325 = Story325();
auto story326 = Story326();
auto story327 = Story327();
auto story328 = Story328();
auto story329 = Story329();
auto story330 = Story330();
auto story331 = Story331();
auto story332 = Story332();
auto story333 = Story333();
auto story334 = Story334();
auto event335 = Event335();
auto story335 = Story335();
auto story336 = Story336();
auto story337 = Story337();
auto story338 = Story338();
auto story339 = Story339();
auto story340 = Story340();
auto story341 = Story341();
auto story342 = Story342();
auto story343 = Story343();
auto story344 = Story344();
auto story345 = Story345();
auto story346 = Story346();
auto story347 = Story347();
auto story348 = Story348();
auto story349 = Story349();
auto story350 = Story350();
auto story351 = Story351();
auto story352 = Story352();
auto story353 = Story353();
auto story354 = Story354();
auto event354 = Event354();
auto story355 = Story355();
auto story356 = Story356();
auto story357 = Story357();
auto story358 = Story358();
auto story359 = Story359();
auto story360 = Story360();
auto story361 = Story361();
auto story362 = Story362();
auto story363 = Story363();
auto story364 = Story364();
auto story365 = Story365();
auto story366 = Story366();
auto story367 = Story367();
auto story368 = Story368();
auto story369 = Story369();
auto story370 = Story370();
auto story371 = Story371();
auto story372 = Story372();
auto story373 = Story373();
auto story374 = Story374();
auto story375 = Story375();
auto story376 = Story376();
auto story377 = Story377();
auto story378 = Story378();
auto story379 = Story379();

void InitializeStories()
{
    Stories = {
        &event059, &event117, &event167, &event225, &event310, &event316, &event335, &event354,
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
        &story150, &story151, &story152, &story153, &story154, &story155, &story156, &story157, &story158, &story159,
        &story160, &story161, &story162, &story163, &story164, &story165, &story166, &story167, &story168, &story169,
        &story170, &story171, &story172, &story173, &story174, &story175, &story176, &story177, &story178, &story179,
        &story180, &story181, &story182, &story183, &story184, &story185, &story186, &story187, &story188, &story189,
        &story190, &story191, &story192, &story193, &story194, &story195, &story196, &story197, &story198, &story199,
        &story200, &story201, &story202, &story203, &story204, &story205, &story206, &story207, &story208, &story209,
        &story210, &story211, &story212, &story213, &story214, &story215, &story216, &story217, &story218, &story219,
        &story220, &story221, &story222, &story223, &story224, &story225, &story226, &story227, &story228, &story229,
        &story230, &story231, &story232, &story233, &story234, &story235, &story236, &story237, &story238, &story239,
        &story240, &story241, &story242, &story243, &story244, &story245, &story246, &story247, &story248, &story249,
        &story250, &story251, &story252, &story253, &story254, &story255, &story256, &story257, &story258, &story259,
        &story260, &story261, &story262, &story263, &story264, &story265, &story266, &story267, &story268, &story269,
        &story270, &story271, &story272, &story273, &story274, &story275, &story276, &story277, &story278, &story279,
        &story280, &story281, &story282, &story283, &story284, &story285, &story286, &story287, &story288, &story289,
        &story290, &story291, &story292, &story293, &story294, &story295, &story296, &story297, &story298, &story299,
        &story300, &story301, &story302, &story303, &story304, &story305, &story306, &story307, &story308, &story309,
        &story310, &story311, &story312, &story313, &story314, &story315, &story316, &story317, &story318, &story319,
        &story320, &story321, &story322, &story323, &story324, &story325, &story326, &story327, &story328, &story329,
        &story330, &story331, &story332, &story333, &story334, &story335, &story336, &story337, &story338, &story339,
        &story340, &story341, &story342, &story343, &story344, &story345, &story346, &story347, &story348, &story349,
        &story350, &story351, &story352, &story353, &story354, &story355, &story356, &story357, &story358, &story359,
        &story360, &story361, &story362, &story363, &story364, &story365, &story366, &story367, &story368, &story369,
        &story370, &story371, &story372, &story373, &story374, &story375, &story376, &story377, &story378, &story379};
}

#endif