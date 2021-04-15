#ifndef ABSTRACTCONTROLLERBUILDER_H
#define ABSTRACTCONTROLLERBUILDER_H

#include "IControllerBuilder.h"
#include <quuid.h>
#include "abstractgamecontroller.h"
#include "AbstractApplicationInterface.h"

typedef IControllerBuilder<AbstractGameController,
                           AbstractModelsContext,
                           AbstractApplicationInterface,
                           QByteArray> ControllerBuilderInterface;

class AbstractControllerBuilder : public QObject,
        public ControllerBuilderInterface
{
    Q_OBJECT
signals:
    void requestFTPDetails(const QUuid &tournament);
    void sendController(AbstractGameController* controller);

public slots:
    virtual void determineTournamentGameMode(const QUuid& tournament,
                                       const int &gameMode) = 0;
    virtual AbstractGameController* assembleFTPGameController(const QByteArray&,
                                                              AbstractApplicationInterface*,
                                                              AbstractModelsContext*) = 0;
};

#endif // ABSTRACTCONTROLLERBUILDER_H
