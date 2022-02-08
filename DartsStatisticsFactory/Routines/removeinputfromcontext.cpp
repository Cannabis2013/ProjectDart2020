#include "removeinputfromcontext.h"
#include "SLAs/servicescontext.h"
#include <qvector.h>

RemoveInputFromContext::RemoveInputFromContext(ServicesContext *provider)
{
    _statsDb = provider->currentStatsServices()->statsDb();
    _iptsDb = provider->inputServices()->inputsDb();
}

bool RemoveInputFromContext::remove(const QString &name)
{
    CurrentStats stats;
    Input ipt;
    try {
        auto stats = _statsDb->model([=](const CurrentStats &m){return m.name == name;});
        auto ipt = getLastInput(name,stats);
    }  catch (...) {
        return false;
    }
    auto indexOfStats = _statsDb->indexOf(stats);
    _statsDb->replace(indexOfStats,ipt.stats);
    auto indexOfInput = _iptsDb->indexOf(ipt);
    _iptsDb->remove(indexOfInput);
    return true;
}

Input RemoveInputFromContext::getLastInput(const QString &name, const CurrentStats &stats)
{
    auto n = stats.n;
    auto input = _iptsDb->model([=](const Input &ipt){
        if(ipt.name != name)
            return false;
        auto iptStatsImage = ipt.stats;
        if(iptStatsImage.n != n)
            return false;
        return true;
    });
    return input;
}
