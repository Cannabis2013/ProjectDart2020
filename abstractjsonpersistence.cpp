#include "abstractjsonpersistence.h"

void AbstractJSONPersistence::writeJsonObjectToFile(const QJsonObject &json, const QString &fileName)
{
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out << json;
    file.close();
}

QJsonObject AbstractJSONPersistence::readJsonObjectFromFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.exists())
        throw "File not found";
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    QJsonObject obj;
    in >> obj;
    return obj;
}
