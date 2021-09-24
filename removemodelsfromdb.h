#ifndef REMOVEMODELSFROMDB_H
#define REMOVEMODELSFROMDB_H

#include "ModelsContext/MCDbSLAs/iremovemodelsfromdb.h"
#include "ModelsContext/MCDbSLAs/imodelsdbcontext.h"

class RemoveModelsFromDb :
        public IRemoveModelsFromDb<IModelsDbContext>
{
public:
    virtual bool remove(const QVector<int> &indexes, IModelsDbContext *dbService) const override
    {
        auto r = true;
        auto startIndex = indexes.count() - 1;
        for (int i = startIndex; i >= 0; --i) {
            auto index = indexes.at(i);
            r = dbService->remove(index) ? r : false;
        }
        return r;
    }
};
#endif // TOURNAMENTMODELCONTEXT_H
