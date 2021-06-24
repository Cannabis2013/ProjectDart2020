#ifndef MODELINTERFACE_H
#define MODELINTERFACE_H

#include "ijson.h"

template<class TUuid, typename TjsonFormat>
class IModel : public IJson<TjsonFormat>
{
public:
    virtual TUuid id() const = 0;
    virtual IModel* setId(const TUuid &val) = 0;
};

#endif // MODELINTERFACE_H
