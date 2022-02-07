#include "resetstatscontext.h"
#include "SLAs/servicescontext.h"
#include <qvector.h>
#include <Players/Models/currentstats.h>
ResetStatsContext::ResetStatsContext(ServicesContext *provider)
{
    _statsDb = provider->currentStatsServices()->statsDb();
    _iptDb = provider->inputServices()->inputsDb();
}

void ResetStatsContext::reset()
{
    resetCurrentStats();
    _iptDb->clear();
}

void ResetStatsContext::resetCurrentStats()
{
    auto models = _statsDb->models();
    _statsDb->clear();
    for (const auto &model : models)
        _statsDb->add({.name = model.name});
}
