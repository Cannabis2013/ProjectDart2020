#ifndef IUPDATEDARTSINDEXES_H
#define IUPDATEDARTSINDEXES_H
#include "TournamentModels/dartsmetamodel.h"
#include "IndexesDbSLAs/idartsindex.h"
#include "DbSLAs/idbcontext.h"
template<typename TBaseModel, typename TUuid = QUuid>
class IUpdateDartsIndexes
{
public:
    typedef TBaseModel BaseModel;
    typedef TUuid Uuid;
    virtual IDbContext<BaseModel> *update(IDartsIndex *model, const Uuid &tournament, IDbContext<BaseModel> *dbContext) const = 0;
};
#endif // IUPDATEDARTSINDEXES_H
