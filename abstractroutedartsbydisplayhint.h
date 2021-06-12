#ifndef ABSTRACTROUTEBYDISPLAYHINT_H
#define ABSTRACTROUTEBYDISPLAYHINT_H

#include "abstractdartscontroller.h"
#include "AbstractApplicationInterface.h"

class AbstractRouteDartsByDisplayHint : public QObject
{
    Q_OBJECT
public slots:
    virtual void determineRouteByDisplayHint(const int & displayHint) = 0;

signals:
    void dartsSingleColumnInitialized();
    void dartsMultiColumnInitialized();

};

#endif // ABSTRACTROUTEBYDISPLAYHINT_H
