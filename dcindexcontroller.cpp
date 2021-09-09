#include "dcindexcontroller.h"

void DCIndexController::syncIndex()
{
    _totalIndex = _turnIndex;
}

DCIndexController::DCIndexController(const DCBuilding::IDCMetaInfo *meta)
{
    _numberOfAttempts = meta->attempts();
}

int DCIndexController::turnIndex() const
{
    return _turnIndex;
}

void DCIndexController::setTurnIndex(const int &index)
{
    _turnIndex = index;
}

int DCIndexController::totalIndex() const
{
    return _totalIndex;
}

void DCIndexController::setTotalIndex(const int &index)
{
    _totalIndex = index;
}

int DCIndexController::roundIndex() const
{
    return _roundIndex;
}

int DCIndexController::setIndex() const
{
    return _setIndex;
}

int DCIndexController::attemptIndex() const
{
    return _attemptIndex;
}

void DCIndexController::setAttemptIndex(const int &index)
{
    _attemptIndex = index;
}

void DCIndexController::setRoundIndex(const int &index)
{
    _roundIndex = index;
}

void DCIndexController::setSetIndex(const int &index)
{
    _setIndex = index;
}

int DCIndexController::numberOfAttempts() const
{
    return _numberOfAttempts;
}

void DCIndexController::setNumberOfAttempts(const int &value)
{
    _numberOfAttempts = value;
}
