#ifndef DARTSCONTROLLERPOINTMODELSSERVICE_H
#define DARTSCONTROLLERPOINTMODELSSERVICE_H

#include "idartscontrollermodelsservice.h"
#include "idartscontrollerpoint.h"
#include <qstring.h>
#include <quuid.h>

namespace DartsPointControllerContext {
    class DartsControllerPointModelsService : public
            IDartsControllerModelsService<IDartsControllerPoint<QUuid,QString,QByteArray>,QString,QUuid>
    {
    public:
        typedef IDartsControllerPoint<QUuid,QString,QByteArray> PointModel;
        void addAccumulatedScoreToModel(const DartsModelInterface *model, const int &score) const override;
        void addPlayerIdToModel(const DartsModelInterface *model, const IdFormat &id) const override;
    };
}

#endif // DARTSPOINTMODELSSERVICE_H