#include "routerequestbytournamentid.h"

void RouteRequestByTournamentId::processTournamentDetails(const QByteArray &json, const int &inputHint)
{
    switch (inputHint) {
        case SingleAttempt : emit requestBuildDartsPointController(json);
        case MultiAttempt : emit requestBuildDartsScoreController(json);
    }
}
