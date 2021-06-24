#include "scoreindexcontroller.h"

using namespace DartsScoreControllerContext;

ScoreIndexController *ScoreIndexController::createInstance()
{
    return new ScoreIndexController();
}

void ScoreIndexController::setIndexes(const IDartsScoreControllerIndexes<QByteArray> *indexes)
{
    _totalIndex = indexes->totalTurns();
    _turnIndex = indexes->turnIndex();
    _roundIndex = indexes->roundIndex();
    _setIndex = indexes->setIndex();
}

void ScoreIndexController::reset()
{
    _totalIndex = 0;
    _turnIndex = 0;
    _roundIndex = 1;
    _setIndex = 0;
    _attemptIndex = 0;
}

void ScoreIndexController::next()
{
    incrementTurnIndex();
    incrementSetIndex();
    if(setIndex() >= playersCount()){
        incrementRoundIndex();
        resetSetIndex();
    }
}

void ScoreIndexController::undo()
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

void ScoreIndexController::redo()
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

bool ScoreIndexController::canUndo() const
{
    return turnIndex() > 0;
}

bool ScoreIndexController::canRedo() const
{
    return turnIndex() < _totalIndex;
}

void ScoreIndexController::syncIndex()
{
    _totalIndex = _turnIndex;
}

int ScoreIndexController::turnIndex() const
{
    return _turnIndex;
}

void ScoreIndexController::setTurnIndex(const int &index)
{
    _turnIndex = index;
}

int ScoreIndexController::totalIndex() const
{
    return _totalIndex;
}

void ScoreIndexController::setTotalIndex(const int &index)
{
    _totalIndex = index;
}

int ScoreIndexController::roundIndex() const
{
    return _roundIndex;
}

int ScoreIndexController::setIndex() const
{
    return _setIndex;
}

void ScoreIndexController::incrementTurnIndex()
{
    if(_turnIndex == _totalIndex)
        _totalIndex++;
    _turnIndex++;
}

void ScoreIndexController::incrementRoundIndex()
{
    _roundIndex++;
}

void ScoreIndexController::incrementSetIndex()
{
    _setIndex++;
}

void ScoreIndexController::resetSetIndex()
{
    _setIndex = 0;
}

void ScoreIndexController::resetLegIndex()
{
    _attemptIndex = 0;
}

int ScoreIndexController::playersCount() const
{
    return _playerCount;
}

void ScoreIndexController::setRoundIndex(const int &index)
{
    _roundIndex = index;
}

void ScoreIndexController::setSetIndex(const int &index)
{
    _setIndex = index;
}

int ScoreIndexController::numberOfAttempts() const
{
    return 1;
}

void ScoreIndexController::setNumberOfAttempts(const int &)
{
    Q_UNIMPLEMENTED();
}

int ScoreIndexController::lastPlayerIndex()
{
    return playersCount() -1;
}

void ScoreIndexController::setPlayersCount(const int &playerCount)
{
    _playerCount = playerCount;
}
