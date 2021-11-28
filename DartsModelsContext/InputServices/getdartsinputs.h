#ifndef GETDARTSINPUTS_H
#define GETDARTSINPUTS_H
#include "DartsModelsContext/InputsDbSLAs/igetinputs.h"
#include "DartsModelsContext/InputModelsSLAs/iplayerinput.h"
#include "ModelsContext/DbSLAs/idbcontext.h"
class GetDartsInputs : public IGetInputs<IModel<QUuid>,AbstractDartsInput>
{
public:
    virtual SuperModel *get(const DartsMetaModel &meta, const IDartsIndex *index, const IDbContext<BaseModel> *dbContext) const override
    {
        auto models = dbContext->models();
        auto model = dbContext->model([=](IModel<QUuid> *model){
            auto inputModel = dynamic_cast<const AbstractDartsInput*>(model);
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
        });
        return dynamic_cast<AbstractDartsInput*>(model);
    }
    QVector<SuperModel*> get(const QUuid &tournamentId, const IDbContext<BaseModel> *dbService) const override
    {
        const auto& models = dbService->models();
        auto tournamentInputs = getModels(tournamentId,models);
        return tournamentInputs;
    }
    QVector<SuperModel*> get(const QUuid &tournamentId, const int &hint, const IDbContext<BaseModel> *dbService) const override
    {
        auto tournamentInputs = get(tournamentId,dbService);
        auto inputsByHint = getModels(hint,tournamentInputs);
        return inputsByHint;
    }
private:
    QVector<AbstractDartsInput*> getModels(const QUuid &tournamentId, const QVector<IModel<QUuid>*> &models) const
    {
        QVector<AbstractDartsInput*> list;
        for (const auto& model : models) {
            auto input = dynamic_cast<AbstractDartsInput*>(model);
            if(input->tournamentId() == tournamentId)
                list << input;
        }
        return list;
    }
    QVector<AbstractDartsInput*> getModels(const int &hint, const QVector<AbstractDartsInput*> &inputs) const
    {
        QVector<AbstractDartsInput*> list;
        for (const auto& input : inputs) {
            if(input ->hint() == hint)
                list << input;
        }
        return list;
    }
};
#endif // GETINPUTMODELSSERVICE_H
