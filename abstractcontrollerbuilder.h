#ifndef ABSTRACTCONTROLLERBUILDER_H
#define ABSTRACTCONTROLLERBUILDER_H

#include "IControllerBuilder.h"
#include <quuid.h>
#include "abstractgamecontroller.h"
#include "abstractmodelscontext.h"
#include "AbstractApplicationInterface.h"

typedef IControllerBuilder<AbstractGameController,
                           AbstractModelsContext,
                           AbstractApplicationInterface,
                           QVector<int>,
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
    virtual void determineTournamentGameMode(const QUuid& tournament,
                                       const int &gameMode) = 0;
    virtual AbstractGameController* assembleFTPGameController(const QVector<QUuid>& tournamentIdAndWinner,
                                                              const QVector<int>& values,
                                                              const QVector<QUuid>& userIds,
                                                              const QVector<QString>& userNames,
                                                              const QVector<int>& playerScores,
                                                              AbstractApplicationInterface* applicationInterface,
                                                              AbstractModelsContext* modelsContext) = 0;
};

#endif // ABSTRACTCONTROLLERBUILDER_H
