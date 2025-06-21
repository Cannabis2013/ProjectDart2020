#include "dartsinitializer.h"
#include "src/init/controllervalues.h"
#include "src/input/persistence/idartsinputs.h"
#include "src/players/persistences/idartsplayers.h"
#include "src/scores/persistence/idartsscores.h"
#include "src/scores/services/iscoresupdate.h"
#include "src/servicecollection.h"
#include "src/turns/persistences/idartsindexes.h"
#include "src/validation/services/iclosurefilter.h"
#include "src/validation/services/iopenvalidator.h"

DartsInitializer::DartsInitializer(ServiceCollection* services)
    : _services(services)
{
}

void DartsInitializer::init(const QByteArray& json)
{
        ControllerValues values(json);
        _services->players->init(values.playersCount);
        _services->indexes->init(values.playersCount);
        _services->inputs->init();
        _services->scoresUpdate->initPlayerScores(values.initialScore);
        _services->openingFilter->init(values.withOpenCondition,values.openingModifier);
        _services->closeningFilter->init(values.withCloseCondition);
}

void DartsInitializer::initFromStorage()
{
        _services->players->initFromFile();
        _services->indexes->initFromFile();
        _services->inputs->initFromFile();
        _services->scores->initFromStorage();
        _services->closeningFilter->initFromFile();
        _services->openingFilter->initFromFile();
}

void DartsInitializer::reset()
{
        _services->players->reset();
        _services->indexes->reset();
        _services->inputs->init();
        _services->scoresUpdate->resetPlayerScores();
        _services->openingFilter->reset();
}

void DartsInitializer::saveState()
{
        _services->indexes->saveState();
        _services->scores->saveState();
        _services->inputs->saveState();
        _services->players->saveState();
        _services->closeningFilter->saveState();
        _services->openingFilter->saveState();
}
