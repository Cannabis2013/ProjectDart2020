#ifndef ABSTRACTROUTEBYHINT_H
#define ABSTRACTROUTEBYHINT_H

#include "DartsController/ControllerSLA/abstractdartscontroller.h"
#include "DartApplication/SLAs/AbstractApplicationInterface.h"

class AbstractRouteByHint : public QObject
{
    Q_OBJECT
public slots:
    virtual void routeByInputHint(const int &inputHint) = 0;
signals:
    void dartsPointSingleColumnInitialized();
    void dartsPointMultiColumnInitialized();
    void dartsScoreSingleColumnInitialized();
    void dartsScoreMultiColumnInitialized();

};

#endif // ABSTRACTROUTEBYDISPLAYHINT_H
