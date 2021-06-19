#ifndef DARTSSINGLEATTEMPTPOINTJSONSERVICE_H
#define DARTSSINGLEATTEMPTPOINTJSONSERVICE_H

#include <QJsonDocument>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "dartssingleattemptindexes.h"
#include "dartscontrollerpoint.h"
#include "idartscontrollerjsonservice.h"


namespace DartsPointControllerContext
{
    typedef IDartscontrollerJsonService<IDartsControllerPoint<QUuid,QString,QByteArray>,
                                   IDartsPointControllerIndexes,
                                   QByteArray,QUuid> IDartsJsonService;
    class DartsPointJsonService :public IDartsJsonService
    {
    public:
        QByteArray convertDartsIndexesToJson(const DartsIndexes* indexes) const override;
        QUuid getWinnerIdByJson(const QByteArray& json) const override;
        QByteArray assembleJsonWinnerName(const QString &winnerId) const override;

        // IDartscontrollerJsonService interface
    public:
        QByteArray convertDartsModelToJson(const PointModel *model) const override;
    };
}

#endif // DARTSSINGLEATTEMPTPOINTJSONSERVICE_H
