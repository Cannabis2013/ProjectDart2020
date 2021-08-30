#ifndef DARTSCONTROLLERPOINTMODELSSERVICE_H
#define DARTSCONTROLLERPOINTMODELSSERVICE_H

#include "idartscontrollermodelsservice.h"
#include "idpcmodel.h"
#include <qstring.h>
#include <quuid.h>

namespace DPCContext {
    class DartsControllerPointModelsService : public
            IDartsControllerModelsService<IDPCModel,QString,QUuid>
    {
    public:
        void addAccumulatedScoreToModel(const DartsModelInterface *model, const int &score) const override;
        void addPlayerIdToModel(const DartsModelInterface *model, const IdFormat &id) const override;
    };
}

#endif // DARTSPOINTMODELSSERVICE_H
