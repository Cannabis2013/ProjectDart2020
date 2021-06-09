#ifndef ABSTRACTROUTEBYDISPLAYHINT_H
#define ABSTRACTROUTEBYDISPLAYHINT_H

#include "abstractdartscontroller.h"
#include "AbstractApplicationInterface.h"

class AbstractRouteByDisplayHint : public QObject
{
    Q_OBJECT
public slots:
    virtual void processDartsController(AbstractDartsController* controller, const int & displayHint) = 0;

signals:
    void sendDartsPointSingleAttempt(AbstractDartsController* controller);
    void sendDartsScoreMultiAttempt(AbstractDartsController* controller);

};

#endif // ABSTRACTROUTEBYDISPLAYHINT_H
