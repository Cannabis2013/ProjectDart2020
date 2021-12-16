#ifndef GETDARTSINPUTS_H
#define GETDARTSINPUTS_H
#include <qvector.h>
#include <quuid.h>
#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"
#include "DartsModelsContext/TournamentModels/dartsmetamodel.h"
#include "DartsModelsContext/InputsDbSLAs/igetinputs.h"
#include "DartsModelsContext/DbSLAs/idbcontext.h"
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
class GetDartsInputs : public IGetInputs<IModel<QUuid>,AbstractDartsInput>
{
public:
    virtual SuperModel *get(const DartsMetaModel &meta, const IDartsIndex *index, const IDbContext<Model> *dbContext) const override
    {
        auto model = dbContext->model([=](Model *model){
            auto inputModel = dynamic_cast<const SuperModel*>(model);
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
        return dynamic_cast<SuperModel*>(model);
    }
    QVector<SuperModel*> get(const QUuid &tournamentId, const IDbContext<Model> *dbService) const override
    {
        const auto& models = dbService->models();
        auto tournamentInputs = getModels(tournamentId,models);
        return tournamentInputs;
    }
    QVector<SuperModel*> get(const QUuid &tournamentId, const int &hint, const IDbContext<Model> *dbService) const override
    {
        auto tournamentInputs = get(tournamentId,dbService);
        auto inputsByHint = getModels(hint,tournamentInputs);
        return inputsByHint;
    }
private:
    QVector<SuperModel*> getModels(const QUuid &tournamentId, const QVector<Model*> &models) const
    {
        QVector<SuperModel*> list;
        for (const auto& model : models) {
            auto input = dynamic_cast<SuperModel*>(model);
            if(input->tournamentId() == tournamentId)
                list << input;
        }
        return list;
    }
    QVector<SuperModel*> getModels(const int &hint, const QVector<SuperModel*> &inputs) const
    {
        QVector<SuperModel*> list;
        for (const auto& input : inputs) {
            if(input ->hint() == hint)
                list << input;
        }
        return list;
    }
};
#endif // GETINPUTMODELSSERVICE_H
