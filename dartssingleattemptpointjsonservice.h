#ifndef DARTSSINGLEATTEMPTPOINTJSONSERVICE_H
#define DARTSSINGLEATTEMPTPOINTJSONSERVICE_H

#include "IDartsSingleAttemptPointJsonService.h"
#include <QJsonDocument>
#include <qjsonobject.h>
#include <qjsonarray.h>

class DartsSingleAttemptPointJsonService :
        public IDartsSingleAttemptPointJsonService
{
public:
    const KeyInputValues *assemblePointStructFromJson(const QByteArray &json) const override;
    const ExtendedInputValues * assembleExtendedInputModelFromJson(const QByteArray& json) const override;
    QVector<const ExtendedInputValues *> assembleExtendedInputModelsFromJson(const QByteArray& json) const override;
    QVector<const PlayerDetailsStruct *> assemblePlayerDetailsStructsFromJson(const QByteArray& json) const override;
    const PlayerDetailsStruct *assembleWinnerStructFromJson(const QByteArray& json) const override;
    QByteArray assembleJsonFromParameters(const QString&playerName, const int &pointValue, const int &scoreValue) const override;
    QByteArray assembleJsonFromParameters(const QString& playerName, const int& pointValue, const int& scoreValue, const int& modKeyCode) const override;
    const DartsIndexes *assembleDartsIndexesFromJson(const QByteArray &json) const override;
    QByteArray assembleJsonDartsPoints(const IScoreController *controller) const override;
    QByteArray assembleJsonDartsPoint(const QString &playerName, const int& point, const int &score) const override;
    QByteArray assembleJsonTurnValues(const bool &canUndo, const bool &canRedo, const int &roundIndex, const QString& currentPlayerName, const QString& targetRow) const override;
    QByteArray assembleJsonAddPointValues(const QUuid& tournamentId, const int& roundIndex, const int &setIndex,
                                          const int &attemptIndex, const QUuid &winnerId, const QUuid &playerId,
                                          const int &point, const int &modKeyCode) const override;
    QByteArray assembleJsonWinnerName(const QString &winnerId) const override;
};



#endif // DARTSSINGLEATTEMPTPOINTJSONSERVICE_H
