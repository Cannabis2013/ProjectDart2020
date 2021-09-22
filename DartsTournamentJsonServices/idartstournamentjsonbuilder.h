#ifndef IDARTSTOURNAMENTJSONBUILDER_H
#define IDARTSTOURNAMENTJSONBUILDER_H

#include "itournamentjsonbuilder.h"
#include "abstractdartstournament.h"
class IDartsTournamentJsonBuilder : public ITournamentJsonBuilder<IModel<QUuid>,QByteArray>
{};
#endif // ICREATEJSONFROMDARTSTOURNAMENT_H
