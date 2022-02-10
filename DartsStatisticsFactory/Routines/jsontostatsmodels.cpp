#include "jsontostatsmodels.h"
#include <qvector.h>
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <QJsonObject>
#include "SLAs/servicescontext.h"
#include "Players/ijsontostatsmodel.h"

JsonToStatsModels::JsonToStatsModels(ServicesContext *provider)
{
    _converter = provider->statisticServices()->jsonToStatsModel();
}

JsonToStatsModels::Models JsonToStatsModels::convert(const ByteArray &ba) const
{
    auto jDoc = QJsonDocument::fromJson(ba);
    if(!jDoc.isObject()) return Models();
    auto jObj = jDoc.object();
    auto jVal = jObj.value("players");
    if(!jVal.isArray()) return Models();
    auto arr = jVal.toArray();
    Models m;
    for (const auto &val : arr)
        m << _converter->convert(val.toObject());
    return m;
}
