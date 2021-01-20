#ifndef ABSTRACTCONTROLLERBUILDER_H
#define ABSTRACTCONTROLLERBUILDER_H

#include "IControllerBuilder.h"
#include <quuid.h>
#include<qlist.h>
#include "abstractgamecontroller.h"
typedef IControllerBuilder<AbstractGameController,
                           QUuid,QList<int>,
                           QList<QUuid>,
                           QList<QString>,
                           QList<int>> ControllerBuilder;

class AbstractControllerBuilder : public QObject,
        public ControllerBuilder
{
signals:
    void requestFTPDetails(const QUuid &tournament);
    void sendController(AbstractGameController* controller);

public slots:
    virtual void handleRecieveGameMode(const QUuid& tournament,
                                       const int &gameMode) = 0;
    virtual AbstractGameController* assembleFTPGameController(const QUuid& tournament,
                                   const QUuid& winner,
                                   const QList<int>& parameters,
                                   const QList<QUuid>& playerIds,
                                   const QList<QString>& playerNames) = 0;


};

#endif // ABSTRACTCONTROLLERBUILDER_H
