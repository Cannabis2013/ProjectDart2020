#include "dartsplayer.h"

DartsPlayer::DartsPlayer() { }

DartsPlayer::DartsPlayer(const QString& name)
    : _name(name)
{
}

DartsPlayer::DartsPlayer(const QString& name, const QString& url, const QString& nationality)
    : _name(name)
    , _winnerImageUrl(url)
    , _nationality(nationality)
{
}

DartsPlayer::DartsPlayer(const QJsonObject& jsonObj)
{
        _name = jsonObj.value("name").toString("");
        _winner = jsonObj.value("winner").toBool();
        _winnerImageUrl = jsonObj.value("winnerImage").toString("");
}

QJsonObject DartsPlayer::jsonObject() const
{
        QJsonObject jsonObj;
        jsonObj["name"] = _name;
        jsonObj["winner"] = _winner;
        jsonObj["winnerImage"] = _winnerImageUrl;
        jsonObj["nationality"] = _nationality;
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

QString DartsPlayer::winnerImageUrl() const
{
        return _winnerImageUrl;
}
