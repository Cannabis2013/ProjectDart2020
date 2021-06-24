#ifndef IADDSCORETODARTSSCOREMODEL_H
#define IADDSCORETODARTSSCOREMODEL_H

#include "idartscontrollerscore.h"
#include <quuid.h>

namespace DartsScoreControllerContext {
    class IAddScoreToDartsScoreModel
    {
    public:
        typedef IDartsControllerScore<QUuid,QString,QByteArray> ScoreModel;
        virtual const ScoreModel* addScoretoModel(const ScoreModel *model, const int &score) const = 0;
    };
}

#endif // IADDTOTALSCORETODARTSSCOREMODEL_H
