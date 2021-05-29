#ifndef DARTSMULTIATTEMPTJSONSERVICE_H
#define DARTSMULTIATTEMPTJSONSERVICE_H

#include "idartsscorejsonbuilderservice.h"

#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "idartscontrollerscore.h"
#include "iplayerscoreservice.h"
#include "idartsmultiattemptindexes.h"

namespace DartsScoreMultiAttemptContext
{
    class DartsScoreJsonBuilderService :
            public IDartsScoreJsonBuilderService<IDartsControllerScore<QUuid,QString,QByteArray>,
                                         IDartsMultiAttemptIndexes,QByteArray,QString>
    {
    public:
        QByteArray buildJsonAddScoreValues(const DartsIndexes* indexes, const ModelInterface* model) const override;
        QByteArray assembleJsonWinnerName(const QUuid &tournamentId, const QUuid &winnerId) const override;
        QByteArray buildJsonByDartsScoreModels(const QVector<const ModelInterface*>& inputModels) const override;
    };
}


#endif // DARTSMULTIATTEMPTJSONSERVICE_H
