#include "serviceinitializer.h"
#include "src/DartsController/servicecollection.h"
#include "src/DartsController/indexes/idartsindexes.h"
#include "src/DartsController/init/controllervalues.h"
#include "src/DartsController/input/idartsinputs.h"
#include "src/DartsController/players/idartsplayers.h"
#include "src/DartsController/scores/idartsscores.h"
#include "src/DartsController/status/idartsstatus.h"
#include "src/DartsController/turns/iturncontroller.h"
#include "src/DartsController/validation/dartsevaluators.h"

ServiceInitializer::ServiceInitializer(ServiceCollection* services)
    : _services(services)
{
}

void ServiceInitializer::init(const QByteArray& json)
{
        ControllerValues values(json);
        _services->players->init();
        _services->indexes->init(values.playersCount());
        _services->inputs->init();
        _services->scores->init(values.initialScore());
        _services->status->init();
        auto evaluator = _services->evaluators->validator(values.mode());
        _services->evaluator = evaluator;
        _services->evaluator->init();
}

void ServiceInitializer::initFromStorage()
{
        _services->players->initFromFile();
        _services->indexes->initFromFile();
        _services->inputs->initFromFile();
        _services->scores->initFromFile();
        _services->status->initFromFile();
        auto evaluator = _services->evaluators->validator();
        _services->evaluator = evaluator;
        _services->evaluator->init();
}

void ServiceInitializer::reset()
{
        _services->players->reset();
        _services->indexes->reset();
        _services->inputs->init();
        _services->scores->reset();
        _services->status->init();
        _services->evaluator->init();
}

void ServiceInitializer::saveState()
{
        _services->indexes->saveState();
        _services->scores->saveState();
        _services->inputs->saveState();
        _services->players->saveState();
        _services->status->saveState();
        _services->evaluators->saveState();
}
