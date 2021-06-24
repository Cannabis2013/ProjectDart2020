#ifndef IADDTOTALSCORETODARTSPOINT_H
#define IADDTOTALSCORETODARTSPOINT_H

#include "idartscontrollerpoint.h"
#include "iaddtomodel.h"
#include <quuid.h>

class IAddTotalScoreToDartsPoint : public
        IAddToModel<DartsPointControllerContext::IDartsControllerPoint<QUuid,QString,QByteArray>,int>
{
public:
    virtual void add(const ModelInterface *model, const Value &totalScore) override = 0;
};

#endif // IADDPLAYERNAMETODARTSPOINT_H
