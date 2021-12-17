#ifndef IDARTSCONSISTENCY_H
#define IDARTSCONSISTENCY_H
#include "PlayerModelsContext/SLAs/absplactx.h"
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
class IDartsConsistency
{
public:
    virtual bool verify(IModel<QUuid> *tournament, const QVector<AbstractDartsInput*> &inputs,const AbsPlaCtx *playersContext) const = 0;
};
#endif // IDARTSCONSISTENCY_H
