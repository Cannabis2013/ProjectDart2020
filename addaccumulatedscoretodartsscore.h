#ifndef ADDACCUMULATEDSCORETOMODEL_H
#define ADDACCUMULATEDSCORETOMODEL_H

#include "ibinaryservice.h"
#include "idartscontrollerscore.h"
#include <quuid.h>
namespace DartsScoreControllerContext {
    class AddAccumulatedScoreToDartsScore :public
            IBinaryService<const IDartsControllerScore<QUuid,QString,QByteArray>*,const int&,
                           const IDartsControllerScore<QUuid,QString,QByteArray>*>
    {
    public:
        typedef IDartsControllerScore<QUuid,QString,QByteArray> ControllerScore;
        const ControllerScore* service(const ControllerScore* model,
                                   const int& totalScore) override
        {
            auto mutableModel = const_cast<ControllerScore*>(model);
            mutableModel->setAccumulatedScore(totalScore);
            return mutableModel;
        }
    };
}

#endif // ADDACCUMULATEDSCORETOMODEL_H
