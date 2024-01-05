#include "controllerinitializer.h"
#include "controllerservices.h"
#include "src/DartsController/controller/controllervalues.h"

ControllerInitializer::ControllerInitializer(ControllerServices* services)
    : _services(services)
{
}

void ControllerInitializer::init(const QByteArray& json)
{
        ControllerValues values(json);
        _services->players()->init(values.playersCount());
        _services->indexes()->init(values.playersCount());
        _services->inputs()->init();
        _services->scores()->init(values.initialScore());
        _services->status()->init();
        auto evaluator = _services->evaluators()->validator(values.mode());
        _services->setEvaluator(evaluator);
        _services->evaluator()->init();
}

void ControllerInitializer::initFromStorage()
{
        _services->players()->initFromFile();
        _services->indexes()->initFromFile();
        _services->inputs()->initFromFile();
        _services->scores()->initFromFile();
        _services->status()->initFromFile();
        auto evaluator = _services->evaluators()->validator();
        _services->setEvaluator(evaluator);
}

void ControllerInitializer::reset()
{
        _services->players()->reset();
        _services->indexes()->reset();
        _services->inputs()->init();
        _services->scores()->reset();
        _services->status()->init();
        _services->evaluator()->init();
}

void ControllerInitializer::saveState()
{
        _services->indexes()->saveState();
        _services->scores()->saveState();
        _services->inputs()->saveState();
        _services->players()->saveState();
        _services->status()->saveState();
        _services->evaluators()->saveState();
}
