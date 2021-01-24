#ifndef ABSTRACTCONTROLLERBUILDER_H
#define ABSTRACTCONTROLLERBUILDER_H

#include "IControllerBuilder.h"
#include <quuid.h>
#include<qlist.h>
#include "abstractgamecontroller.h"
typedef IControllerBuilder<AbstractGameController,
                           QUuid,QVector<int>,
                           QVector<QUuid>,
                           QVector<QString>,
                           QVector<int>> ControllerBuilder;

class AbstractControllerBuilder : public QObject,
        public ControllerBuilder
{
    Q_OBJECT
signals:
    void requestFTPDetails(const QUuid &tournament);
    void sendController(AbstractGameController* controller);

public slots:
    virtual void handleRecieveGameMode(const QUuid& tournament,
                                       const int &gameMode) = 0;
    virtual AbstractGameController* assembleFTPGameController(const QVector<QUuid>& tournamentIdAndWinner,
                                                              const QVector<int>& values,
                                                              const QVector<QUuid>& userIds,
                                                              const QVector<QString>& userNames) = 0;
};

#endif // ABSTRACTCONTROLLERBUILDER_H
