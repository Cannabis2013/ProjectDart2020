#ifndef DCRESETSCOREMODELS_H
#define DCRESETSCOREMODELS_H
#include "idcresetscorescoremodels.h"
class DCResetScoreModels : public IDCResetScoreScoreModels
{
public:
    virtual void reset(IDCScoresService *scoresService, const int &initialScore) const override
    {
        auto models = scoresService->scoreModels();
        initializeModels(models,initialScore);
        replaceModels(models,scoresService);
    }
private:
    void initializeModels(IDCScoresService::DartsScoreModels &models, const int &initialScore) const
    {
        for (auto &model : models)
            model.totalScore = initialScore;
    }
    void replaceModels(const IDCScoresService::DartsScoreModels &models, IDCScoresService *scoresService) const
    {
        scoresService->scoreModels().clear();
        scoresService->scoreModels().append(models);
    }
};
#endif // DCRESETSCOREMODELS_H
