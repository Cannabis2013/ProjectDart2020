#ifndef REMOVEMODELSFROMDB_H
#define REMOVEMODELSFROMDB_H

#include "iremovemodelsfromdb.h"
#include "idbservice.h"

namespace ModelsContext{
    class RemoveModelsFromDb :
            public IRemoveModelsFromDb<IDbService>
    {
    public:
        virtual bool remove(const QVector<int> &indexes, IDbService *dbService) const override;
    };
}
#endif // TOURNAMENTMODELCONTEXT_H
