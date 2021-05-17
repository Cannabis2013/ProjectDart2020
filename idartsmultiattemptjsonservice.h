#ifndef IDARTSMULTIATTEMPTJSONSERVICE_H
#define IDARTSMULTIATTEMPTJSONSERVICE_H

#include "iunaryservice.h"
#include "dartsScoreModels.h"
#include <qbytearray.h>
#include <qvector.h>
#include <iplayerscoreservice.h>
class IDartsMultiAttemptJsonService {
public:
    typedef DartsScoresContext::DartsInputKeyValues KeyInputValues;
    typedef DartsScoresContext::DartsInputPlayerDetails PlayerDetailsStruct;
    typedef DartsScoresContext::DartsSingleAttemptIndexes DartsIndexes;
    virtual QByteArray assembleJsonDartsMultiAttemptScores(const IPlayerScoreService*) const = 0;
    virtual int getScoretByJson(const QByteArray&) const = 0;
    virtual const DartsScoresContext::DartsScore * assembleDartsScoreByJson(const QByteArray&) const = 0;
    virtual QVector<const DartsScoresContext::DartsScore*> assembleDartsScoresByJson(const QByteArray&) const = 0;
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
    virtual QByteArray assembleJsonWinnerName(const QUuid&, const QUuid&) const = 0;
};

#endif // IDARTSMULTIATTEMPTJSONSERVICE_H
