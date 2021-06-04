#ifndef DARTSPOINTSJSONSERVICE_H
#define DARTSPOINTSJSONSERVICE_H

#include "idartspointsjsonservice.h"
#include "iplayerinput.h"
#include "imodelsdbcontext.h"
#include "iplayermodelsservice.h"
#include "idartspointindexes.h"
#include "iunaryservice.h"
#include "ibinaryservice.h"

namespace DartsModelsContext {
    class DartsPointsJsonService : public
            IDartsPointsJsonService<IPlayerInput,IPlayerModelsService,IDartsPointIndexes,QByteArray>
    {
    public:

        // IDartsPointsJsonService interface
    public:
        virtual JsonFormat assembleJsonDartsPointIndexes(const IndexesInterface *indexes) const override;
        virtual JsonFormat assembleJsonOrderedDartsPointModels(const QVector<const ModelInterface *> &, const PlayerModelsInterface *) const override;
        virtual JsonFormat assembleJsonFromTournamentDartsPoints(const QVector<const ModelInterface *> &models) const override;
        virtual const ModelInterface *assembleDartsPointModelFromJson(const JsonFormat &) const override;
        // Set service methods
        DartsPointsJsonService* setAssembleJsonDartsPointIndexes(IUnaryService<const IDartsPointIndexes *, QByteArray> *newAssembleJsonDartsPointIndexes);
        DartsPointsJsonService* setAssembleJsonOrderedDartsPointModels(IBinaryService<const QVector<const IPlayerInput *> &, const IPlayerModelsService *, const QByteArray> *newAssembleJsonOrderedDartsPointModels);

    private:
        IUnaryService<const IDartsPointIndexes*,QByteArray>* _assembleJsonDartsPointIndexes;
        IBinaryService<const QVector<const IPlayerInput*>&,
                       const IPlayerModelsService*,const QByteArray>* _assembleJsonOrderedDartsPointModels;
        IUnaryService<const QVector<const IPlayerInput*>&,
                       QByteArray>* _assembleJsonFromTournamentDartsPoints;
        IUnaryService<const QByteArray&,const IPlayerInput*>* _assembleDartsPointModelFromJson;
    };
}


#endif // DARTSPOINTSJSONSERVICE_H
