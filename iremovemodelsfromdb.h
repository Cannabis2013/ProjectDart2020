#ifndef IREMOVEMODELSFROMDB_H
#define IREMOVEMODELSFROMDB_H

#include <qvector.h>

template<typename TDbService>
class IRemoveModelsFromDb
{
public:
    virtual bool remove(const QVector<int>& indexes, TDbService *dbService) const = 0;
};

#endif // ITOURNAMENTDBSERVICE_H
