#include "dartscontroller.h"
#include "src/DartsController/indexes/dartsindexes.h"
#include "src/DartsController/init/dartInitInfo.h"
#include "src/DartsController/input/dartinputevaluator.h"
#include "src/DartsController/input/dartsinputs.h"
#include "src/DartsController/players/dartplayers.h"
#include "src/DartsController/responses/ErrorInfo.h"
#include "src/DartsController/scores/dartsscores.h"
#include <src/DartsController/responses/dartsinforesponse.h>

DartsController::DartsController() {
    _indexes = new DartsIndexes();
        _players = new DartPlayers();
        _inputs = new DartsInputs(_indexes,_players);
        _scores = new DartsScores(_indexes,_players,_inputs);
        _evaluator = new DartInputEvaluator(_scores);
        _response = new DartsInfoResponse(_scores,_players,_indexes);
}

void DartsController::init(const QStringList& playerNames)
{
        DartInitInfo info(playerNames);
        _players->initPlayers(info.playerNames());
        _indexes->init(info.playersCount());
        _scores->init(info.playersCount());
}

QStringList DartsController::playerNames() const
{
        return _players->names();
}

void DartsController::initFromSaved()
{
        _players->initPlayers();
        _indexes->init();
        _scores->init();
}

QByteArray DartsController::initialValues() const
{
        return _response->initialInfo().toJson();
}

QByteArray DartsController::turnInfo() const
{
        if(_scores->score().playerScore() == 0)
                return _response->winnerInfo().toJson();
        return _response->currentTurnInfo().toJson();
}

QByteArray DartsController::addInput(const QByteArray &inputAsJson)
{
        auto input = DartsInput::fromJson(inputAsJson);
        if(!_evaluator->isValid(input))
                return ErrorInfo("Invalid input").toJson();
        DartsScore score;
        if(_evaluator->isWithinBounds(input)){
                _inputs->save(input.toInternal());
               score =  _scores->update(input);
        }
        else{
                _inputs->save(DartsInput::nullified(input).toInternal());
                score = _scores->score();
        }
        _indexes->next();
        return score.toJson();
}

bool DartsController::reset() {
        _inputs->clear();
        _scores->reset();
        _indexes->reset();
        return true;
}

QByteArray DartsController::undoTurn() {
        if(!_indexes->canUndo())
                return ErrorInfo("Undo is not allowed").toJson();
        _indexes->undo();
        auto score = _scores->update();
        return score.toJson();
}

QByteArray DartsController::redoTurn() {
        if(!_indexes->redo())
                return ErrorInfo("Not allowed").toJson();
        auto score = _scores->update();
        return score.toJson();
}
