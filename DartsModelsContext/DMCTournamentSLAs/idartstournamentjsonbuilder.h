#ifndef IDARTSTOURNAMENTJSONBUILDER_H
#define IDARTSTOURNAMENTJSONBUILDER_H

#include "DartsModelsContext/DMCTournamentSLAs/abstractdartstournament.h"
class IDartsTournamentJsonBuilder
{
public:
    virtual QByteArray createJson(const QVector<const IModel<QUuid> *> &tournaments) const = 0;
    virtual QByteArray createJson(const IModel<QUuid> *tournament) const  = 0;
};
#endif // ICREATEJSONFROMDARTSTOURNAMENT_H
