#ifndef IGETTOURNAMENTFROMDB_H
#define IGETTOURNAMENTFROMDB_H


template<typename TTournament,typename TUuid, typename TDbService>
class IGetTournamentFromDb
{
public:
    typedef TTournament Tournament ;
    typedef TDbService DbService;
    typedef TUuid Id;
    virtual const Tournament *tournament(const Id &tournamentId, const DbService *dbService) const = 0;
};
#endif // IGETDARTSTOURNAMENTDATA_H
