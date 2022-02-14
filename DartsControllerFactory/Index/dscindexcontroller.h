#ifndef DSCINDEXCONTROLLER_H
#define DSCINDEXCONTROLLER_H
#include "Index/idcindexcontroller.h"
#include "Models/dcmeta.h"
#include "Models/dcindex.h"
class DSCIndexController : public IDCIndexController<DCIndex,DCMeta>
{
public:
    virtual void init(const DCMeta &meta) override
    {
        _pCount = meta.playersCount,
        _idx = meta.index;
    }
    DCIndex index() const override {return _idx;}
    virtual DCIndex prevIndex() const override
    {
        auto reqIdx = _idx;
        reqIdx.roundIndex--;
        return reqIdx;
    }
    void next() override
    {
        if(_idx.turnIndex == _idx.totalTurns)
            _idx.totalTurns++;
        _idx.turnIndex++;
        _idx.attemptIndex++;
        if(_idx.attemptIndex >= _attempts)
        {
            _idx.playerIndex++;
            _idx.attemptIndex = 0;
        }
        if(_idx.playerIndex >= pCount()){
            _idx.roundIndex++;
            _idx.playerIndex = 0;
        }
    }
    virtual DCIndex undo() override
    {
        if(_idx.turnIndex <= 0)
            throw "ERROR: CAN'T UNDO!";
        _idx.turnIndex--;
        _idx.attemptIndex--;
        if(_idx.attemptIndex < 0)
        {
            _idx.playerIndex--;
            _idx.attemptIndex = _attempts - 1;
        }
        if(_idx.playerIndex < 0)
        {
            _idx.roundIndex--;
            _idx.playerIndex = pCount() - 1;
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
            _idx.playerIndex++;
            _idx.attemptIndex = 0;
        }
        if(_idx.playerIndex >= pCount()){
            _idx.roundIndex++;
            _idx.playerIndex = 0;
        }
        return _idx;
    }
private:
    int pCount() const {return _pCount;}
    DCIndex _idx;
    const int _attempts = 1;
    int _pCount;
};
#endif // DSCINDEXCONTROLLER_H
