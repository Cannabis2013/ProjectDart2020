#ifndef IDARTSCREATEJSONMETADATA_H
#define IDARTSCREATEJSONMETADATA_H

#include "DartsModelsContext/igetdartstournamentfromdb.h"
#include "idartstournamentsdb.h"
#include "iadddetailstotournamentjson.h"
#include "ModelsContext/imodelsdbcontext.h"
#include "dartstournamentjsonbuilder.h"

class IDartsCreateJsonMetaData
{
public:
    virtual QByteArray createJsonDartsMetaData(const IModel<QUuid> *tournamentModel,
                                               const IDartsTournamentJsonBuilder *jsonBuilder) const = 0;
};

#endif // IDARTSCREATEJSONMETADATA_H
