#include "wiggleinput.h"

#ifdef Q_OS_WIN
    #include <Windows.h>
#endif

#ifdef Q_OS_OSX
#endif

void WiggleInput::moveMouseRelative(long x, long y)
{
#ifdef Q_OS_WIN
    moveMouseRelative_Win(x, y);
#endif
#ifdef Q_OS_OSX
    moveMouseRelative_OSX(x, y);
#endif
#ifdef Q_OS_LINUX
    moveMouseRelative_Lin(x, y);
#endif
}

void WiggleInput::moveMouseAbsolute(long x, long y)
{
#ifdef Q_OS_WIN
    moveMouseAbsolute_Win(x, y);
#endif
#ifdef Q_OS_OSX
    moveMouseAbsolute_OSX(x, y);
#endif
#ifdef Q_OS_LINUX
    moveMouseAbsolute_Lin(x, y);
#endif
}

#ifdef Q_OS_WIN
void WiggleInput::moveMouseRelative_Win(long x, long y)
{
    INPUT Input = { 0 };
    Input.type = INPUT_MOUSE;

    Input.mi.dx = (LONG)x;
    Input.mi.dy = (LONG)y;
    Input.mi.dwFlags = MOUSEEVENTF_MOVE;

    SendInput(1, &Input, sizeof(INPUT));
}

void WiggleInput::moveMouseAbsolute_Win(long x, long y)
{
    INPUT Input = { 0 };
    Input.type = INPUT_MOUSE;

    Input.mi.dx = (LONG)x;
    Input.mi.dy = (LONG)y;
    Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;

    SendInput(1, &Input, sizeof(INPUT));
}
#endif

#ifdef Q_OS_OSX
void WiggleInput::moveMouseRelative_OSX(long x, long y)
{

}

void WiggleInput::moveMouseAbsolute_OSX(long x, long y)
{

}
#endif

#ifdef Q_OS_LINUX
void WiggleInput::moveMouseRelative_Lin(long x, long y)
{

}

void WiggleInput::moveMouseAbsolute_Lin(long x, long y)
{

}
#endif
