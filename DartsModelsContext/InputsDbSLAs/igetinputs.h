#ifndef IGETINPUTS_H
#define IGETINPUTS_H
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
#include "ModelsContext/DbSLAs/imodelsdbcontext.h"
#include "DartsModelsContext/TournamentModels/dartsmetamodel.h"
#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"
template<typename TBaseModel, typename TSuperModel>
class IGetInputs
{
public:
    typedef TBaseModel BaseModel;
    typedef TSuperModel SuperModel;
    virtual SuperModel *get(const DartsMetaModel &meta, const IDartsIndex *index, const IDbContext<BaseModel> *dbContext) const = 0;
    virtual QVector<SuperModel*> get(const QUuid& tournamentId, const IDbContext<BaseModel> *dbService) const = 0;
    virtual QVector<SuperModel*> get(const QUuid& tournamentId, const int& hint, const IDbContext<BaseModel> *dbService) const = 0;
};
#endif // IGETINPUTMODELSSERVICE_H
