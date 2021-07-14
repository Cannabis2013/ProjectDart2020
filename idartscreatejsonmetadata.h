#ifndef IDARTSCREATEJSONMETADATA_H
#define IDARTSCREATEJSONMETADATA_H

#include "igetdartstournamentfromdb.h"
#include "igetdartsplayermodelsfromdb.h"
#include "idartstournamentdb.h"
#include "iadddetailstotournamentjson.h"
#include "iplayermodelsdb.h"
#include "dartstournamentjsonbuilder.h"

class IDartsCreateJsonMetaData
{
public:
    virtual QByteArray createJsonDartsMetaData(const ITournament *tournamentModel,
                                               const IGetDartsPlayerModelsFromDb *getPlayerData,
                                               const IAddDetailsToTournamentJson *jsonManipulator,
                                               const IDartsTournamentJsonBuilder *jsonBuilder,
                                               const IPlayerModelsDb *playersDb) const = 0;
};

#endif // IDARTSCREATEJSONMETADATA_H
