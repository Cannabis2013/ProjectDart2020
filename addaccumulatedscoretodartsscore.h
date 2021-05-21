#ifndef ADDACCUMULATEDSCORETOMODEL_H
#define ADDACCUMULATEDSCORETOMODEL_H

#include "ibinaryservice.h"
#include "dartsscore.h"
namespace DartsScoreMultiAttemptContext {
    class AddAccumulatedScoreToDartsScore :public
            IBinaryService<const DartsScore*,const int&,const DartsScore*>
    {
    public:
        const DartsScore* service(const DartsScore* model,
                                   const int& totalScore) override
        {
            auto mutableModel = const_cast<DartsScore*>(model);
            mutableModel->setAccumulatedScore(totalScore);
            return mutableModel;
        }
    };
}

#endif // ADDACCUMULATEDSCORETOMODEL_H
