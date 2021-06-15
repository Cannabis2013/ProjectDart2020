#include "routebydisplayhint.h"

void RouteByDisplayHint::determineDartsPointRouteByDisplayHint(const int &displayHint)
{
    if(displayHint == SingleColumn)
        emit dartsPointSingleColumnInitialized();
    else if(displayHint == MultiColumn)
        emit dartsPointMultiColumnInitialized();
    else
        throw "ILLEGAL DISPLAY HINT";
}

void RouteByDisplayHint::determineDartsScoreRouteByDisplayHint(const int &displayHint)
{
    if(displayHint == SingleColumn)
        emit dartsScoreSingleColumnInitialized();
    else if(displayHint == MultiColumn)
        emit dartsScoreMultiColumnInitialized();
    else
        throw "ILLEGAL DISPLAY HINT";
}
