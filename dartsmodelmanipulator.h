#ifndef DARTSMODELMANIPULATOR_H
#define DARTSMODELMANIPULATOR_H

#include "idartsmodelmanipulator.h"

class DartsModelManipulator : public IDartsModelManipulator
{
public:
    virtual void addPlayerIds(const Tournament *tournament,
                              const QVector<Id> &playerIds) const override
    {
        auto nonConstTournament = const_cast<Tournament*>(tournament);
        nonConstTournament->setAssignedPlayerIdentities(playerIds);
    }
    virtual void addPlayerNames(const Tournament *tournament,
                                const QVector<String> &playerNames) const override
    {
        auto nonConstTournament = const_cast<Tournament*>(tournament);
        nonConstTournament->setAssignedPlayerNames(playerNames);
    }
    virtual void setWinnerId(const Tournament *tournament, const Id &winnerId) const override
    {
        auto nonConstModel = const_cast<Tournament*>(tournament);
        nonConstModel->setWinnerId(winnerId);
    }
};

#endif // DARTSMODELMANIPULATOR_H
