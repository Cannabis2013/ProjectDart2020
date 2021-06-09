#ifndef ROUTEDARTSBYINPUTHINT_H
#define ROUTEDARTSBYINPUTHINT_H

#include "abstractroutebyinputhint.h"

class RouteDartsByInputHint : public AbstractRouteByInputHint
{
public:
    enum AbstractRouteByInputHint{
        PointHint = 0x4,
        ScoreHint = 0x8
    };
public slots:
    void processTournamentDetails(const QByteArray &json, const int &inputHint) override;
};

#endif // ROUTEDARTSBYINPUTHINT_H
