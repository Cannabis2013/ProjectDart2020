#ifndef IADDTOTALSCORETODARTSPOINT_H
#define IADDTOTALSCORETODARTSPOINT_H

#include "idpcmodel.h"
#include "iaddtomodel.h"
#include <quuid.h>

class IAddTotalScoreToDartsPoint : public
        IAddToModel<DPCContext::IDPCModel,int>
{
public:
    virtual void add(const ModelInterface *model, const Value &totalScore) override = 0;
};

#endif // IADDPLAYERNAMETODARTSPOINT_H
