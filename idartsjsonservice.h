#ifndef IDARTSMODELSJSONSERVICE_H
#define IDARTSMODELSJSONSERVICE_H

#include <qbytearray.h>
#include <idartstournament.h>
#include <qvector.h>
#include "idartspointindexes.h"
#include <quuid.h>
#include "idartsmodelsservice.h"
#include "idartspointmodelsservice.h"
#include "idartsscoremodelsservice.h"
#include "iplayermodelsservice.h"
#include <qjsonarray.h>
#include "idartspointinput.h"
#include "idartspointdb.h"
#include "idartsscoredb.h"

namespace DartsModelsContext {
    class IDartsJsonService
    {
    public:
        // Tournament related
        virtual const IDartsTournament* assembleDartsTournamentFromJson(const QByteArray&) const = 0;
        virtual QVector<int> getDeleteTournamentIndexesFromJson(const QByteArray&) const = 0;
        virtual QByteArray addWinnerNameToDartsTournamentJson(const QByteArray&,const QString& name) const = 0;
        virtual QByteArray assembleJsonDartsTournamentModels(const IDartsModelsService*,
                                                             const IPlayerModelsService*) const = 0;
        virtual QUuid getTournamentIdByJson(const QByteArray&) const = 0;
        virtual QByteArray assembleJsonByDartsTournamentModel(const IDartsTournament*) const = 0;
        virtual QByteArray addPlayerNamesToDartsTournamentJson(const QByteArray&,
                                                            const QVector<QString>&) const = 0;
    };
}


#endif // IDARTSMODELSJSONSERVICE_H
