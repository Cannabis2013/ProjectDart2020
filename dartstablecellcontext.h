#ifndef DARTSTABLECELLCONTEXT_H
#define DARTSTABLECELLCONTEXT_H

#include "itablecellcontext.h"
#include <qpair.h>
class DartsTableCellContext : public ITableCellContext<QPair<int,int>>
{
public:
    virtual int initialValue() const override
    {
        return _initialValue;
    }
    virtual void setInitialValue(const int &value) override
    {
        _initialValue = value;
    }
    virtual QPair<int,int> defaultValues() const override
    {
        return QPair<int,int>(-1,-1);
    }
private:
    int _initialValue = 0;
};


#endif // DARTSTABLECELLCONTEXT_H
