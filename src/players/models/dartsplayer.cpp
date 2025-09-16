#include "dartsplayer.h"

DartsPlayer::DartsPlayer() { }

DartsPlayer::DartsPlayer(const QString& name)
    : _name(name)
{}

DartsPlayer::DartsPlayer(const QJsonObject& jsonObj)
{
        _name = jsonObj.value("name").toString("");
        _winner = jsonObj.value("winner").toBool();
}

QJsonObject DartsPlayer::jsonObject() const
{
        QJsonObject jsonObj;
        jsonObj["name"] = _name;
        jsonObj["winner"] = _winner;
        return jsonObj;
}

QString DartsPlayer::name() const
{
        return _name;
}

bool DartsPlayer::winner() const
{
        return _winner;
}

void DartsPlayer::setWinner(bool status)
{
        _winner = status;
}
