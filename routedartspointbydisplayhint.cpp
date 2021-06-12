#include "routedartspointbydisplayhint.h"

void RouteDartsPointByDisplayHint::determineRouteByDisplayHint(const int &hint)
{
    if(hint == SingleColumn)
        emit dartsSingleColumnInitialized();
    else if(hint == MultiColumn)
        emit dartsMultiColumnInitialized();
    else
        throw "ILLEGAL DISPLAY HINT";
}
