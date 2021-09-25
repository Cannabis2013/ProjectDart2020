#ifndef ROUTEBYINPUTHINT_H
#define ROUTEBYINPUTHINT_H

#include "DartApplication/RouteSLAs/abstractroutebydisplayhint.h"

#define ILLEGAL_DISPLAY "ILLEGAL DISPLAY HINT";
#define ILLEGAL_INPUT "ILLEGAL INPUT HINT";

class RouteByDisplayHint : public AbstractRouteByDisplayHint
{
public:
    /*
     * Public types
     */
    enum DisplayHint{
        SingleColumn = 0x4,
        MultiColumn = 0x8
    };
    enum AbstractRouteByInputHint{
        PointHint = 0x5,
        ScoreHint = 0x6
    };
public slots:
    virtual void routeByHints(const int &inputHint, const int &displayHint) override;
private:
    void routeDPC(const int &displayHint);
    void routeDSC(const int &displayHint);
};

#endif // ROUTEBYINPUTHINT_H
