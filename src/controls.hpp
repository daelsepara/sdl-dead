#ifndef __CONTROLS__HPP__
#define __CONTROLS__HPP__
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

namespace Control
{
    enum class Type
    {
        ANY = 0,
        ABOUT,
        SCROLL_UP,
        SCROLL_DOWN,
        MAP,
        CHART,
        CHARACTER,
        GAME,
        NEW,
        CUSTOM,
        LOAD,
        SAVE,
        SHOP,
        NEXT,
        GLOSSARY,
        ACTION,
        BACK,
        USE,
        DROP,
        CONFIRM,
        QUIT,
        PLUS,
        MINUS,
        TRADE,
        GIVE,
        STEAL,
        LOSE,
        YES,
        NO,
        BUY,
        SELL,
        BARTER,
        GENDER
    };

    class Base
    {
    public:
        int ID = -1;

        int Left = -1;
        int Right = -1;
        int Up = -1;
        int Down = -1;

        int X = 0;
        int Y = 0;

        int W = 0;
        int H = 0;

        Control::Type Type = Control::Type::ANY;
    };
}

class TextButton : public Control::Base
{
private:
    void construct(int id, const char *text, int left, int right, int up, int down, int x, int y, int w, int h)
    {
        ID = id;
        Text = text;
        Left = left;
        Right = right;
        Up = up;
        Down = down;
        X = x;
        Y = y;
        W = w;
        H = h;
    }

public:
    const char *Text = NULL;

    TextButton(int id, const char *text, int left, int right, int up, int down, int x, int y, int w, int h)
    {
        construct(id, text, left, right, up, down, x, y, w, h);
    }

    TextButton(int id, const char *text, int left, int right, int up, int down, int x, int y, int w, int h, Control::Type type)
    {
        Type = type;

        construct(id, text, left, right, up, down, x, y, w, h);
    }
};

class Button : public Control::Base
{
private:
    SDL_Surface *createImage(const char *file)
    {
        auto surface = IMG_Load(File);

        if (surface == NULL)
        {
            std::cerr << "Unable to load image " << file << "! SDL Error: " << SDL_GetError() << std::endl;
        }
        else
        {
            W = surface->w;
            H = surface->h;
        }

        return surface;
    }

    void construct(int id, const char *file, int left, int right, int up, int down, int x, int y)
    {
        ID = id;
        File = file;
        Left = left;
        Right = right;
        Up = up;
        Down = down;
        X = x;
        Y = y;

        Surface = createImage(file);
    }

    void construct(int id, int left, int right, int up, int down, int x, int y)
    {
        ID = id;
        Left = left;
        Right = right;
        Up = up;
        Down = down;
        X = x;
        Y = y;
    }

public:
    const char *File = NULL;

    SDL_Surface *Surface = NULL;

    Button()
    {
    }

    Button(int id, const char *file, int left, int right, int up, int down, int x, int y)
    {
        construct(id, file, left, right, up, down, x, y);
    }

    Button(int id, const char *file, int left, int right, int up, int down, int x, int y, Control::Type type)
    {
        Type = type;

        construct(id, file, left, right, up, down, x, y);
    }

    Button(int id, SDL_Surface *image, int left, int right, int up, int down, int x, int y, Control::Type type)
    {
        Type = type;

        Surface = image;

        if (Surface)
        {
            W = Surface->w;
            H = Surface->h;
        }

        construct(id, left, right, up, down, x, y);
    }

    // constructor for making deep copies of Button controls
    Button(const Button &src)
    {
        ID = src.ID;
        Type = src.Type;
        File = src.File;
        Left = src.Left;
        Right = src.Right;
        Up = src.Up;
        Down = src.Down;
        X = src.X;
        Y = src.Y;
        W = src.W;
        H = src.H;

        if (src.Surface)
        {
            Surface = SDL_ConvertSurface(src.Surface, src.Surface->format, 0);
        }
    }

    // operator overload for making deep copies of Button controls
    Button &operator=(const Button &src)
    {
        // self-assignment protection
        if (this != &src)
        {
            ID = src.ID;
            Type = src.Type;
            File = src.File;
            Left = src.Left;
            Right = src.Right;
            Up = src.Up;
            Down = src.Down;
            X = src.X;
            Y = src.Y;
            W = src.W;
            H = src.H;

            if (Surface)
            {
                SDL_FreeSurface(Surface);

                Surface = NULL;
            }

            if (src.Surface)
            {
                Surface = SDL_ConvertSurface(src.Surface, src.Surface->format, 0);
            }
        }

        return *this;
    }

    // free allocated surface
    ~Button()
    {
        if (Surface)
        {
            SDL_FreeSurface(Surface);

            Surface = NULL;
        }
    }
};
#endif
