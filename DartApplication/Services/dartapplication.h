#ifndef DARTAPPLICATION_H
#define DARTAPPLICATION_H
#include "DartApplication/SLAs/dartapplicationslas.h"
#include <QFuture>
#include <qfuturewatcher.h>
#include <functional>
class DartApplication : public AbstractApplicationInterface,
                        public DartApplicationSLAs
{
    Q_OBJECT
public:
    void addDartsTournaments(const QByteArray &json) override
    {
        auto future = playerModelsContext()->playerModels(json);
        runAsync([=](){
            _dartsModelsContext->addDartsTournament(json,future.result());
        },future);
    }
public slots:
    void setDartsController(AbstractGameController *controller) override
    {
        delete _gameController;
        _gameController = controller;
        connectServices()->connectDC()->connect(controller,this,_dartsModelsContext,routeServices()->routeByInputHint());
        emit requestWakeUp();
    }
private:
    void runAsync(std::function<void()> funct, const QFuture<QVector<IModel<QUuid>*>> &future)
    {
        auto watcher = new QFutureWatcher<QVector<IModel<QUuid>*>>();
        connect(watcher,&QFutureWatcherBase::finished, [=](){
            funct();
            delete watcher;
        });
        watcher->setFuture(future);
    }
};
#endif // DARTAPPLICATION_H
