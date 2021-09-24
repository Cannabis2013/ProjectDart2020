#ifndef ICREATEJSONFROMDARTSTOURNAMENT_H
#define ICREATEJSONFROMDARTSTOURNAMENT_H
#include "itojson.h"
#include "DartTournamentsContext/DTCModelsSLAs/itournament.h"
class ICreateJsonFromDartsTournaments : public IToJson<const QVector<const IModel<QUuid>*>&>
{
public:
    virtual QByteArray toJson(const QVector<const IModel<QUuid>*> &models) const override = 0;
};
#endif // ICREATEJSONFROMDARTSTOURNAMENT_H
