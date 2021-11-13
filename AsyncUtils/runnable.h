#ifndef RUNNABLE_H
#define RUNNABLE_H
#include <QFutureWatcher>
#include <iostream>
#include <qfuture.h>
#include <quuid.h>
#include "ModelsContext/ModelsSLAs/imodel.h"
class Runnable
{
public:
    template<typename T>
    static void runLater(std::function<void()> funct, const QFuture<T> &future)
    {
        auto watcher = new QFutureWatcher<T>();
        QObject::connect(watcher,&QFutureWatcherBase::finished, [=](){
            funct();
            delete watcher;
        });
        watcher->setFuture(future);
    }
};
#endif // RUNNABLE_H
