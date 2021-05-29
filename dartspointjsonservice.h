#ifndef DARTSSINGLEATTEMPTPOINTJSONSERVICE_H
#define DARTSSINGLEATTEMPTPOINTJSONSERVICE_H

#include <QJsonDocument>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "dartssingleattemptindexes.h"
#include "dartscontrollerpoint.h"
#include "idartspointjsonservice.h"
#include "dartscontrollerplayer.h"

namespace DartsPointSingleAttemptContext
{
    typedef IDartsPointJsonService<IDartsControllerPoint<QUuid,QString,QByteArray>,
                                   IDartsSingleAttemptIndexes,
                                   IDartsControllerPlayer<QUuid,QString>,QByteArray> SingleAttemptJsonService;
    class DartsPointJsonService :public SingleAttemptJsonService
    {
    public:

        QVector<const PointModel *> buildDartsControllerPointByJson(const QByteArray& json) const override;
        QVector<const ControllerPlayer *> assemblePlayerDetailsStructsFromJson(const QByteArray& json) const override;
        const ControllerPlayer *assembleWinnerStructFromJson(const QByteArray& json) const override;
        QByteArray buildJsonByIndexesAndPoint(const DartsIndexes* indexes, const PointModel* model) const override;
        QByteArray assembleJsonWinnerName(const QString &winnerId) const override;
    };
}

#endif // DARTSSINGLEATTEMPTPOINTJSONSERVICE_H
