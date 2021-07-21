#ifndef IDARTSCREATEJSONMETADATA_H
#define IDARTSCREATEJSONMETADATA_H

#include "igetdartstournamentfromdb.h"
#include "igetdartsplayermodelsfromdb.h"
#include "idartstournamentsdb.h"
#include "iadddetailstotournamentjson.h"
#include "idbservice.h"
#include "dartstournamentjsonbuilder.h"

class IDartsCreateJsonMetaData
{
public:
    virtual QByteArray createJsonDartsMetaData(const IModel<QUuid> *tournamentModel,
                                               const IGetDartsPlayerModelsFromDb *getPlayerData,
                                               const IAddDetailsToTournamentJson *jsonManipulator,
                                               const IDartsTournamentJsonBuilder *jsonBuilder,
                                               const IDbService *playersDb) const = 0;
};

#endif // IDARTSCREATEJSONMETADATA_H
