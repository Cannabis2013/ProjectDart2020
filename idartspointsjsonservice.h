#ifndef IDARTSPOINTSJSONSERVICE_H
#define IDARTSPOINTSJSONSERVICE_H

#include <qbytearray.h>
#include <qvector.h>

namespace DartsModelsContext {
    template<typename TModelInterface,typename TPlayerModelsService, typename TIndexesInterface, typename TJsonFormat>
    class IDartsPointsJsonService
    {
    public:
        typedef TModelInterface ModelInterface;
        typedef TPlayerModelsService PlayerModelsInterface;
        typedef TIndexesInterface IndexesInterface;
        typedef TJsonFormat JsonFormat;
        virtual JsonFormat assembleJsonDartsPointIndexes(const IndexesInterface*) const = 0;
        virtual JsonFormat assembleJsonOrderedDartsPointModels(const QVector<const ModelInterface*>&,
                                                               const PlayerModelsInterface*) const = 0;
        virtual JsonFormat assembleJsonFromTournamentDartsPoints(const QVector<const ModelInterface*>& models) const = 0;
        virtual const ModelInterface* assembleDartsPointModelFromJson(const JsonFormat&) const = 0;
    };
}


#endif // IDARTSPOINTSJSONSERVICE_H
