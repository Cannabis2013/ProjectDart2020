#ifndef ABSTRACTDCBUILDER_H
#define ABSTRACTDCBUILDER_H

#include <quuid.h>
#include "DartsController/ControllerSLA/abstractdartscontroller.h"
#include "DartApplication/SLAs/AbstractApplicationInterface.h"

class AbstractDCBuilder : public QObject
{
    Q_OBJECT
public slots:
    virtual void createController(const QByteArray &json) = 0;
signals:
    void sendController(AbstractDartsController* controller);
};
#endif // ABSTRACTDCBUILDER_H
