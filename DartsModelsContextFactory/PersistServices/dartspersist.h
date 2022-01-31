#ifndef DARTSPERSIST_H
#define DARTSPERSIST_H
#include "DbSLAs/idartspersist.h"
template<typename T> class IDbJsonBuilder;
template<typename T> class IModelConverter;
template<typename T> class IDbContext;
template<typename T> class IModel;
class QUuid;
class DMCServices;
class DartsPersist : public IDartsPersist
{
public:
    typedef IModel<QUuid> Model;
    typedef IDbContext<Model> DbContext;
    typedef IDbJsonBuilder<Model> ModelsConverter;
    typedef IModelConverter<Model> ModelConverter;
    DartsPersist(DMCServices *services);
    bool persistTournamentsChanges() override;
    bool persistInputChanges() override;
    bool persistAllChanges() override;
private:
    bool persistTournaments();
    bool persistInputs();
    bool persist(DbContext *dbContext, ModelsConverter *convertModels, ModelConverter *convertModel);
    DMCServices *_services;
};

#endif // DARTSPERSIST_H
