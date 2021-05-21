#ifndef DARTSMULTIATTEMPTJSONSERVICE_H
#define DARTSMULTIATTEMPTJSONSERVICE_H

#include "idartsmultiattemptjsonservice.h"

#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "dartsscore.h"
#include "iplayerscoreservice.h"

namespace DartsScoreMultiAttemptContext
{
    class DartsMultiAttemptJsonService :
            public IDartsMultiAttemptJsonService<IPlayerScoreService<DartsScore>>
    {
    public:
        typedef IPlayerScoreService<DartsScore> PlayerScoreService;
        QByteArray assembleJsonDartsMultiAttemptScores(const PlayerScoreService *scoreService) const override;
        int getScoreByJson(const QByteArray &json) const override;
        QByteArray assembleJsonTurnValues(const bool &canUndo, const bool &canRedo, const int &roundIndex, const QString &currentPlayerName, const QString &targetRow) const override;
        QByteArray assembleJsonAddScoreValues(const QUuid &tournamentId, const int &roundIndex, const int &setIndex, const QUuid &winnerId, const QUuid &playerId, const int &score) const override;
        QByteArray assembleJsonWinnerName(const QUuid &tournamentId, const QUuid &winnerId) const override;
    };
}


#endif // DARTSMULTIATTEMPTJSONSERVICE_H
