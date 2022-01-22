#ifndef IDARTSCONSISTENCY_H
#define IDARTSCONSISTENCY_H
#include "InputModelsSLAs/idartsinput.h"
#include "ContextSLA/absplactx.h"
template<typename TModel>
class IDartsConsistency
{
public:
    typedef TModel Model;
    typedef QVector<Model*> Models;
    virtual bool verify(Model *tournament, const Models &inputs,const AbsPlaCtx *playersContext) const = 0;
};
#endif // IDARTSCONSISTENCY_H
