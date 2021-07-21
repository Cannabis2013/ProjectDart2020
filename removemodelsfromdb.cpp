#include "removemodelsfromdb.h"

using namespace ModelsContext;

bool ModelsContext::RemoveModelsFromDb::remove(const QVector<int> &indexes, IDbService *dbService) const
{
    auto r = true;
    auto startIndex = indexes.count() - 1;
    for (int i = startIndex; i >= 0; --i) {
        auto index = indexes.at(i);
        r = dbService->remove(index) ? r : false;
    }
    return r;
}
