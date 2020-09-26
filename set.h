#ifndef SET_H
#define SET_H

#include <quuid.h>
#include <qlist.h>

#include "isetmodel.h"

class Set : public ISet<QUuid,QList<QUuid>>
{
    // IModel interface
public:
    QUuid id() const override
    {
        return _id;
    }
    ISet* setId(const QUuid &val) override
    {
        _id = val;
        return this;
    }
    int type() const override
    {
        return _modelType;
    }
    ISet* setType(const int &val) override
    {
        _modelType = val;
        return this;
    }
    // ISet interface
    QUuid parent() const override
    {
        return _round;
    }
    ISet* setParent(const QUuid &id) override
    {
        _round = id;
        return this;
    }

    int index() const override
    {
        return _index;
    }
    ISet<QUuid,QList<QUuid>>* setIndex(const int &index) override
    {
        _index = index;
        return this;
    }
    static ISet* createInstance()
    {
        return new Set();
    }

private:
    int _modelType, _index;
    QUuid _id, _round;

};

#endif // SET_H
