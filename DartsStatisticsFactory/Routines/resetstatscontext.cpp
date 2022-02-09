#include "resetstatscontext.h"
#include "SLAs/servicescontext.h"
#include <qvector.h>
#include <Players/Models/imirrorsdb.h>
ResetStatsContext::ResetStatsContext(ServicesContext *provider)
{
    _statsDb = provider->statisticServices()->statModels();
    _iptDb = provider->snapShotServices()->snapShots();
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
