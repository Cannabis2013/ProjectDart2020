#ifndef ICREATEDARTSTOURNAMENTSFROMJSON_H
#define ICREATEDARTSTOURNAMENTSFROMJSON_H

#include "DartTournamentsContext/DTCModelsSLAs/itournament.h"
#include "icreatefromjson.h"
class ICreateDartsTournamentModelsFromJson : public ICreateFromJson<QVector<const IModel<QUuid>*>>
{
public:
    virtual QVector<const IModel<QUuid>*> create(const QByteArray &json) const override = 0;
};

#endif // ICREATEDARTSTOURNAMENTFROMJSON_H
