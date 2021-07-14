#ifndef ITOURNAMENTMODELMANIPULATOR_H
#define ITOURNAMENTMODELMANIPULATOR_H

#include <qvector.h>
#include <quuid.h>
#include <qstring.h>

template<typename TTournament, typename TDbService,typename TUuid = QUuid, typename TString = QString>
class ITournamentModelManipulator
{
public:
    virtual void addPlayerIds(const TTournament *tournament, const QVector<TUuid> &playerIds, TDbService *dbService) const = 0;
    virtual void addPlayerNames(const TTournament *tournament, const QVector<TString> &playerNames, TDbService *dbService) const = 0;
    virtual void setWinnerId(const TTournament *tournament, const TUuid &winnerId, TDbService *dbService) const = 0;
};

#endif // ITOURNAMENTMODELMANIPULATOR_H
