#ifndef ADDTOTALSCORETODARTSINPUTS_H
#define ADDTOTALSCORETODARTSINPUTS_H

#include "iaddtotalscoretodartsinputs.h"
#include "idartscontrollerpoint.h"
#include <qvector.h>

namespace DartsPointControllerContext {
    class AddTotalScoreToDartsInputs : public IAddTotalScoreToDartsInputs
    {
    public:
        void addTotalScoreToInputs(const InputModels &inputModels, const int &initialPoint) const override;
    private:
        QVector<QUuid> buildListOfPlayerIds(const InputModels &inputModels) const;
        InputModels getPointInputModelsByPlayerId(const InputModels &inputModels, const QUuid &playerId) const;
        void addTotalScoresToInputModels(const InputModels &inputModels,
                                     const int &initialScore) const;
    };
}

#endif // ADDTOTALSCORETODARTSINPUTS_H
