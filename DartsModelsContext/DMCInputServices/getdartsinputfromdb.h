#ifndef GETDARTSINPUTFROMDB_H
#define GETDARTSINPUTFROMDB_H

#include "DartsModelsContext/InputsDbSLAs/igetdartsinputfromdb.h"
#include "DartsModelsContext/InputsDbSLAs/idartsinput.h"
class GetDartsInputFromDb : public IGetDartsInputFromDb
{
public:
    virtual ModelsContext::IDartsInput *get(const QUuid &tournamentId, const QUuid &playerId,
                                            const int &roundIndex, const int &attemptIndex,
                                            const IModelsDbContext *dbService) const override
    {
        auto models = dbService->models();
        for (const auto &model : models) {
            if(match(model,tournamentId,playerId,roundIndex,attemptIndex))
                return dynamic_cast<ModelsContext::IDartsInput*>(model);
        }
        throw "Model not found";
    }
private:
    bool match(const IModel<QUuid>* model,const QUuid &tournamentId, const QUuid &playerId,
               const int &roundIndex, const int &attemptIndex) const
    {
        auto dartsPointModel = dynamic_cast<const ModelsContext::IDartsInput*>(model);
        if(dartsPointModel->tournamentId() != tournamentId)
            return false;
        else if(dartsPointModel->playerId() != playerId)
            return false;
        else if(dartsPointModel->roundIndex() != roundIndex)
            return false;
        else if(dartsPointModel->attempt() != attemptIndex)
            return false;
        else
            return true;
    }
};

#endif // GETDARTSPOINTFROMDB_H
