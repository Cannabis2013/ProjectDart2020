#include "dartscontroller.h"

void DartsController::init(const QByteArray& json)
{
        initializer()->init(json);
}

void DartsController::initFromSaved(){
        initializer()->initFromStorage();
}

void DartsController::reset()
{
        initializer()->reset();
}

void DartsController::saveState(){
        initializer()->saveState();
}

QByteArray DartsController::playerScores() const
{
        return scores()->scores().toJson();
}

QStringList DartsController::playerNames() const
{
        return players()->names();
}

QString DartsController::winnerImage() const
{
        return players()->winner().winnerImageUrl();
}

QByteArray DartsController::turnInfo() const
{
        return turnValues()->currentTurnInfo();
}

void DartsController::addInput(const QString& mod, const int& point){
        adder()->add(mod, point);
        scores()->update();
        evaluator()->evaluateWinnerCondition();
}

void DartsController::undoTurn(){
        turns()->undo();
}

void DartsController::redoTurn(){
        turns()->redo();
}

void DartsController::skipTurn()
{
        trimmer()->trimInputs();
        indexes()->skipturn();
}
