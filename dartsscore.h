#ifndef DARTSSCORE_H
#define DARTSSCORE_H

#include "idartsscore.h"

namespace DartsScoreMultiAttemptContext
{
    class DartsScore : public IDartsScore
    {
    public:
        int score() const override
        {
            return _score;
        }
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
        void setScore(int newScore)
        {
            _score = newScore;
        }

    private:
        int _score;
        QUuid _playerId;
        QString _playerName;
    };
};

#endif // DARTSSCORE_H
