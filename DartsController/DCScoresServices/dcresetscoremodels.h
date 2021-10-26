#ifndef DCRESETSCOREMODELS_H
#define DCRESETSCOREMODELS_H
#include "DartsController/DCScoresSLAs/idcresetscorescoremodels.h"
class DCResetScoreModels : public IDCResetScoreScoreModels
{
public:
    virtual void reset(IDCScoreModels *scoresService, const int &initialScore) const override
    {
        auto models = scoresService->scores();
        initializeModels(models,initialScore);
        replaceModels(models,scoresService);
    }
private:
    void initializeModels(IDCScoreModels::DartsScoreModels &models, const int &initialScore) const
    {
        for (auto &model : models)
            model.remainingScore = initialScore;
    }
    void replaceModels(const IDCScoreModels::DartsScoreModels &models, IDCScoreModels *scoresService) const
    {
        scoresService->scores().clear();
        scoresService->scores().append(models);
    }
};
#endif // DCRESETSCOREMODELS_H
