#ifndef IDARTSTOURNAMENTSDBMANIPULATOR_H
#define IDARTSTOURNAMENTSDBMANIPULATOR_H

#include "iremovemodelsfromdb.h"
#include "idartstournamentdb.h"

class IRemoveTournamentsFromDb : public
        IRemoveModelsFromDb<IDartsTournamentDb>
{};
#endif // IDARTSTOURNAMENTSDBMANIPULATOR_H

