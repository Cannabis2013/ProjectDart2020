#include "dcindexcontroller.h"

void DCIndexController::reset()
{
    _totalIndex = 0;
    _turnIndex = 0;
    _roundIndex = 1;
    _setIndex = 0;
    _attemptIndex = 0;
}

void DCIndexController::next()
{
    incrementTurnIndex();
    incrementSetIndex();
    if(setIndex() >= playersCount()){
        incrementRoundIndex();
        resetSetIndex();
    }
}

void DCIndexController::undo()
{
    if(!canUndo())
        return;
    _turnIndex--;
    if(_setIndex == 0)
    {
        _setIndex = lastPlayerIndex();
        _roundIndex--;
    }
    else
    {
        _setIndex--;
    }
}

void DCIndexController::redo()
{
    if(_setIndex == lastPlayerIndex())
    {
        _setIndex = 0;
        _roundIndex++;
    }
    else
        _setIndex++;
    _turnIndex++;
}

bool DCIndexController::canUndo() const
{
    return turnIndex() > 0;
}

bool DCIndexController::canRedo() const
{
    return turnIndex() < _totalIndex;
}

void DCIndexController::syncIndex()
{
    _totalIndex = _turnIndex;
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

void DCIndexController::incrementTurnIndex()
{
    if(_turnIndex == _totalIndex)
        _totalIndex++;
    _turnIndex++;
}

void DCIndexController::incrementRoundIndex()
{
    _roundIndex++;
}

void DCIndexController::incrementSetIndex()
{
    _setIndex++;
}

void DCIndexController::resetSetIndex()
{
    _setIndex = 0;
}

void DCIndexController::resetLegIndex()
{
    _attemptIndex = 0;
}

int DCIndexController::playersCount() const
{
    return _playerCount;
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
    return 1;
}

void DCIndexController::setNumberOfAttempts(const int &)
{
}

int DCIndexController::lastPlayerIndex()
{
    return playersCount() -1;
}

void DCIndexController::setPlayersCount(const int &playerCount)
{
    _playerCount = playerCount;
}
