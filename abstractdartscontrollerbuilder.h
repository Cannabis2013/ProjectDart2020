#ifndef ABSTRACTCONTROLLERBUILDER_H
#define ABSTRACTCONTROLLERBUILDER_H

#include "IControllerBuilder.h"
#include <quuid.h>
#include "abstractdartscontroller.h"
#include "AbstractApplicationInterface.h"

typedef IControllerBuilder<AbstractGameController,
                           QByteArray> ControllerBuilderInterface;

class AbstractDartsControllerBuilder : public QObject,
        public ControllerBuilderInterface
{
    Q_OBJECT

public slots:
    virtual AbstractGameController* buildDartsController(const QByteArray& json) = 0;
signals:
    void requestDartsDetails(const QUuid &tournament);
    void sendController(AbstractDartsController* controller,const int &displayHint);
};

#endif // ABSTRACTCONTROLLERBUILDER_H
