#ifndef DARTSSCOREJSONSERVICE_H
#define DARTSSCOREJSONSERVICE_H

#include "idartsscorejsonservice.h"
#include "iplayerinput.h"
#include "idartsscoreindexes.h"
#include <qbytearray.h>
#include "iunaryservice.h"

namespace DartsModelsContext {
    class DartsScoreJsonService : public
            IDartsScoreJsonService<IPlayerInput,IDartsScoreIndexes,QByteArray>
    {
    public:
        static DartsScoreJsonService* createInstance();
        virtual JsonFormat assembleJsonDartsScoreIndexes(const ModelIndexes *) const override;
        virtual JsonFormat assembleJsonFromDartsMultiAttemptScores(const QVector<const ModelInterface *> &) const override;
        DartsScoreJsonService* setAssembleJsonByDartsScoreIndexes(IUnaryService<const IDartsScoreIndexes *, QByteArray> *newAssembleJsonByDartsScoreIndexes);
        DartsScoreJsonService* setAssembleJsonFromDartsMultiAttemptScores(IUnaryService<const QVector<const IPlayerInput *> &, QByteArray> *newAssembleJsonFromDartsMultiAttemptScores);

    private:
        IUnaryService<const IDartsScoreIndexes*,QByteArray>* _assembleJsonByDartsScoreIndexes;
        IUnaryService<const QVector<const IPlayerInput*>&,
                                    QByteArray>* _assembleJsonFromDartsMultiAttemptScores;
    };
}

#endif // DARTSSCOREJSONSERVICE_H
