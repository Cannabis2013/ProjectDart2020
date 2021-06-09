#include "routedartsbydisplayhint.h"

void RouteDartsByDisplayHint::processDartsController(AbstractDartsController *controller, const int &displayHint)
{
    if(displayHint == SingleAttempt)
        emit sendDartsPointSingleAttempt(controller);
    else if(displayHint == MultiAttempt)
        emit sendDartsScoreMultiAttempt(controller);
    else
        throw "ILLEGAL DISPLAY HINT";
}
