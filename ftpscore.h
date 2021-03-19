#ifndef POINT_H
#define POINT_H

#include <quuid.h>

#include "iscoremodel.h"

class FTPScore : public IScore<QUuid>
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
    int type() const override
    {
        return _modelType;
    }
    FTPScore* setType(const int &val) override
    {
        _modelType = val;
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
        return _throwIndex;
    }
    FTPScore* setAttempt(const int &index) override
    {
        _throwIndex = index;
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

    int keyCode() const override
    {
        return _keyCode;
    }
    FTPScore* setKeyCode(const int &key) override
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
    IScore* setTournament(const QUuid &tournament)
    {
        _tournament = tournament;
        return this;
    }

private:
    int _modelType;
    int _pointValue;
    int _scoreValue;
    int _throwIndex;
    int _setIndex;
    int _roundIndex;
    int _hint;
    int _keyCode;
    int _gameMode;
    QUuid _id, _player, _tournament;
};

#endif // POINT_H












