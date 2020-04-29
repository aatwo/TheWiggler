#ifndef WIGGLEINPUT_H
#define WIGGLEINPUT_H

#include <QObject>

class WiggleInput
{
    public:

        static void moveMouseRelative(long x, long y);
        static void moveMouseAbsolute(long x, long y);

    private:

#ifdef Q_OS_WIN
        static void moveMouseRelative_Win(long x, long y);
        static void moveMouseAbsolute_Win(long x, long y);
#endif

#ifdef Q_OS_OSX
        static void moveMouseRelative_OSX(long x, long y);
        static void moveMouseAbsolute_OSX(long x, long y);
#endif

#ifdef Q_OS_LINUX
        static void moveMouseRelative_Lin(long x, long y);
        static void moveMouseAbsolute_Lin(long x, long y);
#endif
};

#endif // WIGGLEINPUT_H
