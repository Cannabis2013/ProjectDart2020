#ifndef DARTSSCOREINPUT_H
#define DARTSSCOREINPUT_H

#include "idartsscoreinput.h"

namespace DartsModelsContext {
    class DartsScoreInput : public IDartsScoreInput
    {
    public:
        static DartsScoreInput* createInstance()
        {
            return new DartsScoreInput();
        }
        QUuid id() const override
        {
            return _id;
        }
        DartsScoreInput *setId(const QUuid &val) override
        {
            _id = val;
            return this;
        }
        int hint() const override
        {
            return _hint;
        }
        DartsScoreInput *setHint(const int &hint) override
        {
            _hint = hint;
            return this;
        }
        QUuid playerId() const override
        {
            return _playerId;
        }
        DartsScoreInput *setPlayerId(const QUuid &id) override
        {
            _playerId = id;
            return this;
        }
        QString playerName() const override
        {
            return _playerName;
        }
        DartsScoreInput *setPlayerName(const QString &name) override
        {
            _playerName = name;
            return this;
        }
        QUuid tournamentId() const override
        {
            return _tournamentId;
        }
        DartsScoreInput *setTournamentId(const QUuid &tournamentId) override
        {
            _tournamentId = tournamentId;
            return this;
        }
        int roundIndex() const override
        {
           return _roundIndex;
        }
        DartsScoreInput *setRoundIndex(const int &index) override
        {
            _roundIndex = index;
            return this;
        }
        int setIndex() const override
        {
            return _setIndex;
        }
        DartsScoreInput *setSetIndex(const int &index) override
        {
            _setIndex = index;
            return this;
        }
        int score() const override
        {
            return _score;
        }
        DartsScoreInput *setScore(const int &score) override
        {
            _score = score;
            return this;
        }
    private:
        DartsScoreInput(){}
        int _score;
        int _roundIndex;
        int _setIndex;
        int _hint;
        QUuid _id;
        QUuid _playerId;
        QString _playerName;
        QUuid _tournamentId;
    };
}


#endif // DARTSSCOREINPUT_H
