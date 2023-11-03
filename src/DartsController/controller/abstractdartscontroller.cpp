#include "abstractdartscontroller.h"

IDartsEvaluator* AbstractDartsController::evaluator() const
{
        return _evaluator;
}

void AbstractDartsController::setEvaluator(IDartsEvaluator* newEvaluator)
{
        _evaluator = newEvaluator;
}

IDartsIndexes* AbstractDartsController::indexes() const
{
        return _indexes;
}

void AbstractDartsController::setIndexes(IDartsIndexes* newIndexes)
{
        _indexes = newIndexes;
}

IDartsScores* AbstractDartsController::scores() const
{
        return _scores;
}

void AbstractDartsController::setScores(IDartsScores* newScores)
{
        _scores = newScores;
}

IDartsInputs* AbstractDartsController::inputs() const
{
        return _inputs;
}

void AbstractDartsController::setInputs(IDartsInputs* newInputs)
{
        _inputs = newInputs;
}

IDartsInfoResponse* AbstractDartsController::turnValues() const
{
        return _turnValues;
}

void AbstractDartsController::setTurnValues(IDartsInfoResponse* newTurnValues)
{
        _turnValues = newTurnValues;
}

IDartsPlayers* AbstractDartsController::players() const
{
        return _players;
}

void AbstractDartsController::setPlayers(IDartsPlayers* newPlayers)
{
        _players = newPlayers;
}

IDartsStatistics* AbstractDartsController::statistics() const
{
        return _statistics;
}

void AbstractDartsController::setStatistics(IDartsStatistics* newStatistics)
{
        _statistics = newStatistics;
}

IDartsFinishes* AbstractDartsController::finishes() const
{
        return _finishes;
}

void AbstractDartsController::setFinishes(IDartsFinishes* newFinishes)
{
        _finishes = newFinishes;
}

IDartsStatus* AbstractDartsController::status() const
{
        return _status;
}

void AbstractDartsController::setStatus(IDartsStatus* newStatus)
{
        _status = newStatus;
}

IDartsInputAdder* AbstractDartsController::adder() const
{
        return _adder;
}

void AbstractDartsController::setAdder(IDartsInputAdder* newAdder)
{
        newAdder->setEvaluator(&_evaluator);
        _adder = newAdder;
}

DartsEvaluators* AbstractDartsController::evaluators() const
{
        return _evaluators;
}

void AbstractDartsController::setEvaluators(DartsEvaluators* newEvaluators)
{
        _evaluators = newEvaluators;
}

IDartsInputTrimmer* AbstractDartsController::trimmer() const
{
        return _trimmer;
}

void AbstractDartsController::setTrimmer(IDartsInputTrimmer* newTrimmer)
{
        _trimmer = newTrimmer;
}
