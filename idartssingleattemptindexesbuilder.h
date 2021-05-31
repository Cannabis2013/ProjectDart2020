#ifndef IDARTSINDEXESBUILDER_H
#define IDARTSINDEXESBUILDER_H

#include <qvector.h>
namespace DartsModelsContext{
    template<typename TIndexesInterface, typename TInputModelInterface>
    class IDartsSingleAttemptIndexesBuilder{
    public:
        typedef TInputModelInterface InputModelInterface;
        typedef TIndexesInterface IndexesInterface;
        virtual const IndexesInterface* buildIndexes(const QVector<const InputModelInterface*>& inputModels,
                                                     const int& assignedPlayerCount,
                                                     const int& numberOfAttempts) const = 0;
    };
}

#endif // IDARTSINDEXESBUILDER_H
