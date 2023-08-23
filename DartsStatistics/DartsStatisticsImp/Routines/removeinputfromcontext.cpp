#include "removeinputfromcontext.h"
#include <qvector.h>
#include <qdebug.h>
#include <DartsStatistics/Contracts/SLAs/servicescontext.h>
#include <DartsStatistics/Contracts/Db/istatsdb.h>

RemoveInputFromContext::RemoveInputFromContext(ServicesContext *provider)
{
        _mirrorsDb = provider->statisticServices()->statModels();
        _iptsDb = provider->snapShotServices()->snapShotsDb();
        _createMirror = provider->statisticServices()->createStatistic();
}

bool RemoveInputFromContext::remove(const QString &name)
{
        PlayerStats *mirror;
        PlayerStats newMirror;
        SnapShot ipt;
        try {
                mirror = &_mirrorsDb->model([=](const PlayerStats &m){return m.name == name;});
                auto ipt = getInputByN(name,mirror->n);
        }  catch (std::exception *e) {
                qDebug() << e->what();
                return false;
        }
        auto indexOfInput = _iptsDb->indexOf(ipt);
        _iptsDb->remove(indexOfInput);
        SnapShot newLastIpt;
        try {
                newMirror = getInputByN(name,mirror->n - 1).stats;
        }  catch (std::exception *e) {
                newMirror = _createMirror->create(name);
                qDebug() << e->what();
                return false;
        }
        *mirror = newMirror;
        return true;
}

SnapShot RemoveInputFromContext::getInputByN(const QString &name, const int &n)
{
    auto input = _iptsDb->model([=](const SnapShot &ipt){
        if(ipt.name != name)
            return false;
        auto iptStatsImage = ipt.stats;
        if(iptStatsImage.n != n)
            return false;
        return true;
    });
    return input;
}
