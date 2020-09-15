#ifndef IROUNDMODEL_H
#define IROUNDMODEL_H

#include "itournamentmodel.h"

template<class TUuid, class TList>
class IRound : public IModel<TUuid>
{
public:
    virtual int index() const = 0;
    virtual void setIndex(const int &val) = 0;
};

#endif // IROUNDMODEL_H
