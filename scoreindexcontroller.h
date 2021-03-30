#ifndef SCOREINDEXCONTROLLER_H
#define SCOREINDEXCONTROLLER_H

#include <qvector.h>
#include "indexcontrollerinterface.h"

class ScoreIndexController : public IndexControllerInterface
{
public:
    // Create instance
    static ScoreIndexController* createInstance();
    // IndexControllerInterface interface
    virtual void setIndexes(const int &totalTurns,
                            const int & turnIndex,
                            const int &roundIndex,
                            const int &setIndex,
                            const int &attemptIndex) override
    {
        _totalIndex = totalTurns;
        _turnIndex = turnIndex;
        _roundIndex = roundIndex;
        _setIndex = setIndex;
        _attemptIndex = attemptIndex;
    }
    virtual void reset() override;
    virtual void next() override;
    virtual void undo() override;
    virtual void redo() override;
    virtual bool canUndo() override;
    virtual bool canRedo() override;
    virtual void syncIndex() override;
    virtual int turnIndex() override;
    virtual void setTurnIndex(const int &index) override
    {
        _turnIndex = index;
    }
    virtual int totalIndex() override;
    virtual void setTotalIndex(const int &index) override
    {
        _totalIndex = index;
    }
    virtual int roundIndex() override;
    virtual int setIndex() override;
    virtual int attempt() override;


    void setPlayersCount(const int& playerCount) override;
    int playersCount() override;

    virtual void setRoundIndex(const int &index) override;
    virtual void setSetIndex(const int &index) override;

    virtual void setAttempt(const int &) override;
    virtual int numberOfAttempts() override;
    virtual void setNumberOfAttempts(const int &) override;
private:
    // Private methods
    void incrementTurnIndex();
    void incrementRoundIndex();
    void incrementSetIndex();
    void resetSetIndex();
    void resetLegIndex();
    int lastPlayerIndex();

    int _turnIndex = 0, _totalIndex  = 0, _roundIndex = 1, _setIndex = 0, _attemptIndex = 0;
    int _attempt = 0, _playerCount;
};

#endif // SCOREINDEXCONTROLLER_H
