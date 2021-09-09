#ifndef DCGETPLAYERNAME_H
#define DCGETPLAYERNAME_H

#include "idcgetplayername.h"
class DCGetPlayerName : public IDCGetPlayerName
{
public:
    virtual QString playerName(const QUuid &id, IDCScoresService *scoresService) const override
    {
        auto scoreModels = scoresService->scoreModels();
        auto model = scoreModel(id,scoreModels);
        return model.name;
    }
private:
    DCContext::DCScoreModel scoreModel(const QUuid &id, const IDCScoresService::DartsScoreModels &models) const
    {
        for (const auto &model : models) {
            if(model.id == id)
                return model;
        }
        return DCContext::DCScoreModel();
    }
};

#endif // DCGETPLAYERNAME_H
