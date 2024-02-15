#include "dartscontroller.h"
#include "src/DartsController/scores/DartsPlayerScores.h"

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
        return scores()->scores().json();
}

QByteArray DartsController::allPlayers() const
{
        return players()->allAsJson();
}

QByteArray DartsController::turnReport() const
{
        return turnDetails()->report();
}

void DartsController::addInput(const QString& mod, const int& point){
        adder()->add(mod, point);
}

void DartsController::undoTurn(){
        turns()->undo();
}

void DartsController::redoTurn(){
        turns()->redo();
}

void DartsController::skipTurn()
{
        turns()->skip();
}
