#ifndef DARTSMULTIATTEMPTJSONSERVICE_H
#define DARTSMULTIATTEMPTJSONSERVICE_H

#include "idartsscorejsonbuilderservice.h"

#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "idartscontrollerscore.h"
#include "iplayerscoreservice.h"

namespace DartsScoreMultiAttemptContext
{
    class DartsScoreJsonBuilderService :
            public IDartsScoreJsonBuilderService<IDartsControllerScore<QUuid,QString,QByteArray>>
    {
    public:
        QByteArray assembleJsonAddScoreValues(const QUuid &tournamentId,
                                              const int &roundIndex, const int &setIndex,
                                              const QUuid &winnerId, const QUuid &playerId,
                                              const int &score) const override;
        QByteArray assembleJsonWinnerName(const QUuid &tournamentId, const QUuid &winnerId) const override;

        QByteArray buildJsonByDartsScoreModels(const QVector<const InputModelInterface*>& inputModels) const override;
    };
}


#endif // DARTSMULTIATTEMPTJSONSERVICE_H
