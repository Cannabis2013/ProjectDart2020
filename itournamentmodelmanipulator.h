#ifndef ITOURNAMENTMODELMANIPULATOR_H
#define ITOURNAMENTMODELMANIPULATOR_H

#include <qvector.h>

template<typename TTournament, typename TUuid, typename TString>
class ITournamentModelManipulator
{
public:
    typedef TTournament Tournament;
    typedef TUuid Id;
    typedef TString String;
    virtual void addPlayerIds(const Tournament *tournament, const QVector<Id> &playerIds) const = 0;
    virtual void addPlayerNames(const Tournament *tournament, const QVector<String> &playerNames) const = 0;
    virtual void setWinnerId(const Tournament *tournament, const Id &winnerId) const = 0;
};

#endif // ITOURNAMENTMODELMANIPULATOR_H
