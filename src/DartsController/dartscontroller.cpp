#include "dartscontroller.h"

#include "src/DartsController/indexes/dartindexes.h"
#include "src/DartsController/init/dartInitInfo.h"
#include "src/DartsController/input/dartinputevaluator.h"
#include "src/DartsController/input/dartinputs.h"
#include "src/DartsController/players/dartplayers.h"
#include "src/DartsController/responses/ErrorInfo.h"
#include "src/DartsController/scores/dartsscores.h"
#include <src/DartsController/responses/dartsinforesponse.h>

DartsController::DartsController() {
        _indexes = new DartIndexes();
        _players = new DartPlayers();
        _inputs = new DartInputs(_indexes);
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
        _indexes->initFromExternalContext(_players->playersCount());
}

QByteArray DartsController::initialValues() const
{
        return _response->initialInfo().toJson();
}

QByteArray DartsController::turnInfo() const
{
        return _response->currentTurnInfo().toJson();
}

QByteArray DartsController::addInput(const QByteArray &inputAsJson)
{
        auto input = DartInput::fromJson(inputAsJson);
        if(!_evaluator->isValid(input))
                return ErrorInfo("Invalid input").toJson(); // Should return some error message
        if(_evaluator->isWithinBounds(input)){
                _inputs->save(input);
                _scores->update(input);
        }
        else{
                _inputs->save(DartInput::nullified(input));
        }
        if(_scores->score() == 0)
                return _response->winnerInfo().toJson();
        _indexes->next();
        return _response->currentTurnInfo().toJson();
}

bool DartsController::reset() {
        _inputs->clear();
        _scores->reset();
        _indexes->reset();
        return true;
}

QByteArray DartsController::undoTurn() {
        if(!_indexes->previous())
                return ErrorInfo("Undo is not allowed").toJson();
        _scores->update();
        return _response->currentTurnInfo().toJson();
}

QByteArray DartsController::redoTurn() {
        if(!_indexes->next())
                return ErrorInfo("Not allowed").toJson();
        _scores->update();
        return _response->currentTurnInfo().toJson();
}
