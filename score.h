#ifndef POINT_H
#define POINT_H

#include <quuid.h>

#include "iscoremodel.h"

class Score : public IScore<QUuid>
{
public:
    QUuid id() const override
    {
        return _id;
    }
    Score* setId(const QUuid &val) override
    {
        _id = val;
        return this;
    }
    int type() const override
    {
        return _modelType;
    }
    Score* setType(const int &val) override
    {
        _modelType = val;
        return this;
    }
    int point() const override
    {
        return _pointValue;
    }
    Score* setPoint(const int &point) override
    {
        _pointValue = point;
        return this;
    }
    QUuid parent() const override
    {
        return _set;
    }
    Score* setParent(const QUuid &id) override
    {
        _set = id;
        return this;
    }
    QUuid player() const override
    {
        return _player;
    }
    Score* setPlayer(const QUuid &id) override
    {
        _player = id;
        return this;
    }
    int throwIndex() const override
    {
        return _throwIndex;
    }
    Score* setThrowIndex(const int &index) override
    {
        _throwIndex = index;
        return this;
    }
    int hint() const override
    {
        return _hint;
    }
    Score* setHint(const int &hint) override
    {
        _hint = hint;
        return this;
    }
    int score() const override
    {
        return _scoreValue;
    }
    Score* setScore(const int &score) override
    {
        _scoreValue = score;
        return this;
    }

    int keyCode() const override
    {
        return _keyCode;
    }
    Score* setKeyCode(const int &key) override
    {
        _keyCode = key;
        return this;
    }
    static Score* createInstance()
    {
        return new Score();
    }
    int setIndex() const
    {
        return _setIndex;
    }
    void setSetIndex(int setIndex)
    {
        _setIndex = setIndex;
    }

    int roundIndex() const
    {
        return _roundIndex;
    }
    void setRoundIndex(int roundIndex)
    {
        _roundIndex = roundIndex;
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
    QUuid _id, _player, _set;    
};

#endif // POINT_H








