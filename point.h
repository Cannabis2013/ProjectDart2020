#ifndef POINT_H
#define POINT_H

#include <quuid.h>

#include "gamemodelscontext.h"

class Point : public IPoint<QUuid>
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
    int legIndex() const override
    {
        return _legIndex;
    }
    void setLegIndex(const int &index) override
    {
        _legIndex = index;
    }
    int hint() const override
    {
        return _hint;
    }
    void setHint(const int &hint) override
    {
        _hint = hint;
    }
private:
    int _modelType, _pointValue, _legIndex, _hint;
    QUuid _id, _player, _set;
};





#endif // POINT_H
