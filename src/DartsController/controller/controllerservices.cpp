#include "controllerservices.h"

AbstractDartsEvaluator* ControllerServices::evaluator() const
{
        return _evaluator;
}

void ControllerServices::setEvaluator(AbstractDartsEvaluator* newEvaluator)
{
        _evaluator = newEvaluator;
}

IDartsIndexes* ControllerServices::indexes() const
{
        return _indexes;
}

void ControllerServices::setIndexes(IDartsIndexes* newIndexes)
{
        _indexes = newIndexes;
}

IDartsScores* ControllerServices::scores() const
{
        return _scores;
}

void ControllerServices::setScores(IDartsScores* newScores)
{
        _scores = newScores;
}

IDartsInputs* ControllerServices::inputs() const
{
        return _inputs;
}

void ControllerServices::setInputs(IDartsInputs* newInputs)
{
        _inputs = newInputs;
}

IDartsTurnInfo* ControllerServices::turnDetails() const
{
        return _turnInfo;
}

void ControllerServices::setTurnInfo(IDartsTurnInfo* newTurnValues)
{
        _turnInfo = newTurnValues;
}

IDartsPlayers* ControllerServices::players() const
{
        return _players;
}

void ControllerServices::setPlayers(IDartsPlayers* newPlayers)
{
        _players = newPlayers;
}

IDartsStatistics* ControllerServices::statistics() const
{
        return _statistics;
}

void ControllerServices::setStatistics(IDartsStatistics* newStatistics)
{
        _statistics = newStatistics;
}

IDartsFinishes* ControllerServices::finishes() const
{
        return _finishes;
}

void ControllerServices::setFinishes(IDartsFinishes* newFinishes)
{
        _finishes = newFinishes;
}

IDartsStatus* ControllerServices::status() const
{
        return _status;
}

void ControllerServices::setStatus(IDartsStatus* newStatus)
{
        _status = newStatus;
}

IDartsInputAdder* ControllerServices::adder() const
{
        return _adder;
}

void ControllerServices::setAdder(IDartsInputAdder* newAdder)
{
        newAdder->setEvaluator(&_evaluator);
        _adder = newAdder;
}

DartsEvaluators* ControllerServices::evaluators() const
{
        return _evaluators;
}

void ControllerServices::setEvaluators(DartsEvaluators* newEvaluators)
{
        _evaluators = newEvaluators;
}

ControllerInitializer* ControllerServices::initializer() const
{
        return _initializer;
}

void ControllerServices::setInitializer(ControllerInitializer* newInitializor)
{
        _initializer = newInitializor;
}

IDartsTurns* ControllerServices::turns() const
{
        return _turns;
}

void ControllerServices::setTurns(IDartsTurns* newTurns)
{
        _turns = newTurns;
}