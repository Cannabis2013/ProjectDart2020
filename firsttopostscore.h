#ifndef POINT_H
#define POINT_H

#include <quuid.h>

#include "iscoremodel.h"

class FirstToPostScore : public IScore<QUuid>
{
public:
    QUuid id() const override
    {
        return _id;
    }
    FirstToPostScore* setId(const QUuid &val) override
    {
        _id = val;
        return this;
    }
    int type() const override
    {
        return _modelType;
    }
    FirstToPostScore* setType(const int &val) override
    {
        _modelType = val;
        return this;
    }
    int point() const override
    {
        return _pointValue;
    }
    FirstToPostScore* setPoint(const int &point) override
    {
        _pointValue = point;
        return this;
    }
    QUuid parent() const override
    {
        return _tournament;
    }
    FirstToPostScore* setParent(const QUuid &id) override
    {
        _tournament = id;
        return this;
    }
    QUuid player() const override
    {
        return _player;
    }
    FirstToPostScore* setPlayer(const QUuid &id) override
    {
        _player = id;
        return this;
    }
    int throwIndex() const override
    {
        return _throwIndex;
    }
    FirstToPostScore* setThrowIndex(const int &index) override
    {
        _throwIndex = index;
        return this;
    }
    int hint() const override
    {
        return _hint;
    }
    FirstToPostScore* setHint(const int &hint) override
    {
        _hint = hint;
        return this;
    }
    int score() const override
    {
        return _scoreValue;
    }
    FirstToPostScore* setScore(const int &score) override
    {
        _scoreValue = score;
        return this;
    }

    int keyCode() const override
    {
        return _keyCode;
    }
    FirstToPostScore* setKeyCode(const int &key) override
    {
        _keyCode = key;
        return this;
    }
    static FirstToPostScore* createInstance()
    {
        return new FirstToPostScore();
    }
    int setIndex() const override
    {
        return _setIndex;
    }
    FirstToPostScore* setSetIndex(const int &index) override
    {
        _setIndex = index;
        return this;
    }

    int roundIndex() const override
    {
        return _roundIndex;
    }
    FirstToPostScore* setRoundIndex(const int &index) override
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
    int _modelType,
        _pointValue,
        _scoreValue,
        _throwIndex,
        _setIndex,
        _roundIndex,
        _hint,
        _keyCode;
    QUuid _id, _player, _tournament;
};

#endif // POINT_H












