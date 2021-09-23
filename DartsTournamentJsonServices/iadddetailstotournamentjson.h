#ifndef IADDDETAILSTOTOURNAMENTJSON_H
#define IADDDETAILSTOTOURNAMENTJSON_H

#include <qbytearray.h>
#include <abstractdartstournament.h>
#include <qvector.h>
#include "idartspointindexes.h"
#include <quuid.h>
#include "DCInputSLAs/idartsinputsethint.h"
#include "isetmodelhint.h"
#include <qjsonarray.h>
#include "idartsinput.h"
#include "ModelsContext/imodelsdbcontext.h"
#include "idartstournamentsdb.h"

class IAddDetailsToTournamentJson
{
public:
    // Tournament related
    virtual QByteArray addWinnerName(const QByteArray&,const QString& name) const = 0;
    virtual QByteArray addPlayerNames(const QByteArray&,const QVector<QString>&) const = 0;
};


#endif // IDARTSMODELSJSONSERVICE_H
