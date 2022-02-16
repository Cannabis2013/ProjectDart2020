#ifndef DARTSPERSIST_H
#define DARTSPERSIST_H
#include "DbSLAs/idartspersist.h"
template<typename T> class IDbJsonBuilder;
template<typename T> class IModelConverter;
template<typename T> class IDbContext;
template<typename T> class IModel;
class QUuid;
class DartsModelsServices;
class DartsPersist : public IDartsPersist
{
public:
    typedef IModel<QUuid> Model;
    typedef IDbContext<Model> DbContext;
    typedef IDbJsonBuilder<Model> ModelsConverter;
    typedef IModelConverter<Model> ModelConverter;
    DartsPersist(DartsModelsServices *services);
    bool persistTournamentsChanges() override;
    bool persistInputChanges() override;
    bool persistAllChanges() override;
private:
    bool persistTournaments();
    bool persistInputs();
    bool persist(DbContext *dbContext, ModelsConverter *convertModels, ModelConverter *convertModel);
    DartsModelsServices *_services;
};

#endif // DARTSPERSIST_H
