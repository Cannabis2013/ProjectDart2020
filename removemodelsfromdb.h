#ifndef REMOVEMODELSFROMDB_H
#define REMOVEMODELSFROMDB_H

#include "iremovemodelsfromdb.h"
#include "imodelsdbcontext.h"

namespace ModelsContext{
    class RemoveModelsFromDb :
            public IRemoveModelsFromDb<IModelsDbContext>
    {
    public:
        virtual bool remove(const QVector<int> &indexes, IModelsDbContext *dbService) const override;
    };
}
#endif // TOURNAMENTMODELCONTEXT_H
