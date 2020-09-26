#ifndef IROUNDMODEL_H
#define IROUNDMODEL_H

#include "itournamentmodel.h"

template<class TUuid, class TList>
class IRound : public IModel<TUuid>
{
public:
    virtual int index() const = 0;
    virtual IRound* setIndex(const int &val) = 0;

    // IModel interface
public:
    virtual IRound* setId(const TUuid &val) override = 0;
    virtual IRound* setType(const int &val) override = 0;
    virtual IRound* setParent(const TUuid &parent) override = 0;
};

#endif // IROUNDMODEL_H
