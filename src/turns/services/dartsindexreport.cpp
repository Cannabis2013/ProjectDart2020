#include "dartsindexreport.h"
#include "src/servicecollection.h"
#include "src/turns/models/dartsturnindex.h"
#include "src/turns/persistences/idartsindexes.h"

#include <QByteArray>
#include <QJsonDocument>

DartsIndexReport::DartsIndexReport(ServiceCollection* services)
    : _services(services)
{
}

QByteArray DartsIndexReport::report() const
{
        QJsonObject jsonObj;
        auto index = _services->indexes->index();
        jsonObj["roundIndex"] = index.roundIndex();
        jsonObj["turnId"] = index.turnId();
        auto jsonDoc = QJsonDocument(jsonObj);
        return jsonDoc.toJson(QJsonDocument::Compact);
}
