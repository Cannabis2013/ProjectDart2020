#ifndef DARTSINDEXES_H
#define DARTSINDEXES_H

#include "DartsModelsContext/IndexesDbSLAs/idartsindexes.h"

class DartsIndexes : public IDartsIndexes
{
public:
    int totalTurns() const override
    {
        return _totalTurns;
    }
    void setTotalTurns(const int& val) override
    {
        _totalTurns = val;
    }
    int turnIndex() const override
    {
        return _turnIndex;
    }
    void setTurnIndex(const int& val) override
    {
        _turnIndex = val;
    }
    int roundIndex() const override
    {
        return _roundIndex;
    }
    void setRoundIndex(const int& val) override
    {
        _roundIndex = val;
    }
    int setIndex() const override
    {
        return _setIndex;
    }
    void setSetIndex(const int& val) override
    {
        _setIndex = val;
    }
    int attemptIndex() const override
    {
        return _attemptIndex;
    }
    void setAttemptIndex(const int& val) override
    {
        _attemptIndex = val;
    }
    virtual QUuid id() const override
    {
        return _id;
    }
    virtual DartsIndexes *setId(const QUuid &id) override
    {
        _id = id;
        return this;
    }
    virtual QUuid tournamentId() const override
    {
        return _tournamentId;
    }
    virtual void setTournamentId(const QUuid &id) override
    {
        _tournamentId = id;
    }
private:
    QUuid _id;
    QUuid _tournamentId;
    int _totalTurns = 0;
    int _turnIndex = 0;
    int _roundIndex = 0;
    int _setIndex = 0;
    int _attemptIndex = 0;
};
#endif // DARTSINDEXES_H
