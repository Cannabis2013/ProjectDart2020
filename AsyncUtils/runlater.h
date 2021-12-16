#ifndef RUNLATER_H
#define RUNLATER_H
#include <QFutureWatcher>
#include <iostream>
#include <qfuture.h>
#include <quuid.h>
class RunLater
{
public:
    template<typename T = void>
    static void run(const QFuture<T> &future,std::function<void(const T&)> funct)
    {
        auto watcher = new QFutureWatcher<T>();
        QObject::connect(watcher,&QFutureWatcherBase::finished, [=](){
            funct(future.result());
            delete watcher;
        });
        watcher->setFuture(future);
    }
    template<typename T = void>
    static void run(const QFuture<T> &future,std::function<void()> funct)
    {
        auto watcher = new QFutureWatcher<T>();
        QObject::connect(watcher,&QFutureWatcherBase::finished, [=](){
            funct();
            delete watcher;
        });
        watcher->setFuture(future);
    }
};
#endif // RUNLATER_H
