#ifndef POINT_H
#define POINT_H

#include <quuid.h>

#include "iscoremodel.h"

class FTPScore : public IFtpScore<QUuid>
{
public:
    QUuid id() const override
    {
        return _id;
    }
    FTPScore* setId(const QUuid &val) override
    {
        _id = val;
        return this;
    }
    int point() const override
    {
        return _pointValue;
    }
    FTPScore* setPointValue(const int &point) override
    {
        _pointValue = point;
        return this;
    }

    virtual int accumulatedScore() const override
    {
        return _accumulatedScore;
    }
    virtual FTPScore *setAccumulatedScore(const int& score) override
    {
        _accumulatedScore = score;
        return this;
    }
    QUuid parent() const override
    {
        return _tournament;
    }
    FTPScore* setParent(const QUuid &id) override
    {
        _tournament = id;
        return this;
    }
    QUuid player() const override
    {
        return _player;
    }
    FTPScore* setPlayer(const QUuid &id) override
    {
        _player = id;
        return this;
    }
    int attempt() const override
    {
        return _attemptIndex;
    }
    FTPScore* setAttempt(const int &index) override
    {
        _attemptIndex = index;
        return this;
    }
    int hint() const override
    {
        return _hint;
    }
    FTPScore* setDisplayHint(const int &hint) override
    {
        _hint = hint;
        return this;
    }
    int score() const override
    {
        return _scoreValue;
    }
    FTPScore* setScoreValue(const int &score) override
    {
        _scoreValue = score;
        return this;
    }

    int modKeyCode() const override
    {
        return _keyCode;
    }
    FTPScore* setModKeyCode(const int &key) override
    {
        _keyCode = key;
        return this;
    }

    static FTPScore* createInstance()
    {
        return new FTPScore();
    }
    int setIndex() const override
    {
        return _setIndex;
    }
    FTPScore* setSetIndex(const int &index) override
    {
        _setIndex = index;
        return this;
    }

    int roundIndex() const override
    {
        return _roundIndex;
    }
    FTPScore* setRoundIndex(const int &index) override
    {
        _roundIndex = index;
        return this;
    }

    QUuid tournament() const
    {
        return _tournament;
    }
    FTPScore* setTournament(const QUuid &tournament)
    {
        _tournament = tournament;
        return this;
    }

private:
    int _pointValue;
    int _scoreValue;
    int _accumulatedScore;
    int _roundIndex;
    int _setIndex;
    int _attemptIndex;
    int _hint;
    int _keyCode;
    QUuid _id, _player, _tournament;
};

#endif // POINT_H












