#ifndef DSCINDEXCONTROLLER_H
#define DSCINDEXCONTROLLER_H
#include "DartsController/DCIndexSLAs/absdcidxctrl.h"
class DSCIndexController : public AbsDCIdxCtrl
{
public:
    virtual void init(const DCIndex &idx) override {_idx = idx;}
    DCIndex index() const override {return _idx;}
    DCIndex next() override
    {
        if(_idx.turnIndex == _idx.totalTurns)
            _idx.totalTurns++;
        _idx.turnIndex++;
        _idx.attemptIndex++;
        if(_idx.attemptIndex >= _attempts)
        {
            _idx.setIndex++;
            _idx.attemptIndex = 0;
        }
        if(_idx.setIndex >= playersCount()){
            _idx.roundIndex++;
            _idx.setIndex = 0;
        }
        return _idx;
    }
    virtual DCIndex undo() override
    {
        if(_idx.turnIndex <= 0)
            throw "ERROR: CAN'T UNDO!";
        _idx.turnIndex--;
        _idx.attemptIndex--;
        if(_idx.attemptIndex < 0)
        {
            _idx.setIndex--;
            _idx.attemptIndex = _attempts - 1;
        }
        if(_idx.setIndex < 0)
        {
            _idx.roundIndex--;
            _idx.setIndex = playersCount() - 1;
        }
        return _idx;
    }
    virtual DCIndex redo() override
    {
        if(_idx.turnIndex >= _idx.totalTurns)
            throw "ERROR: CAN'T REDO!";
        _idx.turnIndex++;
        _idx.attemptIndex++;
        if(_idx.attemptIndex >= _attempts)
        {
            _idx.setIndex++;
            _idx.attemptIndex = 0;
        }
        if(_idx.setIndex >= playersCount()){
            _idx.roundIndex++;
            _idx.setIndex = 0;
        }
        return _idx;
    }
private:
    DCIndex _idx;
    const int _attempts = 1;
};
#endif // DSCINDEXCONTROLLER_H
