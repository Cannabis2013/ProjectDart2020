#ifndef ROUTEREQUESTBYTOURNAMENTID_H
#define ROUTEREQUESTBYTOURNAMENTID_H

#include "abstractroutebyinputhint.h"

class RouteRequestByTournamentId : public AbstractRouteByInputHint
{
public:
    enum InputHint {
        SingleAttempt = 0x4,
        MultiAttempt = 0x8
    };
public slots:
    void processTournamentDetails(const QByteArray &json, const int &inputHint) override;
};



#endif // ROUTEREQUESTBYTOURNAMENTID_H
