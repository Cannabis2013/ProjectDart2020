#ifndef POINTINDEXCONTROLLER_H
#define POINTINDEXCONTROLLER_H

#include "indexcontrollerinterface.h"
#include <qlist.h>

class PointIndexController : public IndexControllerInterface
{
    // IndexControllerInterface interface
public:
    static PointIndexController* createInstance(const int &legCount,
                                                const int &playerCount,
                                                const QList<int> &indexes)
    {
        return new PointIndexController(legCount,playerCount,indexes);
    }

    virtual void reset() override
    {
        _totalIndex = 0;
        _index = 0;
        _roundIndex = 1;
        _setIndex = 0;
        _legIndex = 0;
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
        _index--;
        if(_legIndex > 0)
            _legIndex--;
        else
        {
            _legIndex = 2;

            if(_setIndex == 0)
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
        if(++_legIndex >= _legCount)
        {
            _legIndex = 0;
            if(_setIndex == lastPlayerIndex())
            {
                _setIndex = 0;
                _roundIndex++;
            }
            else
                _setIndex++;
        }
        _index++;
    }
    virtual bool canUndo() override
    {
        return _index > 0;
    }
    virtual bool canRedo() override
    {
        return _index < _totalIndex;
    }
    virtual void syncIndex() override
    {
        _totalIndex = _index;
    }
    virtual int index() override
    {
        return _index;
    }
    virtual int totalIndex() override
    {
        return _totalIndex;
    }
    virtual int roundIndex() override
    {
        return _roundIndex;
    }
    virtual int setIndex() override
    {
        return _setIndex;
    }
    virtual int legIndex() override
    {
        return _legIndex;
    }
private:
    PointIndexController(const int &legCount,
                         const int &playerCount,
                         const QList<int> &indexes) :
    _legCount(legCount),_playerCount(playerCount)
    {
        _totalIndex = indexes.at(0);
        _index = indexes.at(1);
        _roundIndex = indexes.at(2);
        _setIndex = indexes.at(3);
        _legIndex = indexes.at(4);
    }

    int playerCount()
    {
        return _playerCount;
    }
    void incrementTurnIndex()
    {
        if(_index == _totalIndex)
            _totalIndex++;
        _index++;
    }

    int checkForEndOfLeg()
    {
        auto result = _index % _legCount == 0;
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
        _legIndex++;
    }
    void resetSetIndex()
    {
        _setIndex = 0;
    }
    void resetLegIndex()
    {
        _legIndex = 0;
    }

    int lastPlayerIndex()
    {
        return _playerCount -1;
    }

    int _index = 0, _totalIndex  = 0, _roundIndex = 1, _setIndex = 0, _legIndex = 0;
    const int _legCount, _playerCount;
};



#endif // POINTINDEXCONTROLLER_H
