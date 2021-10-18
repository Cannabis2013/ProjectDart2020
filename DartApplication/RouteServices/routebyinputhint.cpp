#include "routebyinputhint.h"

void RouteByInputHint::routeByInputHint(const int &inputHint)
{
    if(inputHint == PointHint)
        emit dartsPointSingleColumnInitialized();
    else if(inputHint == ScoreHint)
        emit dartsScoreSingleColumnInitialized();
    else
        throw ILLEGAL_INPUT;
}
