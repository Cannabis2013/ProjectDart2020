#include "dartsturns.h"

#include "src/DartsController/indexes/idartsindexes.h"
#include "src/DartsController/input/idartsinputs.h"
#include "src/DartsController/input/idartsinputtrimmer.h"
#include "src/DartsController/players/dartsplayer.h"
#include "src/DartsController/players/idartsplayers.h"
#include "src/DartsController/scores/DartsPlayerScores.h"
#include "src/DartsController/scores/idartsscores.h"
#include "src/DartsController/status/idartsstatus.h"
#include "src/DartsController/validation/abstractdartsevaluator.h"

DartsTurns::DartsTurns(IDartsStatus* status,
    IDartsIndexes* indexes,
    IDartsScores* scores,
    IDartsPlayers* players,
    IDartsInputs* inputs,
    IDartsInputTrimmer* trimmer)
    : _status(status)
    , _indexes(indexes)
    , _scores(scores)
    , _players(players)
    , _inputs(inputs)
    , _trimmer(trimmer)
{
}

void DartsTurns::init(AbstractDartsEvaluator* evaluator)
{
        _evaluator = evaluator ? evaluator : throw "Evaluator not set";
}

void DartsTurns::undo()
{
        auto name = _players->one().name();
        undoTurn();
        auto index = _indexes->index();
        if (!_inputs->anyInputs(name, index.throwIndex()))
                _evaluator->updateAllowance(name, false);
}

void DartsTurns::redo()
{
        auto name = _players->one().name();
        redoTurn();
        auto index = _indexes->index();
        if (_inputs->anyInputs(name, index.throwIndex()))
                _evaluator->updateAllowance(name, true);
}

void DartsTurns::skip()
{
        _trimmer->trimInputs();
        _indexes->skipturn();
}

void DartsTurns::undoTurn()
{
        _status->running();
        _indexes->undo();
        _scores->update();
        _evaluator->evaluateWinnerCondition();
}

void DartsTurns::redoTurn()
{
        _indexes->redo();
        _scores->update();
        _evaluator->evaluateWinnerCondition();
}
