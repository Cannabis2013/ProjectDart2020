#ifndef SET_H
#define SET_H

#include <quuid.h>

#include "gamemodelscontext.h"
#include <qlist.h>

class Set : public ISet<QUuid,QList<QUuid>>
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
    // ISet interface
    QUuid parent() const override
    {
        return _round;
    }
    void setParent(const QUuid &id) override
    {
        _round = id;
    }

    int index() const override
    {
        return _index;
    }
    void setIndex(const int &index) override
    {
        _index = index;
    }

private:
    int _modelType, _index;
    QUuid _id, _round;

};

#endif // SET_H
