#ifndef ROUTEBYINPUTHINT_H
#define ROUTEBYINPUTHINT_H

#include "abstractroutedartsbydisplayhint.h"

class RouteDartsPointByDisplayHint : public AbstractRouteDartsByDisplayHint
{
public:
    /*
     * Public types
     */
    enum DisplayHint{
        SingleColumn = 0x4,
        MultiColumn = 0x8
    };
public slots:
    void determineRouteByDisplayHint(const int &hint) override;
};

#endif // ROUTEBYINPUTHINT_H
