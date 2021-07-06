#ifndef IGETPOINTINPUTFROMDB_H
#define IGETPOINTINPUTFROMDB_H

template<typename TModel, typename TUuid, typename TDbService>
class IGetPointInputFromDb
{
public:
    virtual const TModel* get(const TUuid &tournamentId,
                              const TUuid &playerId,
                              const int &roundIndex,
                              const int &attemptIndex,
                              const TDbService* dbService) const = 0;
};

#endif // IGETDARTSPOINTMODELFROMDB_H
