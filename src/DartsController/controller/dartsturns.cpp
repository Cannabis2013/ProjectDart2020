#include "dartsturns.h"

DartsTurns::DartsTurns(IDartsStatus* status, IDartsIndexes* indexes, IDartsScores* scores, IDartsPlayers* players, IPlayerAllowances* allowances, IDartsInputs* inputs)
    : _status(status)
    , _indexes(indexes)
    , _scores(scores)
    , _players(players)
    , _allowances(allowances)
    , _inputs(inputs)
{
}

void DartsTurns::init(IDartsEvaluator* evaluator)
{
        _evaluator = evaluator ? evaluator : throw "Evaluator not set";
}

void DartsTurns::undo()
{
        auto name = _players->player().name();
        undoTurn();
        auto index = _indexes->index();
        if (index.turnIndex() == 0 || index.turnIndex() == 3)
                _allowances->updateAllowance(name, false);
}

void DartsTurns::redo()
{
        auto name = _players->player().name();
        redoTurn();
        updateAllowance(name);
}

void DartsTurns::updateAllowance(const QString& name)
{
        auto inputs = _inputs->inputs(name);
        if (!inputs.isEmpty()) {
                auto lastInput = inputs.last();
                _evaluator->evaluateInput(lastInput.mod(), lastInput.point());
        }
}

void DartsTurns::undoTurn()
{
        _status->running();
        _indexes->undo();
        _scores->update();
        _players->reset();
        _evaluator->evaluateWinnerCondition();
}

void DartsTurns::redoTurn()
{
        _indexes->redo();
        _scores->update();
        _evaluator->evaluateWinnerCondition();
}
