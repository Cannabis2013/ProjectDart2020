#ifndef IDARTSCREATEJSONMETADATA_H
#define IDARTSCREATEJSONMETADATA_H

#include "igetdartstournamentfromdb.h"
#include "idartstournamentsdb.h"
#include "iadddetailstotournamentjson.h"
#include "imodelsdbcontext.h"
#include "dartstournamentjsonbuilder.h"

class IDartsCreateJsonMetaData
{
public:
    virtual QByteArray createJsonDartsMetaData(const IModel<QUuid> *tournamentModel,
                                               const IDartsTournamentJsonBuilder *jsonBuilder) const = 0;
};

#endif // IDARTSCREATEJSONMETADATA_H
