#ifndef ABSTRACTDCBUILDER_H
#define ABSTRACTDCBUILDER_H

#include <quuid.h>
#include "abstractdartscontroller.h"
#include "AbstractApplicationInterface.h"

class AbstractDCBuilder : public QObject
{
    Q_OBJECT
public slots:
    virtual void createController(const QByteArray &json) = 0;
signals:
    void sendController(AbstractDartsController* controller);
};
#endif // ABSTRACTDCBUILDER_H
