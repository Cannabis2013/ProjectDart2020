#ifndef POINT_H
#define POINT_H

#include <quuid.h>

#include "idartspointinput.h"

class DartsPointInput : public IDartsPointInput<QUuid>
{
public:
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
        return _pointValue;
    }
    DartsPointInput* setPointValue(const int &point) override
    {
        _pointValue = point;
        return this;
    }

    QUuid tournamentId() const override
    {
        return _tournament;
    }
    DartsPointInput* setTournamentId(const QUuid &id) override
    {
        _tournament = id;
        return this;
    }
    QUuid player() const override
    {
        return _player;
    }
    DartsPointInput* setPlayer(const QUuid &id) override
    {
        _player = id;
        return this;
    }
    int attempt() const override
    {
        return _attemptIndex;
    }
    DartsPointInput* setAttempt(const int &index) override
    {
        _attemptIndex = index;
        return this;
    }
    int hint() const override
    {
        return _hint;
    }
    DartsPointInput* setDisplayHint(const int &hint) override
    {
        _hint = hint;
        return this;
    }
    int score() const override
    {
        return _scoreValue;
    }
    DartsPointInput* setScoreValue(const int &score) override
    {
        _scoreValue = score;
        return this;
    }

    int modKeyCode() const override
    {
        return _keyCode;
    }
    DartsPointInput* setModKeyCode(const int &key) override
    {
        _keyCode = key;
        return this;
    }

    static DartsPointInput* createInstance()
    {
        return new DartsPointInput();
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
        return _tournament;
    }
    DartsPointInput* setTournament(const QUuid &tournament)
    {
        _tournament = tournament;
        return this;
    }

private:
    int _pointValue;
    int _scoreValue;
    int _roundIndex;
    int _setIndex;
    int _attemptIndex;
    int _hint;
    int _keyCode;
    QUuid _id, _player, _tournament;
};

#endif // POINT_H












