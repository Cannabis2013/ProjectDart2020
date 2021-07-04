#ifndef IDARTSJSONMANIPULATOR_H
#define IDARTSJSONMANIPULATOR_H

#include <qbytearray.h>
#include <idartstournament.h>
#include <qvector.h>
#include "idartspointindexes.h"
#include <quuid.h>
#include "idartstournamentsdbmanipulator.h"
#include "idartspointmodelsservice.h"
#include "idartsscoremodelsservice.h"
#include "iplayermodelsservice.h"
#include <qjsonarray.h>
#include "idartspointinput.h"
#include "idartsinputdb.h"
#include "idartstournamentdb.h"

class IDartsJsonManipulator
{
public:
    // Tournament related
    virtual QByteArray addWinnerNameToDartsTournamentJson(const QByteArray&,
                                                          const QString& name) const = 0;
    virtual QByteArray addPlayerNamesToDartsTournamentJson(const QByteArray&,
                                                           const QVector<QString>&) const = 0;
};


#endif // IDARTSMODELSJSONSERVICE_H
