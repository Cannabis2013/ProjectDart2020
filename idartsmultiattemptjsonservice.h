#ifndef IDARTSMULTIATTEMPTJSONSERVICE_H
#define IDARTSMULTIATTEMPTJSONSERVICE_H

#include "iunaryservice.h"
#include <quuid.h>
#include <qbytearray.h>
#include <qvector.h>
#include <iplayerscoreservice.h>

namespace DartsScoreInputContext {
    struct DartsInputKeyValues
    {
        int score;
    };
    struct DartsInputExtendedValues
    {
        int score;
        QUuid playerId;
    };
    struct DartsInputPlayerDetails
    {
        QUuid playerId;
        QString playerName;
    };
    struct DartsSingleAttemptIndexes
    {
        int totalTurns;
        int turns;
        int roundIndex;
        int setIndex;
    };
}

class IDartsMultiAttemptJsonService
{
public:
    typedef DartsScoreInputContext::DartsInputKeyValues KeyInputValues;
    typedef DartsScoreInputContext::DartsInputExtendedValues ExtendedInputValues;
    typedef DartsScoreInputContext::DartsInputPlayerDetails PlayerDetailsStruct;
    typedef DartsScoreInputContext::DartsSingleAttemptIndexes DartsIndexes;
    virtual QByteArray assembleJsonDartsMultiAttemptScores(const IPlayerScoreService*) const = 0;
    virtual const KeyInputValues* assemblePointStructFromJson(const QByteArray&) const = 0;
    virtual const ExtendedInputValues * assembleExtendedInputModelFromJson(const QByteArray&) const = 0;
    virtual QVector<const ExtendedInputValues*> assembleExtendedInputModelsFromJson(const QByteArray&) const = 0;
    virtual QVector<const PlayerDetailsStruct*> assemblePlayerDetailsStructsFromJson(const QByteArray&) const = 0;
    virtual const PlayerDetailsStruct* assembleWinnerStructFromJson(const QByteArray&) const = 0;
    virtual QByteArray assembleJsonFromParameters(const QString&, const int&) const = 0;
    virtual const DartsIndexes* assembleDartsIndexesFromJson(const QByteArray&) const = 0;
    virtual QByteArray assembleJsonDartsScore(const QString&, const int&) const = 0;
    virtual QByteArray assembleJsonTurnValues(const bool&, const bool&, const int&, const QString&, const QString&) const = 0;
    virtual QByteArray assembleJsonAddScoreValues(const QUuid&,
                                                  const int&,
                                                  const int&,
                                                  const QUuid&,
                                                  const QUuid&,
                                                  const int&) const = 0;
    virtual QByteArray assembleJsonWinnerName(const QString&) const = 0;
};

#endif // IDARTSMULTIATTEMPTJSONSERVICE_H
