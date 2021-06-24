#ifndef DARTSMULTIATTEMPTJSONSERVICE_H
#define DARTSMULTIATTEMPTJSONSERVICE_H

#include "idartsscorejsonbuilderservice.h"

#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "idartscontrollerscore.h"
#include "iplayerscoreservice.h"
#include "idartsscorecontrollerindexes.h"

namespace DartsScoreControllerContext
{
    class DartsScoreJsonBuilderService :
            public IDartsScoreJsonBuilderService<IDartsControllerScore<QUuid,QString,QByteArray>,
                                         IDartsScoreControllerIndexes<QByteArray>,QByteArray,QString>
    {
    public:
        QByteArray createJsonByDartsScore(const ModelInterface* model) const override;
        QByteArray createJsonByIds(const QUuid &tournamentId, const QUuid &winnerId) const override;
        QByteArray createJsonByDartsScoreModels(const QVector<const ModelInterface*>& inputModels) const override;
    };
}


#endif // DARTSMULTIATTEMPTJSONSERVICE_H
