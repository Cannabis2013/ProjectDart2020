#ifndef GETDARTSPOINTFROMDB_H
#define GETDARTSPOINTFROMDB_H

#include "igetdartspointfromdb.h"
#include "idartspointinput.h"
class GetDartsPointFromDb : public IGetDartsPointFromDb
{
public:
    virtual const IPlayerInput *get(const QUuid &tournamentId, const QUuid &playerId,
                                    const int &roundIndex, const int &attemptIndex,
                                    const IDartsInputDb *dbService) const override
    {
        auto models = dbService->models();
        for (const auto &model : models) {
            if(match(model,tournamentId,playerId,roundIndex,attemptIndex))
                return model;
        }
        throw "Model not found";
    }
private:
    bool match(const IPlayerInput* model,const QUuid &tournamentId, const QUuid &playerId,
               const int &roundIndex, const int &attemptIndex) const
    {
        auto dartsPointModel = dynamic_cast<const DartsModelsContext::IDartsPointInput*>(model);
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
