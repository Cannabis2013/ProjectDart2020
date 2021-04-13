#ifndef SIGNALSPY_H
#define SIGNALSPY_H

#include <qeventloop.h>
#include <qtimer.h>

class TestEventLoop
{
public:
    TestEventLoop()
    {
    }
    static int wait(const int& ms)
    {
        auto _loop = new QEventLoop();
        QTimer timer;
        QObject::connect(&timer,&QTimer::timeout,_loop,&QEventLoop::quit);
        timer.start(ms);
        auto r = _loop->exec();
        return r;
    }
};

#endif // SIGNALSPY_H
