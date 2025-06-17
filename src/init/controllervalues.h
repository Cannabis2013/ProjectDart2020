#ifndef CONTROLLERVALUES_H
#define CONTROLLERVALUES_H

#include <QJsonDocument>
#include "qjsonobject.h"

class QByteArray;

class ControllerValues {
public:
    ControllerValues(const QByteArray &json)
    {
        auto jsonDoc = QJsonDocument::fromJson(json);
        auto jsonObj = jsonDoc.object();
        playersCount = jsonObj["playersCount"].toInt(2);
        initialScore = jsonObj["initialScore"].toInt(501);
        withOpenCondition = jsonObj.value("withOpenCondition").toBool();
        withCloseCondition = jsonObj.value("withCloseCondition").toBool();
        openingModifier = jsonObj.value("openingModifier").toString("D");
        mode = jsonObj["gameMode"].toInt(1);
    }

    int playersCount;
    int initialScore;
    int mode;
    bool withOpenCondition;
    QString openingModifier;
    bool withCloseCondition;
};

#endif // CONTROLLERVALUES_H
