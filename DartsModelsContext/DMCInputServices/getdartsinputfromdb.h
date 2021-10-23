#ifndef GETDARTSINPUTFROMDB_H
#define GETDARTSINPUTFROMDB_H

#include "DartsModelsContext/InputsDbSLAs/igetdartsinput.h"
#include "DartsModelsContext/InputsDbSLAs/idartsinput.h"
class GetDartsInputFromDb : public IGetDartsInput
{
public:
    virtual ModelsContext::IDartsInput *get(const DartsMetaModel &meta, const IDartsIndex *index, const IModelsDbContext *dbService) const override
    {
        auto models = dbService->models();
        for (const auto &model : models) {
            if(match(model,meta,index))
                return dynamic_cast<ModelsContext::IDartsInput*>(model);
        }
        return nullptr;
    }
private:
    bool match(const IModel<QUuid>* model, const DartsMetaModel &meta, const IDartsIndex *index) const
    {
        auto inputModel = dynamic_cast<const ModelsContext::IDartsInput*>(model);
        if(inputModel->tournamentId() != meta.tournamentId)
            return false;
        else if(inputModel->playerId() != meta.playerId)
            return false;
        else if(inputModel->roundIndex() != index->roundIndex())
            return false;
        else if(inputModel->attempt() != index->attemptIndex())
            return false;
        else
            return true;
    }
};

#endif // GETDARTSPOINTFROMDB_H
