#ifndef GETTOURNAMENTINDEXESFROMJSON_H
#define GETTOURNAMENTINDEXESFROMJSON_H

#include "iunaryservice.h"
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include <qvector.h>

class GetTournamentIndexesFromJson :
        public IUnaryService<const QByteArray&,QVector<int>>
{
public:
    QVector<int> service(const QByteArray& json) override
    {
        QVector<int> indexes;
        auto obj = QJsonDocument::fromJson(json).object();
        auto arr = obj.value("Indexes").toArray();
        for (auto jsonValue : arr) {
            auto index = jsonValue.toInt();
            indexes << index;
        }
        return indexes;
    }
};

#endif // GETTOURNAMENTINDEXESFROMJSON_H
