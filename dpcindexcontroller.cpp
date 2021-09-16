#include "dpcindexcontroller.h"

DPCIndexController::DPCIndexController(const DCBuilding::IDCMetaInfo *meta)
{
    _numberOfAttempts = meta->attempts();
}

void DPCIndexController::syncIndex()
{
    _totalIndex = _turnIndex;
}

int DPCIndexController::turnIndex() const
{
    return _turnIndex;
}

void DPCIndexController::setTurnIndex(const int &index)
{
    _turnIndex = index;
}

int DPCIndexController::totalIndex() const
{
    return _totalIndex;
}

void DPCIndexController::setTotalIndex(const int &index)
{
    _totalIndex = index;
}

int DPCIndexController::roundIndex() const
{
    return _roundIndex;
}

int DPCIndexController::setIndex() const
{
    return _setIndex;
}

int DPCIndexController::attemptIndex() const
{
    return _attemptIndex;
}

void DPCIndexController::setAttemptIndex(const int &index)
{
    _attemptIndex = index;
}

void DPCIndexController::setRoundIndex(const int &index)
{
    _roundIndex = index;
}

void DPCIndexController::setSetIndex(const int &index)
{
    _setIndex = index;
}

int DPCIndexController::numberOfAttempts() const
{
    return _numberOfAttempts;
}
