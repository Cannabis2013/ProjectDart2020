#ifndef CONTROLLERVALUES_H
#define CONTROLLERVALUES_H

#include <QJsonDocument>
#include "qjsonarray.h"
#include "qjsonobject.h"

class QByteArray;

class ControllerValues {
  public:
    ControllerValues(
      const QByteArray &json)
    {
        auto jsonDoc = QJsonDocument::fromJson(json);
        auto jsonObj = jsonDoc.object();
        initialScore = jsonObj["initialScore"].toInt(501);
        withOpen = jsonObj.value("withOpenCondition").toBool();
        withClose = jsonObj.value("withCloseCondition").toBool();
        closeningMod = jsonObj.value("closeningMod").toString("S");
        openingMod = jsonObj.value("openingMod").toString("D");
        mode = jsonObj["gameMode"].toInt(1);

        auto arr = jsonObj["players"].toArray().toVariantList();
        for (const auto &jsonVal : std::as_const(arr))
          names << jsonVal.toString();

        playersCount = names.length();
    }

    int playersCount = 0;
    QStringList names;
    int initialScore;
    int mode;
    QString openingMod;
    QString closeningMod;
    bool withOpen;
    bool withClose;
};

#endif // CONTROLLERVALUES_H
