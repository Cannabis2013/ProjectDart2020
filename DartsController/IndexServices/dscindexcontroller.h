#ifndef DSCINDEXCONTROLLER_H
#define DSCINDEXCONTROLLER_H
#include "DartsController/DCIndexSLAs/abstractdcidxctrl.h"
class DSCIndexController : public AbstractDCIdxCtrl
{
public:
    DSCIndexController(IDCIdxBuilder *copyContext)
    {
        setCopyContext(copyContext);
    }
    virtual void init(IDartsIndex *index) override
    {
        _index = copyContext()->index(index);
    }
    IDartsIndex *index() const override
    {
        return copyContext()->index(_index);
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
        return copyContext()->index(_index);
    }
    virtual IDartsIndex *undo() override
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
    virtual IDartsIndex *redo() override
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
        return copyContext()->index(_index);
    }
private:
    IDartsIndex *_index;
    const int _attempts = 1;
};
#endif // DSCINDEXCONTROLLER_H
