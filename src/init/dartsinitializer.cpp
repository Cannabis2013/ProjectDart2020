#include "dartsinitializer.h"
#include "src/init/controllervalues.h"
#include "src/input/idartsinputs.h"
#include "src/players/idartsplayers.h"
#include "src/scores/idartsremainings.h"
#include "src/servicecollection.h"
#include "src/turns/idartsindexes.h"
#include "src/validation/iclosurefilter.h"
#include "src/validation/iopenvalidator.h"

DartsInitializer::DartsInitializer(ServiceCollection* services)
  : _services(services)
{}

void DartsInitializer::init(const QByteArray& json)
{
    ControllerValues values(json);
    _services->players->init(values.names);
    _services->indexes->init(values.names.count());
    _services->scores->setInitialRemaining(values.initialScore);
    _services->inputs->init();
    _services->openingFilter->init(values.withOpen, values.openingMod);
    _services->closeningFilter->init(values.withClose, values.closeningMod);
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
    _services->indexes->reset();
    _services->inputs->init();
    _services->players->reset();
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
