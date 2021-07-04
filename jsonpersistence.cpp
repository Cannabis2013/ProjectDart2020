#include "jsonpersistence.h"

void JSONPersistence::writeJsonObjectToFile(const QByteArray &json, const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
        throw "File readings issues: Can't write to file. Maybe it's non existent or access issues";
    QDataStream out(&file);
    out << json;
    file.close();
}

QByteArray JSONPersistence::readJsonObjectFromFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.exists())
        throw "File not found";
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    QByteArray obj;
    in >> obj;
    return obj;
}
