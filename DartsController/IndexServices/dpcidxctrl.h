#ifndef DPCIDXCTRL_H
#define DPCIDXCTRL_H
#include "DartsController/DCIndexSLAs/abstractdcindexctrl.h"
class DPCIndexController : public AbstractDCIndexCtrl
{
public:
    DPCIndexController(IDCIndexBuilder *copyContext)
    {
        setCopyContext(copyContext);
    }
    virtual void init(IDartsIndex *index) override
    {
        _index = copyContext()->index(index);
    }
    IDartsIndex *index() const override
    {
        return copyContext()->index(_index);;
    }
    IDartsIndex *next() override
    {
        if(_index->turnIndex() == _index->totalTurns())
            _index->setTotalTurns(_index->totalTurns() + 1);
        _index->setTurnIndex(_index->turnIndex() + 1);
        _index->setAttemptIndex(_index->attemptIndex() + 1);
        if(_index->attemptIndex() >= _attempts)
        {
            _index->setSetIndex(_index->setIndex() + 1);
            _index->setAttemptIndex(0);
        }
        if(_index->setIndex() >= playersCount()){
            _index->setRoundIndex(_index->roundIndex() + 1);
            _index->setSetIndex(0);
        }
        return _index;
    }
    IDartsIndex *undo() override
    {
        if(_index->turnIndex() <= 0)
            throw "ERROR: CAN'T UNDO!";
        _index->setTurnIndex(_index->turnIndex() - 1);
        _index->setAttemptIndex(_index->attemptIndex() - 1);
        if(_index->attemptIndex() < 0)
        {
            _index->setSetIndex(_index->setIndex() - 1);
            _index->setAttemptIndex(_attempts - 1);
        }
        if(_index->setIndex() < 0)
        {
            _index->setRoundIndex(_index->roundIndex() - 1);
            _index->setSetIndex(playersCount() - 1);
        }
        return _index;
    }
    IDartsIndex *redo() override
    {
        if(_index->turnIndex() >= _index->totalTurns())
            throw "ERROR: CAN'T REDO!";
        _index->setTurnIndex(_index->turnIndex() + 1);
        _index->setAttemptIndex(_index->attemptIndex() + 1);
        if(_index->attemptIndex() >= _attempts)
        {
            _index->setSetIndex(_index->setIndex() + 1);
            _index->setAttemptIndex(0);
        }
        if(_index->setIndex() >= playersCount()){
            _index->setRoundIndex(_index->roundIndex() + 1);
            _index->setSetIndex(0);
        }
        return _index;
    }
private:
    IDartsIndex *_index;
    const int _attempts = 3;
};
#endif // DPCIDXCTRL_H
