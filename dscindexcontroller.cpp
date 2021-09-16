#include "dscindexcontroller.h"

void DSCIndexController::syncIndex()
{
    _totalIndex = _turnIndex;
}

int DSCIndexController::turnIndex() const
{
    return _turnIndex;
}

void DSCIndexController::setTurnIndex(const int &index)
{
    _turnIndex = index;
}

int DSCIndexController::totalIndex() const
{
    return _totalIndex;
}

void DSCIndexController::setTotalIndex(const int &index)
{
    _totalIndex = index;
}

int DSCIndexController::roundIndex() const
{
    return _roundIndex;
}

int DSCIndexController::setIndex() const
{
    return _setIndex;
}

int DSCIndexController::attemptIndex() const
{
    return _attemptIndex;
}

void DSCIndexController::setAttemptIndex(const int &index)
{
    _attemptIndex = index;
}

void DSCIndexController::setRoundIndex(const int &index)
{
    _roundIndex = index;
}

void DSCIndexController::setSetIndex(const int &index)
{
    _setIndex = index;
}

int DSCIndexController::numberOfAttempts() const
{
    return _numberOfAttempts;
}
