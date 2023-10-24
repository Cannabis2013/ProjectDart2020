#include "dartscontroller.h"

void DartsController::init(const QStringList& playerNames, const int& mode){
        _players->init(playerNames);
        _indexes->init(playerNames.count());
        _inputs->init();
        _scores->init();
        _status->init();
        _evaluator = _evaluators->validator(mode);
}

void DartsController::initFromSaved(){
        _players->initFromFile();
        _indexes->initFromFile();
        _inputs->initFromFile();
        _scores->initFromFile();
        _status->initFromFile();
        _evaluator = _evaluators->validator();
}

void DartsController::reset()
{
        _players->reset();
        _indexes->reset();
        _inputs->init();
        _scores->init();
        _status->init();
}

void DartsController::saveState(){
        _indexes->saveState();
        _scores->saveState();
        _inputs->saveState();
        _players->saveState();
        _status->saveState();
        _evaluators->saveState();
}

void DartsController::addInput(const QString& mod, const int& point){
        _adder->add(mod, point);
        _scores->update();
        _evaluator->evaluateScoreCondition();
}

void DartsController::undoTurn(){
        _status->running();
        _indexes->undo();
        _scores->update();
        _evaluator->evaluateScoreCondition();
}

void DartsController::redoTurn(){
        _indexes->redo();
        _scores->update();
        _evaluator->evaluateScoreCondition();
}
