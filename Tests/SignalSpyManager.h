#ifndef SIGNALSPYMANAGER_H
#define SIGNALSPYMANAGER_H
#include <QSignalSpy>
#include <QTimer>
#include <qfuture.h>
#include <qobject.h>
#include <QtConcurrent/QtConcurrent>
#define DEFAULT_WAIT_TIME 750
#define Q_AWAIT(x){TestEventLoop::wait(DEFAULT_WAIT_TIME);}
class SigSpyMng
{
public:
    typedef QVector<QVariant> Args;
    SigSpyMng(QObject *obj, const char *sig)
    {
        _spy = new QSignalSpy(obj,sig);
    }
    ~SigSpyMng()
    {
        delete _spy;
    }
    QFuture<QVector<QVariant>> startListening(const int &waitTime = DEFAULT_WAIT_TIME)
    {
        return QtConcurrent::run([this,waitTime]{
            bool timeUp = false;
            QTimer timer;
            timer.start(waitTime);
            while (_spy->count() <= 0 && !timeUp) {
                if(timer.remainingTime() == 0)
                    timeUp = true;
            }
            if(timeUp)
                return Args();
            auto sigArgs = _spy->takeFirst().toVector();
            if(sigArgs.count() > 0)
                return sigArgs;
            return Args() << true;
        });
    }
private:
    QSignalSpy *_spy;
};
#endif // SIGNALSPYMANAGER_H
