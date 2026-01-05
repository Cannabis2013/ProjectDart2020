#include "dartsinput.h"

#include <QJsonDocument>
#include <qbytearray.h>
#include <qjsonobject.h>

DartsInput::DartsInput(const QJsonObject &jsonObj)
{
    _point = jsonObj.value("point").toInt(-1);
    _mod = jsonObj.value("mod").toString("");
    _playerName = jsonObj.value("player").toString("");
    _roundIndex = jsonObj.value("roundIndex").toInt();
    _turnId = jsonObj.value("turnId").toInt();
}

DartsInput::DartsInput(const QString &mod, const int &point)
    : _point(point)
    , _mod(mod)
{}

DartsInput::DartsInput() {}

QJsonObject DartsInput::toJsonObject() const
{
    QJsonObject jsonObj;
    jsonObj["point"] = _point;
    jsonObj["mod"] = _mod;
    jsonObj["player"] = _playerName;
    jsonObj["roundIndex"] = _roundIndex;
    jsonObj["turnId"] = _turnId;
    return jsonObj;
}

int DartsInput::point() const
{
    return _point;
}

void DartsInput::setPoint(int point)
{
    _point = point;
}

QString DartsInput::mod() const
{
    return _mod;
}

QString DartsInput::playerName() const
{
    return _playerName;
}

int DartsInput::roundIndex() const
{
    return _roundIndex;
}

int DartsInput::turnId() const
{
    return _turnId;
}

void DartsInput::setTurnId(int newTurnId)
{
    _turnId = newTurnId;
}

void DartsInput::setRoundIndex(int newRoundIndex)
{
    _roundIndex = newRoundIndex;
}

void DartsInput::setPlayerName(const QString &newPlayerName)
{
    _playerName = newPlayerName;
}
