#ifndef ABSTRACTROUTEBYDISPLAYHINT_H
#define ABSTRACTROUTEBYDISPLAYHINT_H

#include "DartsController/ControllerSLA/abstractdartscontroller.h"
#include "DartApplication/SLAs/AbstractApplicationInterface.h"

class AbstractRouteByDisplayHint : public QObject
{
    Q_OBJECT
public slots:
    virtual void routeByHints(const int &inputHint,const int & displayHint) = 0;
signals:
    void dartsPointSingleColumnInitialized();
    void dartsPointMultiColumnInitialized();
    void dartsScoreSingleColumnInitialized();
    void dartsScoreMultiColumnInitialized();

};

#endif // ABSTRACTROUTEBYDISPLAYHINT_H
