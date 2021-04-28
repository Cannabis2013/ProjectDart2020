#ifndef TOURNAMENTSJSONASSEMBLER_H
#define TOURNAMENTSJSONASSEMBLER_H

#include "idartstournamentsjsonassemblerservice.h"

#include <qjsonarray.h>
#include <qjsonobject.h>
#include <qvector.h>
#include <imodel.h>
#include <dartstournamentmodel.h>

class TournamentsJSonAssemblerService : public IDartsTournamentsJsonAssemblerService<QJsonArray,QVector<const IModel<QUuid>*>>
{
public:
    QJsonArray assembleDartsTournamentsFromModels(const QVector<const IModel<QUuid>*>& models) override;
private:
    QJsonObject assembleJsonObjectFromDartsTournamentModel(const IDartsTournament<QUuid,QVector<QUuid>,QString>* model);
    QJsonArray assembleJsonArrayFromTournamentPlayerIds(const QVector<QUuid>& players);
};


#endif // TOURNAMENTSJSONASSEMBLER_H
