#ifndef DMCGETINPUTFROMDB_H
#define DMCGETINPUTFROMDB_H

#include "DartsModelsContext/DMCInputSLAs/igetdartsinputfromdb.h"
#include "DartsModelsContext/DMCInputSLAs/idartsinput.h"
class DMCGetInputFromDb : public IGetDartsInputFromDb
{
public:
    virtual const IModel<QUuid> *get(const QUuid &tournamentId, const QUuid &playerId,
                                    const int &roundIndex, const int &attemptIndex,
                                    const IModelsDbContext *dbService) const override
    {
        auto models = dbService->models();
        for (const auto &model : models) {
            if(match(model,tournamentId,playerId,roundIndex,attemptIndex))
                return model;
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
