#ifndef DPCIDXCTRL_H
#define DPCIDXCTRL_H
#include "DartsController/DCIndexSLAs/absdcidxctrl.h"
class DPCIdxCtrl : public AbsDCIdxCtrl
{
public:
    virtual void init(const DCIndex &index) override
    {
        _index = index;
    }
    DCIndex index() const override
    {
        return _index;
    }
    DCIndex next() override
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
        if(_index.setIndex >= playersCount()){
            _index.roundIndex++;
            _index.setIndex = 0;
        }
        return _index;
    }
    DCIndex undo() override
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
            _index.setIndex = playersCount() - 1;
        }
        return _index;
    }
    DCIndex redo() override
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
        if(_index.setIndex >= playersCount()){
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
