#include "createstatsreport.h"
#include "SLAs/servicescontext.h"
#include <qjsondocument.h>
#include <qjsonobject.h>

CreateStatsReport::CreateStatsReport(ServicesContext *provider)
{
    _statsDb = provider->currentStatsServices()->statsDb();
}

ICreateReport::ByteArray CreateStatsReport::create(const QString &name) const
{
    auto stats = _statsDb->model([=](const CurrentStats &m){return m.name == name;});
    return makeReport(stats);
}

ICreateReport::ByteArray CreateStatsReport::makeReport(const CurrentStats &stats) const
{
    QJsonObject obj;
    obj["minimum"] = stats.min;
    obj["middle"] = stats.mid;
    obj["maximum"] = stats.max;
    obj["q1"] = stats.q1;
    obj["q2"] = stats.q2;
    obj["q3"] = stats.q3;
    obj["finishRatio"] = stats.fRatio;
    return QJsonDocument(obj).toJson();
}
