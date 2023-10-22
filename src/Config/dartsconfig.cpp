#include "dartsconfig.h"
#include "src/FileIO/filejsonio.h"
#include <QJsonDocument>

DartsConfig::DartsConfig()
{
        _jsonObj = readFromFile();
}

QByteArray DartsConfig::configData() const
{
        return QJsonDocument(_jsonObj).toJson(QJsonDocument::Compact);
}

QString DartsConfig::readConfigData(const QString& key)
{
        return _jsonObj.value(key).toString("");
}

void DartsConfig::setConfigData(const QString& key, const QString& value)
{
        _jsonObj[key] = value;
        saveToFile();
}

QJsonObject DartsConfig::readFromFile()
{
        FileJsonIO in("config.dat");
        auto jsonDoc = QJsonDocument::fromJson(in.read());
        if (!jsonDoc.isObject())
                return QJsonObject();
        return jsonDoc.object();
}

void DartsConfig::saveToFile()
{
        FileJsonIO out("config.dat");
        auto json = QJsonDocument(_jsonObj).toJson(QJsonDocument::Compact);
        out.write(json);
}
