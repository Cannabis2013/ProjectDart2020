#include "dartscontroller.h"

void DartsController::init(const QStringList& playerNames, const int& mode, const int& initialScore)
{
        players()->init(playerNames);
        indexes()->init(playerNames.count());
        inputs()->init();
        scores()->init(initialScore);
        status()->init();
        setEvaluator(evaluators()->validator(mode));
        evaluator()->init();
}

void DartsController::initFromSaved(){
        players()->initFromFile();
        indexes()->initFromFile();
        inputs()->initFromFile();
        scores()->initFromFile();
        status()->initFromFile();
        setEvaluator(evaluators()->validator());
}

void DartsController::reset()
{
        players()->reset();
        indexes()->reset();
        inputs()->init();
        scores()->reset();
        status()->init();
        evaluator()->init();
}

void DartsController::saveState(){
        indexes()->saveState();
        scores()->saveState();
        inputs()->saveState();
        players()->saveState();
        status()->saveState();
        evaluators()->saveState();
}

QByteArray DartsController::playerScores() const
{
        return scores()->scores().toJson();
}

QStringList DartsController::playerNames() const
{
        return players()->names();
}

QByteArray DartsController::turnInfo() const
{
        return turnValues()->currentTurnInfo();
}

void DartsController::addInput(const QString& mod, const int& point){
        adder()->add(mod, point);
        scores()->update();
        evaluator()->evaluateScoreCondition();
}

void DartsController::undoTurn(){
        status()->running();
        indexes()->undo();
        scores()->update();
        players()->reset();
        evaluator()->evaluateScoreCondition();
}

void DartsController::redoTurn(){
        indexes()->redo();
        scores()->update();
        evaluator()->evaluateScoreCondition();
}

void DartsController::skipTurn()
{
        trimmer()->trimInputs();
        indexes()->skipturn();
}
