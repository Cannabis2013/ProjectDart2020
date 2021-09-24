#ifndef IADDDETAILSTOTOURNAMENTJSON_H
#define IADDDETAILSTOTOURNAMENTJSON_H

#include <qbytearray.h>
#include "DartsModelsContext/DMCTournamentSLAs/abstractdartstournament.h"
#include <qvector.h>
#include "DartsModelsContext/DMCIndexesSLAs/idartsindexes.h"
#include <quuid.h>
#include "DartsModelsContext/DMCInputSLAs/idartsinputsethint.h"
#include <qjsonarray.h>
#include "DartsModelsContext/DMCInputSLAs/idartsinput.h"
#include "ModelsContext/MCDbSLAs/imodelsdbcontext.h"

class IAddDetailsToTournamentJson
{
public:
    // Tournament related
    virtual QByteArray addWinnerName(const QByteArray&,const QString& name) const = 0;
    virtual QByteArray addPlayerNames(const QByteArray&,const QVector<QString>&) const = 0;
};


#endif // IDARTSMODELSJSONSERVICE_H
