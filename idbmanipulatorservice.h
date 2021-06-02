#ifndef IDBSERVICEMANIPULATOR_H
#define IDBSERVICEMANIPULATOR_H

template <typename TDbServiceInterface, typename TUuid>
class IDbManipulatorService
{
public:
    typedef TDbServiceInterface DbServiceInterface;
    typedef TUuid IdFormat;
    virtual void removeModelsByHint(const IdFormat& tournamentId, const int& hint,
                                    const DbServiceInterface* dbService) const = 0;
};

#endif // IDBSERVICEMANIPULATOR_H
