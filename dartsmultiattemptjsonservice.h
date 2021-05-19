#ifndef DARTSMULTIATTEMPTJSONSERVICE_H
#define DARTSMULTIATTEMPTJSONSERVICE_H

#include "idartsmultiattemptjsonservice.h"

#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

using namespace DartsScoreMultiAttemptContext;

class DartsMultiAttemptJsonService :
        public IDartsMultiAttemptJsonService
{
public:
    QByteArray assembleJsonDartsMultiAttemptScores(const IPlayerScoreService *scoreService) const override;
    int getScoretByJson(const QByteArray &json) const override;
    QByteArray assembleJsonFromParameters(const QString &playerName, const int &score) const override;
    QByteArray assembleJsonDartsScore(const QString &playerName, const int &score) const override;
    QByteArray assembleJsonTurnValues(const bool &canUndo, const bool &canRedo, const int &roundIndex, const QString &currentPlayerName, const QString &targetRow) const override;
    QByteArray assembleJsonAddScoreValues(const QUuid &tournamentId, const int &roundIndex, const int &setIndex, const QUuid &winnerId, const QUuid &playerId, const int &score) const override;
    QByteArray assembleJsonWinnerName(const QUuid &tournamentId, const QUuid &winnerId) const override;
};

#endif // DARTSMULTIATTEMPTJSONSERVICE_H
