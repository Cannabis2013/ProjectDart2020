#ifndef ICREATEJSONFROMDARTSTOURNAMENT_H
#define ICREATEJSONFROMDARTSTOURNAMENT_H
#include "icreatejsonfrom.h"
#include "itournament.h"
class ICreateJsonFromDartsTournaments : public ICreateJsonFrom<const QVector<const ITournament*>&>
{
public:
    virtual QByteArray createJson(const QVector<const ITournament*> &models) const override = 0;
};
#endif // ICREATEJSONFROMDARTSTOURNAMENT_H
