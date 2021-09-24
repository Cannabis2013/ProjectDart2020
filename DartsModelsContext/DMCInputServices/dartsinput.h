#ifndef DARTSINPUT_H
#define DARTSINPUT_H
#include "DartsModelsContext/DMCInputSLAs/idartsinput.h"
namespace ModelsContext{
    class DartsInput : public IDartsInput
    {
    public:
        QUuid id() const override
        {
            return _id;
        }
        DartsInput* setId(const QUuid &val) override
        {
            _id = val;
            return this;
        }
        int point() const override
        {
            return _point;
        }
        DartsInput* setPoint(const int &point) override
        {
            _point = point;
            return this;
        }
        int score() const override
        {
            return _score;
        }
        DartsInput *setScore(const int& score) override
        {
            _score = score;
            return this;
        }

        QUuid tournamentId() const override
        {
            return _tournamentId;
        }
        DartsInput* setTournamentId(const QUuid &id) override
        {
            _tournamentId = id;
            return this;
        }
        QUuid playerId() const override
        {
            return _playerId;
        }
        DartsInput* setPlayerId(const QUuid &id) override
        {
            _playerId = id;
            return this;
        }
        QString playerName() const override
        {
            return _playerName;
        }
        DartsInput *setPlayerName(const QString &name) override
        {
            _playerName = name;
            return this;
        }
        int attempt() const override
        {
            return _attempt;
        }
        DartsInput* setAttempt(const int &index) override
        {
            _attempt = index;
            return this;
        }
        int hint() const override
        {
            return _hint;
        }
        DartsInput* setHint(const int &hint) override
        {
            _hint = hint;
            return this;
        }

        int modKeyCode() const override
        {
            return _modKeyCode;
        }
        DartsInput* setModKeyCode(const int &key) override
        {
            _modKeyCode = key;
            return this;
        }
        int setIndex() const override
        {
            return _setIndex;
        }
        DartsInput* setSetIndex(const int &index) override
        {
            _setIndex = index;
            return this;
        }
        int roundIndex() const override
        {
            return _roundIndex;
        }
        DartsInput* setRoundIndex(const int &index) override
        {
            _roundIndex = index;
            return this;
        }
        QUuid tournament() const
        {
            return _tournamentId;
        }
        DartsInput* setTournament(const QUuid &tournament)
        {
            _tournamentId = tournament;
            return this;
        }
    private:
        int _point, _score, _roundIndex, _setIndex, _attempt, _hint, _modKeyCode;
        QUuid _id, _playerId, _tournamentId;
        QString _playerName;
    };
};
#endif // POINT_H
