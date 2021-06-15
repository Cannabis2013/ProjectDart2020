#ifndef ROUTEBYINPUTHINT_H
#define ROUTEBYINPUTHINT_H

#include "abstractroutedartsbydisplayhint.h"

class RouteByDisplayHint : public AbstractRouteDartsByDisplayHint
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
    void determineDartsPointRouteByDisplayHint(const int &displayHint) override;
    void determineDartsScoreRouteByDisplayHint(const int &displayHint) override;
};

#endif // ROUTEBYINPUTHINT_H
