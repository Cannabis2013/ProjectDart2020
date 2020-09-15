#ifndef ISETMODEL_H
#define ISETMODEL_H

#include "iroundmodel.h"

template<class TUuid, class TList>
class ISet : public IModel<TUuid>
{
public:
    virtual int index() const = 0;
    virtual void setIndex(const int &index) = 0;
};

#endif // ISETMODEL_H
