#ifndef IGETSCOREINPUTFROMDB_H
#define IGETSCOREINPUTFROMDB_H

template<typename TModel, typename TUuid, typename TDbService>
class IGetScoreInputFromDb
{
public:
    virtual const TModel *get(const TUuid &tournamentId,
                                         const TUuid &playerId,
                                         const int &roundIndex,
                                         const TDbService *dbService) const = 0;

};

#endif // IGETDARTSSCOREFROMDB_H
