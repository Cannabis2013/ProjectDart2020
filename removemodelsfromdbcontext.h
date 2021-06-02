#ifndef REMOVEMODELSFROMDBCONTEXT_H
#define REMOVEMODELSFROMDBCONTEXT_H

#include "idartsinput.h"
#include "ibinaryservice.h"
#include "imodelsdbcontext.h"

namespace DartsModelsContext {
    typedef IModelsDbContext<IPlayerInput,QUuid> ModelsDbService;
    typedef IBinaryService<const QVector<const IPlayerInput*>&,ModelsDbService*,void> IRemoveModelsService;
    class RemoveModelsFromDbContext : public IRemoveModelsService
    {
    public:
        void service(const QVector<const IPlayerInput*>& models,ModelsDbService* dbContext) override
        {
            auto modelIds = createIdsByModels(models);
            removeModelsByIds(modelIds,dbContext);
        }
    private:
        QVector<QUuid> createIdsByModels(const QVector<const IPlayerInput*>& models)
        {
            QVector<QUuid> modelIds;
            for (const auto& model : models)
                modelIds << model->id();
            return modelIds;
        }
        void removeModelsByIds(const QVector<QUuid>& modelIds, ModelsDbService* dbContext)
        {
            for (const auto& modelId : modelIds)
                dbContext->removeModelById(modelId);
        }
    };
}

#endif // REMOVEMODELSFROMDBCONTEXT_H
