#ifndef GETLASTENTEREDDARTSPOINTMODEL_H
#define GETLASTENTEREDDARTSPOINTMODEL_H

#include "iternaryservice.h"
#include "idartspointinput.h"
#include <quuid.h>
#include "dartspointindexes.h"
#include <qvector.h>
#include "idartssingleattemptindexesbuilder.h"

namespace DartsModelsContext {
    class DartsSingleAttemptIndexesBuilder : public IDartsSingleAttemptIndexesBuilder<IDartsPointIndexes, IDartsInput>
    {
    public:
        enum ModelDisplayHint{
            HiddenHint = 0x1,
            DisplayHint = 0x2,
            allHints = HiddenHint | DisplayHint
        };
        const IDartsPointIndexes* buildIndexes(const QVector<const IDartsInput*>& orderedModels,
                                               const int& assignedPlayersCount,
                                               const int& numberOfAttempts) const override;
    private:
        const IDartsPointIndexes* assembleDartsIndexesByModels(const QVector<const IDartsInput*>& orderedModels,
                                                               const int& assignedPlayersCount,
                                                               const int& attempts) const;;
        const IDartsPointIndexes* assembleInitialDartsIndexes() const;
    };
}


#endif // GETLASTENTEREDDARTSPOINTMODEL_H
