#ifndef REPLYTIMEOUT_H
#define REPLYTIMEOUT_H

#include <qobject.h>
#include <qnetworkreply.h>
#include <qbasictimer.h>
#include <QTimerEvent>
#include <iostream>

using namespace std;

class ReplyTimeout : public QObject
{
    Q_OBJECT
public:

    enum HandleMethod { Abort, Close };
    ReplyTimeout(QNetworkReply* reply,
                 const int timeout,
                 HandleMethod method = Abort,
                 QObject* reciever = nullptr,
                 const char* timeoutSlot = nullptr) :
        QObject(reply), _method(method)
    {
        if(timeoutSlot != nullptr && reciever != nullptr)
            connect(this,SIGNAL(timeoutOccured()),reciever,timeoutSlot);
        if (reply->isRunning())
        {
          _timer.start(timeout, this);
          connect(reply, &QNetworkReply::finished, this, &QObject::deleteLater);
        }
    }
    static void setTimer(QNetworkReply* reply,
                         const int timeout,
                         HandleMethod method = Abort,
                         QObject* reciever = nullptr,
                         const char* timeoutSlot = nullptr)
    {
        if(timeout > 5)
            new ReplyTimeout(reply, timeout,method,reciever,timeoutSlot);
    }

signals:
    void timeoutOccured();

protected:
    void timerEvent(QTimerEvent * ev)
    {
        if (!_timer.isActive() || ev->timerId() != _timer.timerId())
            return;
        auto reply = static_cast<QNetworkReply*>(parent());
        if (reply->isRunning())
        {
          if (_method == Close)
            reply->close();
          else if (_method == Abort)
            reply->abort();

          emit timeoutOccured();
        }
        _timer.stop();
    }

private:
    QBasicTimer _timer;
    HandleMethod _method;
};

#endif // REPLYTIMEOUT_H
