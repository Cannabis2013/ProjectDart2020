#ifndef DARTSPOINTMODELSSERVICE_H
#define DARTSPOINTMODELSSERVICE_H

#include "idartscontrollermodelsservice.h"
#include "idartscontrollerpoint.h"
#include <qstring.h>
#include <quuid.h>

namespace DartsPointSingleAttemptContext {
    class DartsControllerPointModelsService : public
            IDartsControllerModelsService<IDartsControllerPoint<QUuid,QString,QByteArray>,QString>
    {
    public:
        typedef IDartsControllerPoint<QUuid,QString,QByteArray> PointModel;
        const DartsModelInterface *addPlayerNameToModel(const DartsModelInterface *model, const QString &name) const override;
        const DartsModelInterface *addAccumulatedScoreToModel(const DartsModelInterface *model, const int &score) const override;
    };
}

#endif // DARTSPOINTMODELSSERVICE_H
