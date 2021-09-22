#ifndef IREMOVEFROMDB_H
#define IREMOVEFROMDB_H

#include <qvector.h>

template <typename TModelInterface,typename TDbServiceInterface, typename TUuid>
class IRemoveFromDb
{
public:
    virtual void remove(const TUuid& id,TDbServiceInterface* dbService) const = 0;
    virtual void remove(const QVector<const TModelInterface*> &models,
                        const TUuid& tournamentId,TDbServiceInterface* dbService) const = 0;
    virtual void remove(const QVector<const TModelInterface*> &models,const int& hint, TDbServiceInterface* dbService) const = 0;
};

#endif // IDBSERVICEMANIPULATOR_H
