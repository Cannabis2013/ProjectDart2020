#ifndef IDARTSPOINTJSONASSEMBLERSERVICE_H
#define IDARTSPOINTJSONASSEMBLERSERVICE_H

#include "iunaryservice.h"
#include <quuid.h>
#include <qbytearray.h>
#include <qvector.h>
#include <iscorecontroller.h>

namespace DartsInputContext {
    struct DartsInputKeyValues
    {
        int pointValue;
        int modKeyCode;
    };
    struct DartsInputExtendedValues
    {
        int pointValue;
        int modKeyCode;
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
        int attemptIndex;
    };
}

class IDartsSingleAttemptPointJsonService
{
public:
    typedef DartsInputContext::DartsInputKeyValues KeyInputValues;
    typedef DartsInputContext::DartsInputExtendedValues ExtendedInputValues;
    typedef DartsInputContext::DartsInputPlayerDetails PlayerDetailsStruct;
    typedef DartsInputContext::DartsSingleAttemptIndexes DartsIndexes;
    virtual const KeyInputValues* assemblePointStructFromJson(const QByteArray&) const = 0;
    virtual const ExtendedInputValues * assembleExtendedInputModelFromJson(const QByteArray&) const = 0;
    virtual QVector<const ExtendedInputValues*> assembleExtendedInputModelsFromJson(const QByteArray&) const = 0;
    virtual QVector<const PlayerDetailsStruct*> assemblePlayerDetailsStructsFromJson(const QByteArray&) const = 0;
    virtual const PlayerDetailsStruct* assembleWinnerStructFromJson(const QByteArray&) const = 0;
    virtual QByteArray assembleJsonFromParameters(const QString&, const int&,const int&) const = 0;
    virtual QByteArray assembleJsonFromParameters(const QString&, const int&,const int&, const int&) const = 0;
    virtual const DartsIndexes* assembleDartsIndexesFromJson(const QByteArray&) const = 0;
    virtual QByteArray assembleJsonDartsPoints(const IScoreController*) const = 0;
    virtual QByteArray assembleJsonDartsPoint(const QString&, const int&, const int&) const = 0;
    virtual QByteArray assembleJsonTurnValues(const bool&, const bool&, const int&, const QString&, const QString&) const = 0;
    virtual QByteArray assembleJsonAddPointValues(const QUuid&,
                                                  const int&,
                                                  const int&,
                                                  const int&,
                                                  const QUuid&,
                                                  const QUuid&,
                                                  const int&,
                                                  const int&) const = 0;
    virtual QByteArray assembleJsonWinnerName(const QString&) const = 0;
};

#endif // IDARTSPOINTJSONASSEMBLERSERVICE_H
