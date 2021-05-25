#ifndef DARTSSINGLEATTEMPTPOINTJSONSERVICE_H
#define DARTSSINGLEATTEMPTPOINTJSONSERVICE_H

#include "idartspointjsonservice.h"
#include <QJsonDocument>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "dartssingleattemptindexes.h"

namespace DartsPointSingleAttemptContext
{
    typedef IDartsPointJsonService<IDartsSingleAttemptIndexes> SingleAttemptJsonService;
    class DartsPointJsonService :
            public SingleAttemptJsonService
    {
    public:
        QVector<const ExtendedInputValues *> assembleExtendedInputModelsFromJson(const QByteArray& json) const override;
        QVector<const PlayerDetailsStruct *> assemblePlayerDetailsStructsFromJson(const QByteArray& json) const override;
        const PlayerDetailsStruct *assembleWinnerStructFromJson(const QByteArray& json) const override;
        QByteArray assembleJsonAddPointValues(const QUuid& tournamentId, const int& roundIndex, const int &setIndex,
                                              const int &attemptIndex, const QUuid &winnerId, const QUuid &playerId,
                                              const int &point, const int &score, const int &modKeyCode) const override;
        QByteArray assembleJsonWinnerName(const QString &winnerId) const override;
    };
}

#endif // DARTSSINGLEATTEMPTPOINTJSONSERVICE_H
