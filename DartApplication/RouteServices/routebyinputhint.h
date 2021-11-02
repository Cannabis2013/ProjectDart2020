#ifndef ROUTEBYINPUTHINT_H
#define ROUTEBYINPUTHINT_H
#include "DartApplication/RouteSLAs/abstractroutebyhint.h"
#define ILLEGAL_INPUT "ILLEGAL INPUT HINT";
class RouteByInputHint : public AbstractRouteByHint
{
public:
    enum AbstractRouteByInputHint{
        PointHint = 0x5,
        ScoreHint = 0x6
    };
public slots:
    virtual void routeByInputHint(const int &inputHint) override
    {
        if(inputHint == PointHint)
            emit dartsPointInit();
        else if(inputHint == ScoreHint)
            emit dartsScoreInit();
        else
            throw ILLEGAL_INPUT;
    }
private:
};
#endif // ROUTEBYINPUTHINT_H
