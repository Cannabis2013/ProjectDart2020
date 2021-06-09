#include "routedartsbyinputhint.h"

void RouteDartsByInputHint::processTournamentDetails(const QByteArray &json, const int &inputHint)
{
    if(inputHint == PointHint)
        emit requestBuildDartsPointController(json);
    else if(inputHint == ScoreHint)
        emit requestBuildDartsScoreController(json);
    else
        throw "ILLEGAL INPUTHINT";
}
