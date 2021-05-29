#ifndef DARTSSINGLEATTEMPTPOINTJSONSERVICE_H
#define DARTSSINGLEATTEMPTPOINTJSONSERVICE_H

#include <QJsonDocument>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "dartssingleattemptindexes.h"
#include "dartscontrollerpoint.h"
#include "idartspointjsonservice.h"

namespace DartsPointSingleAttemptContext
{
    typedef IDartsPointJsonService<IDartsControllerPoint<QUuid,QString,QByteArray>,
                                   IDartsSingleAttemptIndexes,
                                   QByteArray,QUuid> SingleAttemptJsonService;
    class DartsPointJsonService :public SingleAttemptJsonService
    {
    public:
        QUuid getWinnerIdByJson(const QByteArray& json) const override;
        QByteArray buildJsonByIndexesAndPoint(const DartsIndexes* indexes, const PointModel* model) const override;
        QByteArray assembleJsonWinnerName(const QString &winnerId) const override;
    };
}

#endif // DARTSSINGLEATTEMPTPOINTJSONSERVICE_H
