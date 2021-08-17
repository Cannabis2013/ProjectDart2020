#ifndef DARTSTABLECELLCONTEXT_H
#define DARTSTABLECELLCONTEXT_H

#include "itablecellcontext.h"
#include <QDebug>
class DartsTableCellContext : public ITableCellContext<QPair<int,int>>
{
public:
    int initialValue() const override
    {
        return _initialValue;
    }
    void setInitialValue(const int &value) override
    {
        _initialValue = value;
    }
    Item defaultValues() const override
    {
        return Item(-1,-1);
    }
private:
    int _initialValue;
};
#endif // DARTSTABLECELLCONTEXT_H
