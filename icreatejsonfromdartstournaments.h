#ifndef ICREATEJSONFROMDARTSTOURNAMENT_H
#define ICREATEJSONFROMDARTSTOURNAMENT_H
#include "icreatejsonfrom.h"
#include "itournament.h"
class ICreateJsonFromDartsTournaments : public ICreateJsonFrom<const QVector<const IModel<QUuid>*>&>
{
public:
    virtual QByteArray createJson(const QVector<const IModel<QUuid>*> &models) const override = 0;
};
#endif // ICREATEJSONFROMDARTSTOURNAMENT_H
