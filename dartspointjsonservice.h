#ifndef DARTSPOINTJSONSERVICE_H
#define DARTSPOINTJSONSERVICE_H

#include <QJsonDocument>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "dartscontrollerindexes.h"
#include "dartscontrollerpoint.h"
#include "idartscontrollerjsonservice.h"


namespace DartsPointControllerContext
{
    typedef IDartscontrollerJsonService<IDartsControllerPoint<QUuid,QString,QByteArray>,
                                   IDartsPointControllerIndexes<QByteArray>,
                                   QByteArray,QUuid> IDartsJsonService;
    class DartsPointJsonService :public IDartsJsonService
    {
    public:
        IdFormat getWinnerIdByJson(const JsonFormat& json) const override;
        JsonFormat createJsonByDartsPoint(const PointModel *model) const override;
        JsonFormat createJsonByWinnerName(const QString &winnerId) const override;
        JsonFormat createJsonByTournamentId(const IdFormat &tournamentId) const override;
    };
}

#endif // DARTSSINGLEATTEMPTPOINTJSONSERVICE_H
