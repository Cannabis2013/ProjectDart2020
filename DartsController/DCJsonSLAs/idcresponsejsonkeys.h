#ifndef IDCRESPONSEJSONKEYS_H
#define IDCRESPONSEJSONKEYS_H

#include <qstring.h>

class IDCResponseJsonKeys
{
public:
    virtual QString inputKey() const = 0;
    virtual QString indexesKey() const = 0;
    virtual QString turnValuesKey() const = 0;
    virtual QString winnerValuesKey() const = 0;
};
#endif // IDCRESPONSEJSONKEYS_H
