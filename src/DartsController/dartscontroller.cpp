#include "dartscontroller.h"
#include "src/DartsController/Finishes/dartsfinishes.h"
#include "src/DartsController/indexes/dartsindexes.h"
#include "src/DartsController/input/dartsinputadder.h"
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
        _turnValues = new DartsTurnValues(_players, _indexes, _statistics, _finishes, _scores, _status);
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
        _indexes->initFromFile();
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
        return _scores->scores().toJson();
}

QByteArray DartsController::turnInfo() const
{
        return _turnValues->currentTurnInfo();
}

void DartsController::addInput(const QString& mod, const int& point)
{
        if (_status->status() == IDartsStatus::Winner)
                return;
        _adder->add(mod, point);
        _scores->update();
}

void DartsController::undoTurn()
{
        _status->updateStatus(IDartsStatus::Running);
        _indexes->undo();
        _scores->update();
}

void DartsController::redoTurn()
{
        _indexes->redo();
        _scores->update();
}
