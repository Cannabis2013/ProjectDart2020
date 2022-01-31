#ifndef IUPDATEDARTSINDEXES_H
#define IUPDATEDARTSINDEXES_H
#include "TournamentModels/dartsmetamodel.h"
#include "IndexesDbSLAs/idartsindex.h"
#include "DbSLAs/idbcontext.h"
template<typename TModel, typename TUuid = QUuid>
class IUpdateDartsIndexes
{
public:
    typedef TModel Model;
    typedef TUuid Uuid;
    virtual void update(const QByteArray &byteAray, const Uuid &tournamentID) const = 0;
};
#endif // IUPDATEDARTSINDEXES_H
