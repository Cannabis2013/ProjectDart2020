#ifndef IDARTSPOINTSJSONSERVICE_H
#define IDARTSPOINTSJSONSERVICE_H

#include <qbytearray.h>
#include <qvector.h>

namespace DartsModelsContext {
    template<typename TModelInterface,
             typename TIndexesInterface,
             typename TJsonFormat>
    class IDartsPointsJsonService
    {
    public:
        typedef TModelInterface ModelInterface;
        typedef TIndexesInterface IndexesInterface;
        typedef TJsonFormat JsonFormat;
        virtual JsonFormat createJson(const IndexesInterface*) const = 0;
        virtual JsonFormat createJson(const QVector<const ModelInterface*>& models) const = 0;
    };
}


#endif // IDARTSPOINTSJSONSERVICE_H
