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

class IDartsJsonService
{
public:
    virtual const IDartsTournament* assembleDartsTournamentFromJson(const QByteArray&) const = 0;
    virtual QVector<int> getPlayerIndexesFromJson(const QByteArray&) const = 0;
    virtual QByteArray assembleJsonDartsIndexes(const IDartsPointIndexes*) const = 0;
    virtual QByteArray assembleJsonFromPlayerNamesAndIds(const QVector<QUuid>&, const QVector<QString>&) const = 0;
    virtual QByteArray assembleJsonFromTournamentDartsPoints(const QUuid&,const IDartsModelsService*) const = 0;
    virtual QJsonArray jsonArrayFromDartsScores(const QUuid&, const IDartsModelsService*) const = 0;
    virtual QByteArray assembleJsonOrderedDartsPointModels(const QVector<const IDartsPointInput*>&,
                                                           const IPlayerModelsService*) const = 0;
    virtual QByteArray assembleJsonDartsTournamentModel(const IDartsTournament*,
                                                        const IPlayerModelsService*) const = 0;
    virtual QByteArray assembleJsonDartsTournamentModels(const IDartsModelsService*,
                                                         const IPlayerModelsService*) const = 0;
    virtual QByteArray assembleJsonFromDartsIndexesAndPoints(const IDartsModelsService*,
                                                             const IPlayerModelsService*) const = 0;
    virtual QByteArray assembleJsonFromPlayerIdAndName(const QUuid&,const QString&) const = 0;
    virtual QByteArray assembleJsonFromDartsTournamentModel(const IDartsTournament*) const = 0;
    virtual QVector<int> getDeleteTournamentIndexesFromJson(const QByteArray&) const = 0;
    virtual int getDeletePlayerIndexFromJson(const QByteArray&) const = 0;
    virtual const IDartsPointInput* assembleDartsPointModelFromJson(const QByteArray&) const = 0;
    virtual const IPlayerModel* assemblePlayerModelFromJson(const QByteArray&) const = 0;
    virtual const IDartsTournament* assignPlayerIdsToDartsTournament(const IDartsTournament*,
                                                                     const QVector<QUuid>&) const = 0;
    virtual QByteArray addPlayerNameToJsonPointModel(const QByteArray&,
                                                     const IPlayerModelsService*) const = 0;
    virtual QByteArray assembleJsonFromDartsPointModel(const IDartsPointInput*) const = 0;

};

#endif // IDARTSMODELSJSONSERVICE_H
