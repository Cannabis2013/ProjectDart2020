#ifndef IDARTSCONSISTENCY_H
#define IDARTSCONSISTENCY_H
#include "InputModelsSLAs/abstractdartsinput.h"
#include "ContextSLA/absplactx.h"
class IDartsConsistency
{
public:
    virtual bool verify(IModel<QUuid> *tournament, const QVector<AbstractDartsInput*> &inputs,const AbsPlaCtx *playersContext) const = 0;
};
#endif // IDARTSCONSISTENCY_H
