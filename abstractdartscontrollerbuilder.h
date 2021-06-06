#ifndef ABSTRACTCONTROLLERBUILDER_H
#define ABSTRACTCONTROLLERBUILDER_H

#include "IControllerBuilder.h"
#include <quuid.h>
#include "abstractgamecontroller.h"
#include "AbstractApplicationInterface.h"

typedef IControllerBuilder<AbstractGameController,
                           AbstractModelsService,
                           AbstractApplicationInterface,
                           QByteArray> ControllerBuilderInterface;

class AbstractDartsControllerBuilder : public QObject,
        public ControllerBuilderInterface
{
    Q_OBJECT
signals:
    void requestDartsDetails(const QUuid &tournament);
    void sendController(AbstractGameController* controller);

public slots:
    virtual AbstractGameController* assembleDartsGameController(const QByteArray&,
                                                              AbstractApplicationInterface*,
                                                              AbstractModelsService*) = 0;
};

#endif // ABSTRACTCONTROLLERBUILDER_H
