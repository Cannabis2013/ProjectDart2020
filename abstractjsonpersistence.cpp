#include "abstractjsonpersistence.h"

AbstractJSONPersistence::AbstractJSONPersistence()
{

}

void AbstractJSONPersistence::writeJSONToFile(const QJsonObject &json, const QString &fileName)
{
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);

    QDataStream out(&file);
    out << json.toVariantHash();

    file.close();
}

QJsonObject AbstractJSONPersistence::readJSONFromFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.exists())
        return QJsonObject();
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    QVariantHash dataHash;
    in >> dataHash;
    QJsonObject obj = QJsonObject::fromVariantHash(dataHash);
    return obj;
}
