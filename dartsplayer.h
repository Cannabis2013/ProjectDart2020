#ifndef DARTSPLAYER_H
#define DARTSPLAYER_H

#include "idartsplayer.h"

namespace DartsScoreMultiAttemptContext
{
    class DartsPlayer : public IDartsPlayer
    {
    public:
        QUuid playerId() const override
        {
            return _playerId;
        }
        QString playerName() const override
        {
            return _playerName;
        }
        void setPlayerId(const QUuid &newPlayerId)
        {
            _playerId = newPlayerId;
        }
        void setPlayerName(const QString &newPlayerName)
        {
            _playerName = newPlayerName;
        }
    private:
        QUuid _playerId;
        QString _playerName;
    };
}

#endif // DARTSPLAYER_H
