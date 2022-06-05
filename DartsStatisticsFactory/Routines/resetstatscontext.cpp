#include "resetstatscontext.h"
#include <qvector.h>
#include <DartsStatistics/SLAs/servicescontext.h>
#include <DartsStatistics/Db/istatsdb.h>

ResetStatsContext::ResetStatsContext(ServicesContext *provider)
{
        _statsDb = provider->statisticServices()->statModels();
        _inputDb = provider->snapShotServices()->snapShotsDb();
}

void ResetStatsContext::reset()
{
        resetCurrentStats();
        _inputDb->clear();
}

void ResetStatsContext::resetCurrentStats()
{
        auto models = _statsDb->models();
        _statsDb->clear();
        for (const auto &model : models)
                _statsDb->add({.name = model.name});
}
