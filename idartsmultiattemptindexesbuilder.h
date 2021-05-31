#ifndef IDARTSMULTIATTEMPTINDEXESBUILDER_H
#define IDARTSMULTIATTEMPTINDEXESBUILDER_H

#include <qvector.h>

namespace DartsModelsContext {
    template<typename TIndexesInterface, typename TInputModelInterface>
    class IDartsMultiAttemptIndexesBuilder{
    public:
        typedef TInputModelInterface InputModelInterface;
        typedef TIndexesInterface IndexesInterface;
        virtual const IndexesInterface* buildIndexes(const QVector<const InputModelInterface*>& inputModels,
                                                     const int& assignedPlayerCount) const = 0;
    };
}

#endif // IDARTSMULTIATTEMPTINDEXESBUILDER_H
