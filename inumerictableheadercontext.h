#ifndef INUMERICTABLEHEADERCONTEXT_H
#define INUMERICTABLEHEADERCONTEXT_H

#include "itableheadercontext.h"
template<typename T>
class INumericTableHeaderContext
{
public:
    virtual T headerDataAt(const int &index) const = 0;
    virtual void setAttemptsPerRound(const int &attempts) = 0;
    virtual int attemptsPerRound() const = 0;
    virtual void setInitialValue(const int &initialVal) = 0;
    virtual int initialValue() const = 0;
};


#endif // INUMERICTABLEHEADERCONTEXT_H
