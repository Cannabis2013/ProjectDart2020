#ifndef DPCIDXCTRL_H
#define DPCIDXCTRL_H
#include "DartsController/DCIndexSLAs/idcidxctrl.h"
#include <DartsController/DCMetaServices/dcmeta.h>
class DPCIdxCtrl : public IDCIdxCtrl
{
public:
    virtual void init(const DCMeta &meta) override
    {
        _pCount = meta.playersCount;
        _index = meta.index;
    }
    DCIndex index() const override {return _index;}
    virtual DCIndex prevIndex() const override
    {
        auto reqIdx = _index;
        if(reqIdx.attemptIndex > 0)
            reqIdx.attemptIndex--;
        else
        {
            reqIdx.roundIndex--;
            reqIdx.attemptIndex = _attempts - 1;
        }
        return reqIdx;
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
        if(_index.setIndex >= pCount()){
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
            _index.setIndex = pCount() - 1;
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
        if(_index.setIndex >= pCount()){
            _index.roundIndex++;
            _index.setIndex = 0;
        }
        return _index;
    }

private:
    int pCount() const {return _pCount;}
DCIndex _index;
    const int _attempts = 3;
    int _pCount;
};
#endif // DPCINDEXCONTROLLER_H
