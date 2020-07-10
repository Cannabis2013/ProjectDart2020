#ifndef POINT_H
#define POINT_H

#include <quuid.h>

#include "gamemodelscontext.h"

class Point : public IPoint<QUuid>
{
    // IModel interface
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

    // IPoint interface
    int point() const override
    {
        return _pointValue;
    }
    void setPoint(const int &point) override
    {
        _pointValue = point;
    }
    QUuid set() const override
    {
        return _set;
    }
    void setSet(const QUuid &id) override
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
private:
    int _modelType, _pointValue, _legIndex;
    QUuid _id, _player, _set;

};

#endif // POINT_H
