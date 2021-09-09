#include "routebydisplayhint.h"

void RouteByDisplayHint::routeByHints(const int &inputHint, const int &displayHint)
{
    if(inputHint == PointHint)
        routeDPC(displayHint);
    else if(inputHint == ScoreHint)
        routeDSC(displayHint);
    else
        throw ILLEGAL_INPUT;
}

void RouteByDisplayHint::routeDPC(const int &displayHint)
{
    if(displayHint == SingleColumn)
        emit dartsPointSingleColumnInitialized();
    else if(displayHint == MultiColumn)
        emit dartsPointMultiColumnInitialized();
    else
        throw ILLEGAL_DISPLAY;
}

void RouteByDisplayHint::routeDSC(const int &displayHint)
{
    if(displayHint == SingleColumn)
        emit dartsScoreSingleColumnInitialized();
    else if(displayHint == MultiColumn)
        emit dartsScoreMultiColumnInitialized();
    else
        throw ILLEGAL_DISPLAY;
}
