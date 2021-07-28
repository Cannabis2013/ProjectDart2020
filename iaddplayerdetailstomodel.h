#ifndef ITOURNAMENTMODELMANIPULATOR_H
#define ITOURNAMENTMODELMANIPULATOR_H

#include <qvector.h>
#include <quuid.h>
#include <qstring.h>

template<typename TTournament, typename TPlayer, typename TDbService,typename TUuid = QUuid, typename TString = QString>
class IAddPlayerDetailsToModel
{
public:
    virtual void add(const TTournament *tournament, const QVector<TUuid> &playerIds, TDbService *dbService) const = 0;
    virtual void add(const TTournament *tournament, const QVector<TString> &playerNames, TDbService *dbService) const = 0;
    virtual void add(const TTournament *tournament, const TUuid &winnerId, const TString &winnerName,
                     TDbService *dbService) const = 0;
    virtual void add(const TTournament *tournament, const QVector<const TPlayer*> &playerModels,
                     TDbService *dbService) const = 0;
};

#endif // ITOURNAMENTMODELMANIPULATOR_H
