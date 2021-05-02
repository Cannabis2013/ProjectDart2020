#ifndef GETTOURNAMENTINDEXESFROMJSON_H
#define GETTOURNAMENTINDEXESFROMJSON_H

#include <qvector.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

class GetTournamentIndexesFromJson
{
public:
    static QVector<int> GetIndexesFromJson(const QByteArray& json)
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
