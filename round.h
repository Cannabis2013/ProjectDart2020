#ifndef ROUND_H
#define ROUND_H

#include <quuid.h>

#include "gamemodelscontext.h"


class Round : public IRound<QUuid,QList<QUuid>>
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
    // IRound interface
    int index() const override
    {
        return _index;
    }
    void setIndex(const int &val) override
    {
        _index = val;
    }
    QUuid tournament() const override
    {
        return _tournament;
    }
    void setTournament(const QUuid &id) override
    {
        _tournament = id;
    }
private:
    int _modelType, _index;
    QUuid _id, _tournament;
};

#endif // ROUND_H
