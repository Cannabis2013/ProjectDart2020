#ifndef DARTSHORIZONTALHEADERCONTEXT_H
#define DARTSHORIZONTALHEADERCONTEXT_H

#include "inumerictableheadercontext.h"
#include <qvariant.h>

class DartsHorizontalHeaderContext : public INumericTableHeaderContext<QVariant>
{
public:
    virtual QVariant headerDataAt(const int &index) const override
    {
        auto roundIndex = (index - 1)/_attempsPerRound + 1;
        return index != 0 ? QVariant(roundIndex) : _initialValue;
    }
    virtual void setAttemptsPerRound(const int &attempts) override
    {
        _attempsPerRound = attempts;
    }
    virtual void setInitialValue(const int &initialVal) override
    {
        _initialValue = initialVal;
    }
    virtual int attemptsPerRound() const override
    {
        return _attempsPerRound;
    }
    virtual int initialValue() const override
    {
        return _initialValue;
    }
private:
    int _attempsPerRound = 3;
    int _initialValue = 0;
};

#endif // DARTSHORIZONTALHEADERCONTEXT_H
