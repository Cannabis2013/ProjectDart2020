#ifndef ISCORE_H
#define ISCORE_H

#include "imodel.h"

template<typename TUuid>
class IScore : public IModel<TUuid>
{
public:
    IScore() {}

    virtual int modKeyCode() const = 0;
    virtual IScore* setModKeyCode(const int &key) = 0;
    virtual int hint() const = 0;
    virtual IScore* setDisplayHint(const int &hint) = 0;
    virtual TUuid player() const = 0;
    virtual IScore* setPlayer(const TUuid &id) = 0;
};

#endif // ISCORE_H
