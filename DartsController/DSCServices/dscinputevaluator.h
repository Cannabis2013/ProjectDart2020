#ifndef DSCINPUTEVALUATOR_H
#define DSCINPUTEVALUATOR_H
#include "DartsController/DPCServices/dpcinputevaluator.h"
class DSCInputEvaluator : public AbstractDCInputEvaluator
{
public:
    static DSCInputEvaluator *createInstance()
    {
        return new DSCInputEvaluator();
    }
    virtual void evaluate(AbstractDartsInput *input, const int &scoreCand, IDCMetaInfo *metaInfo, AbstractDartsController *controller,
                          const IDartsStatusCodes *statusCodes, IDCPlayerController *) override
    {
        if(scoreCand >= minimumAllowedScore)
        {
            input->setApproved(true);
            input->setRemainingScore(scoreCand);
            controller->addInputToModelsContext(input);
        }
        else if(scoreCand == 0)
        {
            input->setApproved(true);
            input->setRemainingScore(0);
            updateControllerMeta(input,metaInfo,statusCodes);
            controller->addInputToModelsContext(input);
        }
        else
        {
            input->setScore(0);
            controller->addInputToModelsContext(input);
        }
    }
private:
    void updateControllerMeta(AbstractDartsInput *input, IDCMetaInfo *metaInfo, const IDartsStatusCodes *statusCodes) const
    {
        metaInfo->get().winnerId = input->playerId();
        metaInfo->get().winnerName = input->playerName();
        metaInfo->get().status = statusCodes->winnerFound();
    }
    const int minimumAllowedScore = 2;
};
#endif // SCOREVALIDATOR_H
