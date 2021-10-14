#ifndef IDARTSTOURNAMENTBUILDER_H
#define IDARTSTOURNAMENTBUILDER_H

#include <qvector.h>
#include "DartsModelsContext/InputsDbSLAs/iplayerinput.h"

class IDartsTournamentBuilder
{
public:
    virtual IModel<QUuid> *createTournament(const QByteArray &json) const = 0;
    virtual QVector<IModel<QUuid>*> createTournaments(const QByteArray &json) const = 0;
};
#endif // ICREATEDARTSPOINTMODELFROMJSON_H
