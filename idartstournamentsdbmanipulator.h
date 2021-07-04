#ifndef IDARTSTOURNAMENTSDBMANIPULATOR_H
#define IDARTSTOURNAMENTSDBMANIPULATOR_H

#include <quuid.h>
#include "ipersistence.h"
#include "idartstournament.h"
#include "itournamentdbservice.h"
#include "idartstournamentdb.h"

class IDartsTournamentsDbManipulator : public
        ITournamentDbService<IDartsTournament,IDartsTournamentDb,QUuid,QString>
{};
#endif // IDARTSTOURNAMENTSDBMANIPULATOR_H

