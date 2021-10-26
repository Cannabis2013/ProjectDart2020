#ifndef DPCINDEXCONTROLLER_H
#define DPCINDEXCONTROLLER_H
#include "DartsController/DCIndexSLAs/idcindexcontroller.h"
class DPCIndexController : public IDCIndexController
{
public:
    virtual void initialize(const DCIndex &index) override
    {
        _index = index;
    }
    DCIndex &index() override
    {
        return _index;
    }
    DCIndex &next(const int &playersCount) override
    {
        if(_index.turnIndex == _index.totalTurns)
            _index.totalTurns++;
        _index.turnIndex++;
        _index.attemptIndex++;
        if(_index.attemptIndex >= _attempts)
        {
            _index.setIndex++;
            _index.attemptIndex = 0;
        }
        if(_index.setIndex >= playersCount){
            _index.roundIndex++;
            _index.setIndex = 0;
        }
        return _index;
    }
    virtual DCIndex &undo(const int &playerCount) override
    {
        if(_index.turnIndex <= 0)
            throw "ERROR: CAN'T UNDO!";
        _index.turnIndex--;
        _index.attemptIndex--;
        if(_index.attemptIndex < 0)
        {
            _index.setIndex--;
            _index.attemptIndex = _attempts - 1;
        }
        if(_index.setIndex < 0)
        {
            _index.roundIndex--;
            _index.setIndex = playerCount - 1;
        }
        return _index;
    }
    virtual DCIndex &redo(const int &playersCount) override
    {
        if(_index.turnIndex >= _index.totalTurns)
            throw "ERROR: CAN'T REDO!";
        _index.turnIndex++;
        _index.attemptIndex++;
        if(_index.attemptIndex >= _attempts)
        {
            _index.setIndex++;
            _index.attemptIndex = 0;
        }
        if(_index.setIndex >= playersCount){
            _index.roundIndex++;
            _index.setIndex = 0;
        }
        return _index;
    }
private:
    DCIndex _index;
    const int _attempts = 3;
};
#endif // DPCINDEXCONTROLLER_H
