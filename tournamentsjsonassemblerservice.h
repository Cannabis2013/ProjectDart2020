#ifndef TOURNAMENTSJSONASSEMBLER_H
#define TOURNAMENTSJSONASSEMBLER_H

#include "iunaryservice.h"

#include <qjsonarray.h>
#include <qjsonobject.h>
#include <qvector.h>
#include <imodel.h>
#include <dartstournament.h>

class TournamentsJSonAssemblerService :
        public IUnaryService<const QVector<const IDartsTournament*>&,QJsonArray>
{
public:
    QJsonArray service(const QVector<const IDartsTournament*>& models) override;
private:
    QJsonObject assembleJsonObjectFromDartsTournamentModel(const IDartsTournament* model);
    QJsonArray assembleJsonArrayFromTournamentPlayerIds(const QVector<QUuid>& players);
};


#endif // TOURNAMENTSJSONASSEMBLER_H
