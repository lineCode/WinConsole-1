#ifndef WINCONSOLE_H
#define WINCONSOLE_H

#ifdef WINCONSOLE_EXPORTS
#define WINCONSOLE_API __declspec(dllexport) 
#else
#define WINCONSOLE_API __declspec(dllimport) 
#endif

#define API WINCONSOLE_API

#include <ostream>
#include <string>

namespace con
{
    struct Position
    {
        int x;
        int y;
    };

    struct Size
    {
        int width;
        int height;
    };

    enum class Color
    {
        BLACK,
        BLUE,
        GREEN,
        AQUA,
        RED,
        PURPLE,
        YELLOW,
        GRAY,
        DARK_GRAY,
        LIGHT_BLUE,
        LIGHT_GREEN,
        LIGHT_AQUA,
        LIGHT_RED,
        LIGHT_PURPLE,
        LIGHT_YELLOW,
        WHITE
    };

    API std::ostream & operator<<(std::ostream & out, Color color);

    API void setTitle(const std::string & title);

    API std::string getTitle();

    API void setCursorPosition(int x, int y);
    API void setCursorPosition(const Position & position);

    API Position getCursorPosition();

    API void clear();

    API void setForegroundColor(Color color);

    API void setBackgroundColor(Color color);

    API Color getForegroundColor();

    API Color getBackgroundColor();
}

#undef API

#endif