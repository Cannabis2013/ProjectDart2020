#ifndef MODELINTERFACE_H
#define MODELINTERFACE_H

#include "ijsonmodelsservice.h"

template<class TUuid, typename TjsonFormat>
class IModel : public IJsonModelsService<TjsonFormat>
{
public:
    virtual TUuid id() const = 0;
    virtual IModel* setId(const TUuid &val) = 0;
};

#endif // MODELINTERFACE_H
