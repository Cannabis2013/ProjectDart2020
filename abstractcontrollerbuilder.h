#ifndef ABSTRACTCONTROLLERBUILDER_H
#define ABSTRACTCONTROLLERBUILDER_H

#include "IControllerBuilder.h"
#include <quuid.h>
#include "abstractgamecontroller.h"
#include "abstractmodelscontextinterface.h"
#include "AbstractApplicationInterface.h"

typedef IControllerBuilder<AbstractGameController,
                           AbstractModelsContextInterface,
                           AbstractApplicationInterface,
                           QVector<int>,
                           QVector<QUuid>,
                           QVector<QString>> ControllerBuilder;

class AbstractControllerBuilder : public QObject,
        public ControllerBuilder
{
    Q_OBJECT
signals:
    void requestFTPDetails(const QUuid &tournament);
    void sendController(AbstractGameController* controller);

public slots:
    virtual void determineTournamentGameMode(const QUuid& tournament,
                                       const int &gameMode) = 0;
    virtual AbstractGameController* assembleFTPGameController(const QVector<QUuid>& tournamentIdAndWinner,
                                                              const QVector<int>& values,
                                                              const QVector<QUuid>& userIds,
                                                              const QVector<QString>& userNames,
                                                              AbstractApplicationInterface* applicationInterface,
                                                              AbstractModelsContextInterface* modelsContext) = 0;
};

#endif // ABSTRACTCONTROLLERBUILDER_H
