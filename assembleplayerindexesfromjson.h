#ifndef ASSEMBLEPLAYERINDEXESFROMJSON_H
#define ASSEMBLEPLAYERINDEXESFROMJSON_H

#include <iunaryservice.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

class AssemblePlayerIndexesFromJson : public
        IUnaryService<const QByteArray&,QVector<int>>
{
public:
    QVector<int> service(const QByteArray& json) override
    {
        QVector<int> list;
        auto document = QJsonDocument::fromJson(json);
        auto jsonObject = document.object();
        auto arr = jsonObject.value("playerIndexes").toArray();
        for (const auto& jsonValue : arr) {
            auto index = jsonValue.toInt();
            list << index;
        }
        return list;
    }
};

#endif // ASSEMBLEPLAYERINDEXESFROMJSON_H
