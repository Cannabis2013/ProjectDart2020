#ifndef DSCINDEXCONTROLLER_H
#define DSCINDEXCONTROLLER_H
#include "DartsController/DCIndexSLAs/idcindexcontroller.h"
class DSCIndexController : public IDCIndexController
{
public:
    virtual void init(IDartsIndex *index) override
    {
        _index = index;
    }
    IDartsIndex *index() override
    {
        return _index;
    }
    IDartsIndex *next(const int &playersCount) override
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
        if(_index->setIndex() >= playersCount){
            _index->setRoundIndex(_index->roundIndex() + 1);
            _index->setSetIndex(0);
        }
        return _index;
    }
    virtual IDartsIndex *undo(const int &playerCount) override
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
            _index->setSetIndex(playerCount - 1);
        }

        return _index;
    }
    virtual IDartsIndex *redo(const int &playersCount) override
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
        if(_index->setIndex() >= playersCount){
            _index->setRoundIndex(_index->roundIndex() + 1);
            _index->setSetIndex(0);
        }
        return _index;
    }
private:
    IDartsIndex *_index;
    const int _attempts = 1;
};
#endif // DSCINDEXCONTROLLER_H
