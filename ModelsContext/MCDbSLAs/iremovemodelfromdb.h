#ifndef IREMOVEMODELFROMDB_H
#define IREMOVEMODELFROMDB_H

#include <qvector.h>

template <typename TModelInterface,typename TDbServiceInterface, typename TUuid>
class IRemoveModelFromDb
{
public:
    virtual void remove(const TUuid& id,TDbServiceInterface* dbService) const = 0;
    virtual void remove(const QVector<const TModelInterface*> &models,
                        const TUuid& tournamentId,TDbServiceInterface* dbService) const = 0;
    virtual void remove(const QVector<const TModelInterface*> &models,const int& hint, TDbServiceInterface* dbService) const = 0;
};

#endif // IDBSERVICEMANIPULATOR_H
