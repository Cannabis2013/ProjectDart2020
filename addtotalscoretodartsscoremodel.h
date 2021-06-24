#ifndef ADDTOTALSCORETODARTSSCOREMODEL_H
#define ADDTOTALSCORETODARTSSCOREMODEL_H

#include "iaddscoretodartsscoremodel.h"
#include "idartscontrollerscore.h"
#include <quuid.h>
namespace DartsScoreControllerContext {
    class AddTotalScoreToDartsScoreModel :public
            IAddScoreToDartsScoreModel
    {
    public:
        typedef IDartsControllerScore<QUuid,QString,QByteArray> ControllerScore;
        const ControllerScore* addScoretoModel(const ControllerScore* model,
                                               const int& score) const override
        {
            auto mutableModel = const_cast<ControllerScore*>(model);
            mutableModel->setTotalScore(score);
            return mutableModel;
        }
    };
}

#endif // ADDACCUMULATEDSCORETOMODEL_H
