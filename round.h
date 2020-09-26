#ifndef ROUND_H
#define ROUND_H

#include <quuid.h>

#include "iroundmodel.h"


class Round : public IRound<QUuid,QList<QUuid>>
{

    // IModel interface
public:
    QUuid id() const override
    {
        return _id;
    }
    Round* setId(const QUuid &val) override
    {
        _id = val;
        return this;
    }
    int type() const override
    {
        return _modelType;
    }
    Round* setType(const int &val) override
    {
        _modelType = val;
        return this;
    }
    // IRound interface
    int index() const override
    {
        return _index;
    }
    IRound* setIndex(const int &val) override
    {
        _index = val;
        return this;
    }
    QUuid parent() const override
    {
        return _tournament;
    }
    IRound* setParent(const QUuid &id) override
    {
        _tournament = id;
        return this;
    }

    static IRound<QUuid,QList<QUuid>> *createInstance()
    {
        return new Round();
    }
private:
    int _modelType, _index;
    QUuid _id, _tournament;
};

#endif // ROUND_H
