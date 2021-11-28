#ifndef IGETDARTSTOURNAMENTIDS_H
#define IGETDARTSTOURNAMENTIDS_H
#include <quuid.h>
#include <qvector.h>
#include "ModelsContext/DbSLAs/imodelsdbcontext.h"
template<typename TBaseModel>
class IGetDartsTournamentIds
{
public:
    typedef TBaseModel BaseModel;
    virtual QVector<QUuid> get(const QVector<int> &indexes, const IDbContext<BaseModel> *dbContext) const = 0;
};
#endif // IGETTOURNAMNETIDS_H
