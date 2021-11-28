#ifndef IRESETDARTSTOURNAMENT_H
#define IRESETDARTSTOURNAMENT_H
#include "ModelsContext/DbSLAs/idbcontext.h"
#include <quuid.h>
template<typename TBaseModel, typename TUuid = QUuid>
class IResetDartsTournament
{
public:
    typedef TBaseModel BaseModel;
    typedef TUuid Id;
    virtual IDbContext<BaseModel> *reset(const Id &tournamentId, IDbContext<BaseModel> *dbContext) const = 0;
};
#endif // IRESETDARTSTOURNAMENT_H
