#ifndef ISCORE_H
#define ISCORE_H

#include "imodel.h"

template<typename TUuid>
class IPlayerInput : public IModel<TUuid>
{
public:
    IPlayerInput() {}

    virtual int modKeyCode() const = 0;
    virtual IPlayerInput* setModKeyCode(const int &key) = 0;
    virtual int hint() const = 0;
    virtual IPlayerInput* setDisplayHint(const int &hint) = 0;
    virtual TUuid player() const = 0;
    virtual IPlayerInput* setPlayer(const TUuid &id) = 0;
};

#endif // ISCORE_H
