#include "dartscontroller.h"
#include "src/DartsController/indexes/dartsindexes.h"
#include "src/DartsController/input/InputRequest.h"
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
        _response = new DartsInfoResponse(_players,_indexes);
}

void DartsController::init(const QStringList& playerNames)
{
        _players->initPlayers(playerNames);
        _indexes->init(playerNames.count());
        _scores->init();
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

QByteArray DartsController::playerScores() const
{
        auto json = _scores->scores().toJson();
        return json;
}

QByteArray DartsController::turnInfo() const
{
        if(_scores->score().playerScore() == 0)
                return _response->winnerInfo().toJson();
        return _response->currentTurnInfo().toJson();
}

QByteArray DartsController::addInput(const QByteArray &inputAsJson)
{
        InputRequest req(inputAsJson);
        if(!_evaluator->isValid(req.mod(),req.point()))
                return ErrorInfo("Invalid input").toJson();
        DartsPlayerScore score;
        if(_evaluator->isWithinBounds(req.mod(),req.point())){
                _inputs->save(req.toInput());
               score =  _scores->update(req.toInput());
        }
        else{
                _inputs->save(req.toNullified());
                score = _scores->score();
        }
        _indexes->next();
        return score.toJson();
}

QByteArray DartsController::undoTurn() {
        if(!_indexes->undo())
                return ErrorInfo("Undo is not allowed").toJson();
        auto scores = _scores->update();
        return scores.toJson();
}

QByteArray DartsController::redoTurn() {
        if(!_indexes->redo())
                return ErrorInfo("Not allowed").toJson();
        auto score = _scores->update();
        return score.toJson();
}
