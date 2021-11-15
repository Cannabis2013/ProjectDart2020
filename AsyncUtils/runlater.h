#ifndef RUNLATER_H
#define RUNLATER_H
#include <QFutureWatcher>
#include <iostream>
#include <qfuture.h>
#include <quuid.h>
#include "ModelsContext/ModelsSLAs/imodel.h"
class RunLater
{
public:
    template<typename T>
    static void run(std::function<void()> funct,const QFuture<T> &future)
    {
        auto watcher = new QFutureWatcher<T>();
        QObject::connect(watcher,&QFutureWatcherBase::finished, [=](){
            funct();
            delete watcher;
        });
        watcher->setFuture(future);
    }
    template<typename T, typename U = T>
    static void run(std::function<void()> firstFunct, const QFuture<T> &first,
                    std::function<void()> secondFunct, const QFuture<U> &second)
    {
        auto firstWatcher = new QFutureWatcher<T>();
        auto secondWatcher = new QFutureWatcher<U>();
        QObject::connect(firstWatcher,&QFutureWatcherBase::finished, [=](){
            firstFunct();
            delete firstWatcher;
        });
        firstWatcher->setFuture(first);
        QObject::connect(secondWatcher,&QFutureWatcherBase::finished, [=](){
            secondFunct();
            delete secondWatcher;
        });
        secondWatcher->setFuture(second);
    }
};
#endif // RUNLATER_H
