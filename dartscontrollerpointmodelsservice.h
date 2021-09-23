#ifndef DARTSCONTROLLERPOINTMODELSSERVICE_H
#define DARTSCONTROLLERPOINTMODELSSERVICE_H

#include "idartscontrollermodelsservice.h"
#include "DartsController/DCInputSLAs/idcinputmodel.h"
#include <qstring.h>
#include <quuid.h>

namespace DCContext {
    class DartsControllerPointModelsService : public IDartsControllerModelsService<IDCInputModel,QString,QUuid>
    {
    public:
        void addAccumulatedScoreToModel(const DartsModelInterface *model, const int &score) const override;
        void addPlayerIdToModel(const DartsModelInterface *model, const IdFormat &id) const override;
    };
}

#endif // DARTSPOINTMODELSSERVICE_H
