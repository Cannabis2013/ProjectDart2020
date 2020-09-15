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
    void setId(const QUuid &val) override
    {
        _id = val;
    }
    int type() const override
    {
        return _modelType;
    }
    void setType(const int &val) override
    {
        _modelType = val;
    }
    int point() const override
    {
        return _pointValue;
    }
    void setPoint(const int &point) override
    {
        _pointValue = point;
    }
    QUuid parent() const override
    {
        return _set;
    }
    void setParent(const QUuid &id) override
    {
        _set = id;
    }
    QUuid player() const override
    {
        return _player;
    }
    void setPlayer(const QUuid &id) override
    {
        _player = id;
    }
    int throwIndex() const override
    {
        return _throwIndex;
    }
    void setLegIndex(const int &index) override
    {
        _throwIndex = index;
    }
    int hint() const override
    {
        return _hint;
    }
    void setHint(const int &hint) override
    {
        _hint = hint;
    }
    int score() const override
    {
        return _scoreValue;
    }
    void setScore(const int &score) override
    {
        _scoreValue = score;
    }

private:
    int _modelType, _pointValue, _scoreValue,_throwIndex, _hint;
    QUuid _id, _player, _set;
};

#endif // POINT_H
