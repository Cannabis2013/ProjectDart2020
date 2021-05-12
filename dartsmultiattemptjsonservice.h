#ifndef DARTSMULTIATTEMPTJSONSERVICE_H
#define DARTSMULTIATTEMPTJSONSERVICE_H

#include "idartsmultiattemptjsonservice.h"

#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

class DartsMultiAttemptJsonService :
        public IDartsMultiAttemptJsonService
{
public:

    // IDartsMultiAttemptJsonService interface
public:
    QByteArray assembleJsonDartsMultiAttemptScores(const IPlayerScoreService *scoreService) const override;
    const KeyInputValues *assemblePointStructFromJson(const QByteArray &json) const override;
    const ExtendedInputValues *assembleExtendedInputModelFromJson(const QByteArray &json) const override;
    QVector<const ExtendedInputValues *> assembleExtendedInputModelsFromJson(const QByteArray &json) const override;
    QVector<const PlayerDetailsStruct *> assemblePlayerDetailsStructsFromJson(const QByteArray &) const override;
    const PlayerDetailsStruct *assembleWinnerStructFromJson(const QByteArray &) const override;
    QByteArray assembleJsonFromParameters(const QString &playerName, const int &score) const override;
    const DartsIndexes *assembleDartsIndexesFromJson(const QByteArray &) const override;
    QByteArray assembleJsonDartsScore(const QString &playerName, const int &score) const override;
    QByteArray assembleJsonTurnValues(const bool &canUndo, const bool &canRedo, const int &roundIndex, const QString &currentPlayerName, const QString &targetRow) const override;
    QByteArray assembleJsonAddScoreValues(const QUuid &tournamentId, const int &roundIndex, const int &setIndex, const QUuid &winnerId, const QUuid &playerId, const int &score) const override;
    QByteArray assembleJsonWinnerName(const QString &winnerName) const override;
};

#endif // DARTSMULTIATTEMPTJSONSERVICE_H
