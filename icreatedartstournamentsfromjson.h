#ifndef ICREATEDARTSTOURNAMENTSFROMJSON_H
#define ICREATEDARTSTOURNAMENTSFROMJSON_H

#include "itournament.h"
#include "icreatefromjson.h"
class ICreateDartsTournamentModelsFromJson : public ICreateFromJson<QVector<const ITournament*>>
{
public:
    virtual QVector<const ITournament*> create(const QByteArray &json) const override = 0;
};

#endif // ICREATEDARTSTOURNAMENTFROMJSON_H
