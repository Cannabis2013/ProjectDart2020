#include "scoreindexcontroller.h"

ScoreIndexController *ScoreIndexController::createInstance(const int &playerCount, const QVector<int> &indexes)
{
    return new ScoreIndexController(playerCount,indexes);
}

void ScoreIndexController::reset()
{
    _totalIndex = 0;
    _index = 0;
    _roundIndex = 1;
    _setIndex = 0;
    _legIndex = 0;
}

void ScoreIndexController::next()
{
    incrementTurnIndex();
    incrementSetIndex();
    if(setIndex() >= playerCount()){
        incrementRoundIndex();
        resetSetIndex();
    }
}

void ScoreIndexController::undo()
{
    if(!canUndo())
        return;
    _index--;
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
    _index++;
}

bool ScoreIndexController::canUndo()
{
    return index() > 0;
}

bool ScoreIndexController::canRedo()
{
    return index() < _totalIndex;
}

void ScoreIndexController::syncIndex()
{
    _totalIndex = _index;
}

int ScoreIndexController::index()
{
    return _index;
}

int ScoreIndexController::totalIndex()
{
    return _totalIndex;
}

int ScoreIndexController::roundIndex()
{
    return _roundIndex;
}

int ScoreIndexController::setIndex()
{
    return _setIndex;
}

int ScoreIndexController::attempt()
{
    return _attempt;
}

void ScoreIndexController::incrementTurnIndex()
{
    if(_index == _totalIndex)
        _totalIndex++;
    _index++;
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
    _legIndex = 0;
}

int ScoreIndexController::playerCount()
{
    return _playerCount;
}

int ScoreIndexController::lastPlayerIndex()
{
    return playerCount() -1;
}

ScoreIndexController::ScoreIndexController(const int &playerCount,
                                           const QVector<int> &indexes):
    _playerCount(playerCount)
{
    _totalIndex = indexes.at(0);
    _index = indexes.at(1);
    _roundIndex = indexes.at(2);
    _setIndex = indexes.at(3);
    _legIndex = indexes.at(4);
}
