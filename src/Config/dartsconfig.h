#ifndef DARTSCONFIG_H
#define DARTSCONFIG_H

#include <QJsonObject>
#include <QObject>

class DartsConfig : public QObject {
        Q_OBJECT
public:
        DartsConfig();

        Q_INVOKABLE QByteArray configData() const;
        Q_INVOKABLE QString readConfigData(const QString& key);
        Q_INVOKABLE void setConfigData(const QString& key, const QString& value);

private:
        QJsonObject readFromFile();
        void saveToFile();
        QJsonObject _jsonObj;
};

#endif // DARTSCONFIG_H
