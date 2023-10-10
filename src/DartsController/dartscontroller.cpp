#include "dartscontroller.h"
#include "src/DartsController/Finishes/dartsfinishes.h"
#include "src/DartsController/indexes/dartsindexes.h"
#include "src/DartsController/input/InputRequest.h"
#include "src/DartsController/input/dartsinputevaluator.h"
#include "src/DartsController/input/dartsinputs.h"
#include "src/DartsController/players/dartsplayers.h"
#include "src/DartsController/scores/dartsscores.h"
#include "src/DartsController/statistics/dartsstatistics.h"
#include "src/DartsController/status/DartsStatus.h"
#include <src/DartsController/responses/dartsturnvalues.h>

DartsController::DartsController() {
        _status = new DartsStatus();
        _indexes = new DartsIndexes();
        _finishes = new DartsFinishes();
        _players = new DartsPlayers(_indexes);
        _inputs = new DartsInputs(_indexes, _players);
        _scores = new DartsScores(_indexes, _players, _inputs, _status);
        _evaluator = new DartsInputEvaluator(_scores);
        _statistics = new DartsStatistics(_inputs, _players, _scores, _indexes);
        _response = new DartsTurnValues(_players, _indexes, _statistics, _finishes, _scores, _status);
        _adder = new DartsInputAdder(_inputs, _evaluator, _indexes, _scores);
}

void DartsController::init(const QStringList& playerNames)
{
        _players->initPlayers(playerNames);
        _indexes->init(playerNames.count());
        _inputs->init();
        _scores->init();
        _status->init();
}

QStringList DartsController::playerNames() const
{
        return _players->names();
}

void DartsController::initFromSaved()
{
        _players->initPlayers();
        _indexes->init();
        _inputs->initFromFile();
        _scores->initFromFile();
        _status->initFromFile();
}

void DartsController::saveState()
{
        _indexes->saveState();
        _scores->saveState();
        _inputs->saveState();
        _players->saveState();
        _status->saveState();
}

QByteArray DartsController::playerScores() const
{
        auto json = _scores->scores().toJson();
        return json;
}

QByteArray DartsController::turnInfo() const
{
        return _response->currentTurnInfo().toJson();
}

QByteArray DartsController::addInput(const QByteArray &inputAsJson)
{
        if (_status->status() == IDartsStatus::Winner)
                return _scores->score().toJson();
        _adder->add(InputRequest(inputAsJson));
        return _scores->update().toJson();
}

QByteArray DartsController::undoTurn() {
        _status->updateStatus(IDartsStatus::Running);
        _indexes->undo();
        auto scores = _scores->update();
        return scores.toJson();
}

QByteArray DartsController::redoTurn() {
        _indexes->redo();
        auto score = _scores->update();
        return score.toJson();
}
