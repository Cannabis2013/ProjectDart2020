#include "dpcindexcontroller.h"

void DPCIndexController::init(const DCMeta &meta)
{
        _pCount = meta.playersCount;
        _index = meta.index;
}

DCIndex DPCIndexController::index() const
{
        return _index;
}

DCIndex DPCIndexController::prevIndex() const
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

DCIndex DPCIndexController::next()
{    
        if(_index.turnIndex == _index.totalTurns)
                _index.totalTurns++;
        _index.turnIndex++;
        _index.attemptIndex++;
        if(_index.attemptIndex >= _attempts)
        {
                _index.playerIndex++;
                _index.attemptIndex = 0;
        }
        if(_index.playerIndex >= pCount()){
                _index.roundIndex++;
                _index.playerIndex = 0;
        }
        return _index;
}

DCIndex DPCIndexController::undo()
{
        if(_index.turnIndex <= 0)
                throw "ERROR: CAN'T UNDO!";
        _index.turnIndex--;
        _index.attemptIndex--;
        if(_index.attemptIndex < 0)
        {
                _index.playerIndex--;
                _index.attemptIndex = _attempts - 1;
        }
        if(_index.playerIndex < 0)
        {
                _index.roundIndex--;
                _index.playerIndex = pCount() - 1;
        }
        return _index;
}

DCIndex DPCIndexController::redo()
{    
        if(_index.turnIndex >= _index.totalTurns)
                throw "ERROR: CAN'T REDO!";
        _index.turnIndex++;
        _index.attemptIndex++;
        if(_index.attemptIndex >= _attempts)
        {
                _index.playerIndex++;
                _index.attemptIndex = 0;
        }
        if(_index.playerIndex >= pCount()){
                _index.roundIndex++;
                _index.playerIndex = 0;
        }
        return _index;
}

int DPCIndexController::pCount() const
{
        return _pCount;
}
