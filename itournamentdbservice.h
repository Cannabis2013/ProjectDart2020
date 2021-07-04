#ifndef ITOURNAMENTDBSERVICE_H
#define ITOURNAMENTDBSERVICE_H

#include <qvector.h>

template<typename TTournamentInterface, typename TTournamentDb,typename TUuid, typename TString>
class ITournamentDbService
{
public:
    typedef TTournamentInterface Tournament;
    typedef TTournamentDb DbService;
    typedef TUuid Id;
    typedef TString String;
    virtual Id addDartsTournamentToDb(const Tournament* tournament, DbService *dbService) = 0;
    virtual bool removeTournamentsByIndexes(const QVector<int>& indexes, DbService *dbService) const = 0;
};

#endif // ITOURNAMENTDBSERVICE_H
