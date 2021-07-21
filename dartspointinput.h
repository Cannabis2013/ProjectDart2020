#ifndef POINT_H
#define POINT_H
#include "idartspointinput.h"
namespace ModelsContext{
    class DartsPointInput : public IDartsPointInput
    {
    public:
        static DartsPointInput* createInstance()
        {
            return new DartsPointInput();
        }
        QUuid id() const override
        {
            return _id;
        }
        DartsPointInput* setId(const QUuid &val) override
        {
            _id = val;
            return this;
        }
        int point() const override
        {
            return _point;
        }
        DartsPointInput* setPoint(const int &point) override
        {
            _point = point;
            return this;
        }
        int score() const override
        {
            return _score;
        }
        DartsPointInput *setScore(const int& score) override
        {
            _score = score;
            return this;
        }

        QUuid tournamentId() const override
        {
            return _tournamentId;
        }
        DartsPointInput* setTournamentId(const QUuid &id) override
        {
            _tournamentId = id;
            return this;
        }
        QUuid playerId() const override
        {
            return _playerId;
        }
        DartsPointInput* setPlayerId(const QUuid &id) override
        {
            _playerId = id;
            return this;
        }
        QString playerName() const override
        {
            return _playerName;
        }
        DartsPointInput *setPlayerName(const QString &name) override
        {
            _playerName = name;
            return this;
        }
        int attempt() const override
        {
            return _attempt;
        }
        DartsPointInput* setAttempt(const int &index) override
        {
            _attempt = index;
            return this;
        }
        int hint() const override
        {
            return _hint;
        }
        DartsPointInput* setHint(const int &hint) override
        {
            _hint = hint;
            return this;
        }

        int modKeyCode() const override
        {
            return _modKeyCode;
        }
        DartsPointInput* setModKeyCode(const int &key) override
        {
            _modKeyCode = key;
            return this;
        }
        int setIndex() const override
        {
            return _setIndex;
        }
        DartsPointInput* setSetIndex(const int &index) override
        {
            _setIndex = index;
            return this;
        }
        int roundIndex() const override
        {
            return _roundIndex;
        }
        DartsPointInput* setRoundIndex(const int &index) override
        {
            _roundIndex = index;
            return this;
        }
        QUuid tournament() const
        {
            return _tournamentId;
        }
        DartsPointInput* setTournament(const QUuid &tournament)
        {
            _tournamentId = tournament;
            return this;
        }
    private:
        DartsPointInput()
        {}
        int _point;
        int _score;
        int _roundIndex;
        int _setIndex;
        int _attempt;
        int _hint;
        int _modKeyCode;
        QUuid _id;
        QUuid _playerId;
        QString _playerName;
        QUuid _tournamentId;
    };
};
#endif // POINT_H
