#include "controllervalues.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <qjsonarray.h>

ControllerValues::ControllerValues(const QByteArray& json)
{
        auto jsonDoc = QJsonDocument::fromJson(json);
        auto jsonObj = jsonDoc.object();
        _playersCount = jsonObj["playersCount"].toInt(0);
        _initialScore = jsonObj["initialScore"].toInt(501);
        _mode = jsonObj["gameMode"].toInt(1);
}

int ControllerValues::playersCount() const
{
        return _playersCount;
}

int ControllerValues::initialScore() const
{
        return _initialScore;
}

int ControllerValues::mode() const
{
        return _mode;
}
