#ifndef ABSTRACTROUTEBYDISPLAYHINT_H
#define ABSTRACTROUTEBYDISPLAYHINT_H

#include "abstractdartscontroller.h"
#include "AbstractApplicationInterface.h"

class AbstractRouteByDisplayHint : public QObject
{
    Q_OBJECT
public slots:
    virtual void determineDartsPointRouteByDisplayHint(const int & displayHint) = 0;
    virtual void determineDartsScoreRouteByDisplayHint(const int & displayHint) = 0;
signals:
    void dartsPointSingleColumnInitialized();
    void dartsPointMultiColumnInitialized();
    void dartsScoreSingleColumnInitialized();
    void dartsScoreMultiColumnInitialized();

};

#endif // ABSTRACTROUTEBYDISPLAYHINT_H
