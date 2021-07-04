#ifndef DARTSSCOREJSONSERVICE_H
#define DARTSSCOREJSONSERVICE_H

#include "idartsscorejsonservice.h"
#include "iplayerinput.h"
#include "idartsscoreindexes.h"
#include <qbytearray.h>
#include "iunaryservice.h"
#include "assemblejsonbydartsscoreindexes.h"
#include "assemblejsonfromdartsscores.h"

namespace DartsModelsContext {
    class DartsScoreJsonService : public
            IDartsScoreJsonService<IPlayerInput,IDartsScoreIndexes,QByteArray>
    {
    public:
        static DartsScoreJsonService* createInstance();
        virtual JsonFormat assembleJsonDartsScoreIndexes(const ModelIndexes *) const override;
        virtual JsonFormat assembleJsonFromDartsMultiAttemptScores(const QVector<const ModelInterface *> &) const override;
    private:
        IUnaryService<const IDartsScoreIndexes*,QByteArray>* _assembleJsonByDartsScoreIndexes =
                new AssembleJsonByDartsScoreIndexes;
        IUnaryService<const QVector<const IPlayerInput*>&,
                      QByteArray>* _assembleJsonFromDartsScores = new AssembleJsonFromDartsScores;
    };
}

#endif // DARTSSCOREJSONSERVICE_H
