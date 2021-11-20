#ifndef DCUPDATEINPUTDETAILS_H
#define DCUPDATEINPUTDETAILS_H
#include "DartsController/DCScoresSLAs/idcupdateplayerscores.h"
class DCUpdateInputDetails : public IDCUpdatePlayerScores
{
public:
    void update(const QVector<IModel<QUuid>*> &models, AbstractDCScoresCtx *scoreController) const override
    {
        for (const auto &model : models) {
            auto input = dynamic_cast<AbstractDartsInput*>(model);
            auto scoreModel = &scoreController->score(input->playerId());
            if(input->remainingScore() < scoreModel->remainingScore)
                scoreModel->remainingScore = input->remainingScore();
        }
    }
private:
};
#endif // DPCSUBTRACTPLAYERSCORE_H
