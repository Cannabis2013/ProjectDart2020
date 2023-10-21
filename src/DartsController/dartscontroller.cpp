#include "dartscontroller.h"
#include "src/DartsController/validation/dartsevaluators.h"

void DartsController::init(const QStringList& playerNames, const int& mode)
{
        _players->initPlayers(playerNames);
        _indexes->init(playerNames.count());
        _inputs->init();
        _scores->init();
        _status->init();
        _evaluator = _evaluators->validator(mode);
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
        _evaluator = _evaluators->validator();
}

void DartsController::saveState()
{
        _indexes->saveState();
        _scores->saveState();
        _inputs->saveState();
        _players->saveState();
        _status->saveState();
        _evaluators->saveState();
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
        _adder->add(mod, point);
        _scores->update();
        _evaluator->evaluateScoreCondition();
}

void DartsController::undoTurn()
{
        _status->running();
        _indexes->undo();
        _scores->update();
        _evaluator->evaluateScoreCondition();
}

void DartsController::redoTurn()
{
        _indexes->redo();
        _scores->update();
        _evaluator->evaluateScoreCondition();
}
