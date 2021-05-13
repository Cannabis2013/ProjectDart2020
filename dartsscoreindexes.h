#ifndef DARTSSCOREINDEXES_H
#define DARTSSCOREINDEXES_H

#include "idartsscoreindexes.h"

class DartsScoreIndexes : public IDartsScoreIndexes
{
public:
    static DartsScoreIndexes* createInstance()
    {
        return new DartsScoreIndexes;
    }
    static const DartsScoreIndexes* createInitialInstance()
    {
        auto indexes = DartsScoreIndexes::createInstance();
        indexes->setTotalTurns(0);
        indexes->setTurnIndex(0);
        indexes->setRoundIndex(1);
        indexes->setSetIndex(0);
        return indexes;
    }
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
private:
    int _totalTurns;
    int _turnIndex;
    int _roundIndex;
    int _setIndex;
};

#endif // DARTSSCOREINDEXES_H
