#ifndef DARTSSINGLEATTEMPTPOINTJSONSERVICE_H
#define DARTSSINGLEATTEMPTPOINTJSONSERVICE_H

#include <QJsonDocument>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "dartssingleattemptindexes.h"
#include "idartscontrollerpoint.h"
#include "idartspointjsonservice.h"
#include "dartscontrollerplayer.h"


namespace DartsPointSingleAttemptContext
{
    typedef IDartsControllerPoint<QUuid,QString,QByteArray> ControllerPoint;
    typedef IDartsPointJsonService<ControllerPoint,IDartsSingleAttemptIndexes> SingleAttemptJsonService;
    class DartsPointJsonService :
            public SingleAttemptJsonService
    {
    public:
        QVector<const ExtendedInputValues *> assembleExtendedInputModelsFromJson(const QByteArray& json) const override;
        QVector<const ControllerPlayer *> assemblePlayerDetailsStructsFromJson(const QByteArray& json) const override;
        const ControllerPlayer *assembleWinnerStructFromJson(const QByteArray& json) const override;
        QByteArray assembleJsonAddPointValues(const QUuid& tournamentId, const DartsIndexes* indexes, const QUuid &winnerId, const PointModel* model) const override;
        QByteArray assembleJsonWinnerName(const QString &winnerId) const override;
    };
}

#endif // DARTSSINGLEATTEMPTPOINTJSONSERVICE_H
