#ifndef IDARTSCREATEJSONMETADATA_H
#define IDARTSCREATEJSONMETADATA_H

#include "DartsModelsContext/DMCTournamentSLAs/igetdartstournamentfromdb.h"
#include "DartsModelsContext/DMCTournamentSLAs/iadddetailstotournamentjson.h"
#include "ModelsContext/MCDbSLAs/imodelsdbcontext.h"
#include "DartsModelsContext/DMCTournamentServices/dartstournamentjsonbuilder.h"

class IDartsCreateJsonMetaData
{
public:
    virtual QByteArray createJsonDartsMetaData(const IModel<QUuid> *tournamentModel,
                                               const IDartsTournamentJsonBuilder *jsonBuilder) const = 0;
};

#endif // IDARTSCREATEJSONMETADATA_H
