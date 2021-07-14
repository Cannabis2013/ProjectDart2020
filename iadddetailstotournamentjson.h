#ifndef IADDDETAILSTOTOURNAMENTJSON_H
#define IADDDETAILSTOTOURNAMENTJSON_H

#include <qbytearray.h>
#include <idartstournament.h>
#include <qvector.h>
#include "idartspointindexes.h"
#include <quuid.h>
#include "iremovetournamentsfromdb.h"
#include "idartspointsethint.h"
#include "idartsscoresethint.h"
#include "iplayermodelsservice.h"
#include <qjsonarray.h>
#include "idartspointinput.h"
#include "idartsinputdb.h"
#include "idartstournamentdb.h"

class IAddDetailsToTournamentJson
{
public:
    // Tournament related
    virtual QByteArray addWinnerName(const QByteArray&,
                                                          const QString& name) const = 0;
    virtual QByteArray addPlayerNames(const QByteArray&,
                                                           const QVector<QString>&) const = 0;
};


#endif // IDARTSMODELSJSONSERVICE_H
