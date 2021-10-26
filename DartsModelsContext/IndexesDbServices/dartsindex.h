#ifndef DARTSINDEX_H
#define DARTSINDEX_H

#include "DartsModelsContext/IndexesDbSLAs/idartsindex.h"

class DartsIndex : public IDartsIndex
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
private:
    int _totalTurns = 0;
    int _turnIndex = 0;
    int _roundIndex = 0;
    int _setIndex = 0;
    int _attemptIndex = 0;
};
#endif // DARTSINDEX_H
