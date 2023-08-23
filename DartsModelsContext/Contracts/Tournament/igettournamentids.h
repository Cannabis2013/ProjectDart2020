#ifndef IGETDARTSTOURNAMENTIDS_H
#define IGETDARTSTOURNAMENTIDS_H

#include <quuid.h>

template<typename TBaseModel, typename TDbCtx>
class IGetDartsTournamentIds
{
public:
    typedef TBaseModel BaseModel;
    typedef TDbCtx DbCtx;
    virtual QVector<QUuid> get(const QVector<int> &indexes, const DbCtx *dbContext) const = 0;
};
#endif // IGETTOURNAMNETIDS_H
