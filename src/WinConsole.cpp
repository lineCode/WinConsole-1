#include "WinConsole.h"
#include <Windows.h>

namespace
{
    HANDLE getOutHandle()
    {
        return GetStdHandle(STD_OUTPUT_HANDLE);
    }

    HANDLE getInHandle()
    {
        return GetStdHandle(STD_INPUT_HANDLE);
    }

    CONSOLE_SCREEN_BUFFER_INFO getScreenBufferInfo()
    {
        CONSOLE_SCREEN_BUFFER_INFO info;

        GetConsoleScreenBufferInfo(getOutHandle(), &info);

        return info;
    }

    unsigned char getForegroundColorBits()
    {
        CONSOLE_SCREEN_BUFFER_INFO info = getScreenBufferInfo();

        WORD attributes = info.wAttributes;

        unsigned char lowerNibble = attributes & 0xF;

        return lowerNibble;
    }

    unsigned char getBackgroundColorBits()
    {
        CONSOLE_SCREEN_BUFFER_INFO info = getScreenBufferInfo();

        WORD attributes = info.wAttributes;

        unsigned char higherNibble = (attributes & 0xF0) >> 4;

        return higherNibble;
    }
}

namespace con
{
    void setTitle(const std::string & title)
    {
        SetConsoleTitle(title.c_str());
    }

    std::string getTitle()
    {
        char buffer[1024];

        GetConsoleTitle(buffer, sizeof(buffer));

        return std::string(buffer);
    }

    void setCursorPosition(int x, int y)
    {
        COORD coord;

        coord.X = x;
        coord.Y = y;

        SetConsoleCursorPosition(getOutHandle(), coord);
    }

    void setCursorPosition(const Position & position)
    {
        setCursorPosition(position.x, position.y);
    }

    Position getCursorPosition()
    {
        CONSOLE_SCREEN_BUFFER_INFO info = getScreenBufferInfo();

        Position position;

        position.x = info.dwCursorPosition.X;
        position.y = info.dwCursorPosition.Y;

        return position;
    }

    void clear()
    {
        COORD begin;

        begin.X = 0;
        begin.Y = 0;

        CONSOLE_SCREEN_BUFFER_INFO info = getScreenBufferInfo();

        int size = info.dwSize.X*info.dwSize.Y;

        DWORD written;

        FillConsoleOutputCharacter(getOutHandle(), ' ', size, begin, &written);

        FillConsoleOutputAttribute(getOutHandle(), info.wAttributes, size, begin, &written);

        setCursorPosition(0, 0);
    }

    void setForegroundColor(Color color)
    {
        WORD attributes = (getBackgroundColorBits() << 4) | ((int) color);

        SetConsoleTextAttribute(getOutHandle(), attributes);
    }

    void setBackgroundColor(Color color)
    {
        WORD attributes = ((int) color << 4) | getForegroundColorBits();

        SetConsoleTextAttribute(getOutHandle(), attributes);
    }

    Color getForegroundColor()
    {
        return (Color) getForegroundColorBits();
    }

    Color getBackgroundColor()
    {
        return (Color) getBackgroundColorBits();
    }

    std::ostream & operator<<(std::ostream & out, Color color)
    {
        setForegroundColor(color);

        return out;
    }
}