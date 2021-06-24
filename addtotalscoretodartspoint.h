#ifndef ADDTOTALSCORETODARTSPOINT_H
#define ADDTOTALSCORETODARTSPOINT_H

#include "iaddtotalscoretodartspoint.h"

namespace DartsPointControllerContext {
    class AddTotalScoreToDartsPoint : public IAddTotalScoreToDartsPoint
    {
    public:
        virtual void add(const ModelInterface *model, const Value &totalScore) override
        {
            auto mutableModel = const_cast<ModelInterface*>(model);
            mutableModel->setTotalScore(totalScore);
        }
    };
}

#endif // ADDTOTALSCORETODARTSPOINT_H
