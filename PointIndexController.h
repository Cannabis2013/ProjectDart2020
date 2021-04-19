#ifndef POINTINDEXCONTROLLER_H
#define POINTINDEXCONTROLLER_H

#include "indexcontrollerinterface.h"
#include <qlist.h>

class PointIndexController : public IndexControllerInterface
{
    // IndexControllerInterface interface
public:
    static PointIndexController* createInstance(const int &attemptCount)
    {
        return new PointIndexController(attemptCount);
    }

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

    virtual void reset() override
    {
        _totalIndex = 0;
        _turnIndex = 0;
        _roundIndex = 1;
        _setIndex = 0;
        _attemptIndex = 0;
    }

    virtual void next() override
    {
        incrementTurnIndex();
        if(checkForEndOfLeg())
        {
            incrementSetIndex();
            resetLegIndex();
            if(setIndex() >= playerCount()){
                incrementRoundIndex();
                resetSetIndex();
            }
        }
        else
        {
            incrementLegIndex();
        }
    }
    virtual void undo() override
    {
        _turnIndex--;
        if(attempt() > 0)
           _attemptIndex--;
        else
        {
            _attemptIndex = 2;

            if(setIndex() == 0)
            {
                _setIndex = lastPlayerIndex();
                _roundIndex--;
            }
            else
            {
                _setIndex--;
            }
        }
    }
    virtual void redo() override
    {
        if(++_attemptIndex >= _numberOfAttempts)
        {
            _attemptIndex = 0;
            if(_setIndex == lastPlayerIndex())
            {
                _setIndex = 0;
                _roundIndex++;
            }
            else
                _setIndex++;
        }
        _turnIndex++;
    }
    virtual bool canUndo() override
    {
        return turnIndex() > 0;
    }
    virtual bool canRedo() override
    {
        return turnIndex() < _totalIndex;
    }
    virtual void syncIndex() override
    {
        _totalIndex = _turnIndex;
    }
    virtual int turnIndex() override
    {
        return _turnIndex;
    }
    virtual void setTurnIndex(const int &index) override
    {
        _turnIndex = index;
    }
    virtual int totalIndex() override
    {
        return _totalIndex;
    }
    virtual void setTotalIndex(const int &index) override
    {
        _totalIndex = index;
    }
    virtual int roundIndex() override
    {
        return _roundIndex;
    }
    void setRoundIndex(const int& roundIndex) override
    {
        _roundIndex = roundIndex;
    }
    virtual int setIndex() override
    {
        return _setIndex;
    }
    void setSetIndex(const int& setIndex) override
    {
        _setIndex = setIndex;
    }
    virtual int attempt() override
    {
        return _attemptIndex;
    }

    virtual void setAttempt(const int &index) override
    {
        _attemptIndex = index;
    }
    int numberOfAttempts() override
    {
        return _numberOfAttempts;
    }
    void setNumberOfAttempts(const int& numberOfAttempts) override
    {
        _numberOfAttempts = numberOfAttempts;
    }
    virtual int playersCount() override
    {
        return _playersCount;
    }
    virtual void setPlayersCount(const int &count) override
    {
        _playersCount = count;
    }
private:
    PointIndexController(const int &attempts) :
        _numberOfAttempts(attempts)
    {}
    int playerCount()
    {
        return _playersCount;
    }
    void incrementTurnIndex()
    {
        if(_turnIndex == _totalIndex)
            _totalIndex++;
        _turnIndex++;
    }

    int checkForEndOfLeg()
    {
        auto result = _turnIndex % _numberOfAttempts == 0;
        return result;
    }
    void incrementRoundIndex()
    {
        _roundIndex++;
    }
    void incrementSetIndex()
    {
        _setIndex++;
    }
    void incrementLegIndex()
    {
        _attemptIndex++;
    }
    void resetSetIndex()
    {
        _setIndex = 0;
    }
    void resetLegIndex()
    {
        _attemptIndex = 0;
    }

    int lastPlayerIndex()
    {
        return playerCount() -1;
    }

    int _turnIndex = 0, _totalIndex  = 0, _roundIndex = 1, _setIndex = 0, _attemptIndex = 0;
    int _numberOfAttempts, _playersCount;
};
#endif // POINTINDEXCONTROLLER_H
