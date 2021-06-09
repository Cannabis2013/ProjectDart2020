#ifndef ROUTEBYINPUTHINT_H
#define ROUTEBYINPUTHINT_H

#include "abstractroutebydisplayhint.h"

class RouteDartsByDisplayHint : public AbstractRouteByDisplayHint
{
public:
    /*
     * Public types
     */
    enum DisplayHint{
        SingleAttempt = 0x4,
        MultiAttempt = 0x8
    };
public slots:
    void processDartsController(AbstractDartsController *controller, const int &displayHint) override;
};

#endif // ROUTEBYINPUTHINT_H
