#ifndef DCHINT_H
#define DCHINT_H

#include "DCMetaSLAs/idchint.h"

class DCHint : public IDCHint
{
public:
    static DCHint *createInstance(const int &hint)
    {
        return new DCHint(hint);
    }
    virtual int hint() const override
    {
        return _hint;
    }
private:
    DCHint(const int &hint):
        _hint(hint){}
    const int _hint;
};
#endif // DCHINT_H
