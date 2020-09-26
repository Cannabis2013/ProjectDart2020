#ifndef ISETMODEL_H
#define ISETMODEL_H

#include "iroundmodel.h"

template<class TUuid, class TList>
class ISet : public IModel<TUuid>
{
public:
    virtual int index() const = 0;
    virtual ISet* setIndex(const int &index) = 0;
    virtual ISet *setId(const TUuid &val) override = 0;
    virtual ISet *setType(const int &val) override = 0;
    virtual ISet *setParent(const TUuid &parent) override = 0;
};

#endif // ISETMODEL_H
