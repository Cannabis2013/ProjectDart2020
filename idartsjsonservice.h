#ifndef IDARTSMODELSJSONSERVICE_H
#define IDARTSMODELSJSONSERVICE_H

#include <qbytearray.h>
#include <idartstournament.h>
#include <qvector.h>
#include "idartspointindexes.h"
#include <quuid.h>
#include "idartsmodelsservice.h"
#include "iplayermodelsservice.h"
#include <qjsonarray.h>
#include "idartspointinput.h"

using namespace DartsModelsContext;

class IDartsJsonService
{
public:
    virtual const IDartsTournament* assembleDartsTournamentFromJson(const QByteArray&) const = 0;
    virtual QVector<int> getPlayerIndexesFromJson(const QByteArray&) const = 0;
    virtual QByteArray assembleJsonDartsPointIndexes(const IDartsPointIndexes*) const = 0;
    virtual QByteArray assembleJsonDartsScoreIndexes(const IDartsScoreIndexes*) const = 0;
    virtual QByteArray assembleJsonFromPlayerNamesAndIds(const QVector<QUuid>&, const QVector<QString>&) const = 0;
    virtual QByteArray assembleJsonFromTournamentDartsPoints(const QUuid&,const IDartsModelsService*) const = 0;
    virtual QJsonArray jsonArrayFromDartsScores(const QUuid&, const IDartsModelsService*) const = 0;
    virtual QByteArray assembleJsonOrderedDartsPointModels(const QVector<const IDartsInput*>&,
                                                           const IPlayerModelsService*) const = 0;
    virtual QByteArray addPlayerNamesToDartsTournamentJson(const QByteArray&,
                                                        const QVector<QString>&) const = 0;
    virtual QByteArray addWinnerNameToDartsTournamentJson(const QByteArray&,const QString& name) const = 0;
    virtual QByteArray assembleJsonDartsTournamentModels(const IDartsModelsService*,
                                                         const IPlayerModelsService*) const = 0;
    virtual QByteArray assembleJsonByPlayerIdAndName(const QUuid&,const QString&) const = 0;
    virtual QByteArray assembleJsonFromDartsTournamentModel(const IDartsTournament*) const = 0;
    virtual QVector<int> getDeleteTournamentIndexesFromJson(const QByteArray&) const = 0;
    virtual int getDeletePlayerIndexFromJson(const QByteArray&) const = 0;
    virtual const IDartsInput* assembleDartsPointModelFromJson(const QByteArray&) const = 0;
    virtual const IPlayerModel* assemblePlayerModelFromJson(const QByteArray&) const = 0;
    virtual QByteArray assembleJsonFromDartsMultiAttemptScores(const QVector<const IDartsInput *>&) const = 0;
    virtual QUuid getWinnerIdByJson(const QByteArray&) const = 0;
    virtual QUuid getTournamentIdByJson(const QByteArray&) const = 0;
};

#endif // IDARTSMODELSJSONSERVICE_H
