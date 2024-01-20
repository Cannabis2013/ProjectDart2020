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

QByteArray DartsController::statisticReport() const
{
        return statistics()->report();
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