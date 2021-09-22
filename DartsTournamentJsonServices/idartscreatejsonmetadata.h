#ifndef IDARTSCREATEJSONMETADATA_H
#define IDARTSCREATEJSONMETADATA_H

#include "DTMCServices/igetdartstournamentfromdb.h"
#include "idartstournamentsdb.h"
#include "DartsTournamentJsonServices/iadddetailstotournamentjson.h"
#include "ModelsContext/imodelsdbcontext.h"
#include "dartstournamentjsonbuilder.h"

class IDartsCreateJsonMetaData
{
public:
    virtual QByteArray createJsonDartsMetaData(const IModel<QUuid> *tournamentModel,
                                               const IDartsTournamentJsonBuilder *jsonBuilder) const = 0;
};

#endif // IDARTSCREATEJSONMETADATA_H
