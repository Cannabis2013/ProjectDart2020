#ifndef IDBSERVICEMANIPULATOR_H
#define IDBSERVICEMANIPULATOR_H

#include <qvector.h>

template <typename TModelInterface,typename TDbServiceInterface, typename TUuid>
class IPlayerInputsDbManipulatorService
{
public:
    typedef TModelInterface ModelInterface ;
    typedef QVector<const ModelInterface*> ModelInterfaces;
    typedef TDbServiceInterface DbServiceInterface;
    typedef TUuid IdFormat;

    virtual void removeModelById(const IdFormat& id, DbServiceInterface* dbService) const = 0;
    virtual void removeModelsByTournamentId(const ModelInterfaces& models,
                                            const IdFormat& tournamentId,
                                            DbServiceInterface* dbService) const = 0;
    virtual void removeModelsByHint(const ModelInterfaces& models,
                                    const int& hint,
                                    DbServiceInterface* dbService) const = 0;
};

#endif // IDBSERVICEMANIPULATOR_H
