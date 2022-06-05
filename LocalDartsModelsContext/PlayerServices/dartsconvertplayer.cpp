#include "dartsconvertplayer.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <quuid.h>
#include <DartsModelsContext/Models/DartsPlayer.h>

DartsConvertPlayer::Player DartsConvertPlayer::player(const ByteArray &json) const
{
         auto obj = toJsonObject(json);
         return toPlayer(obj);
}

DartsConvertPlayer::Player DartsConvertPlayer::player(const Json &json) const
{
        return toPlayer(json);
}

DartsConvertPlayer::Json DartsConvertPlayer::toJsonObject(const ByteArray &byteArray) const
{
        return QJsonDocument::fromJson(byteArray).object();
}

DartsConvertPlayer::Player DartsConvertPlayer::toPlayer(const Json &json) const
{
        DartsPlayer player;
        player.id = toUuid(json.value("id").toString());
        player.name = json.value("name").toString();
        return player;
}

QUuid DartsConvertPlayer::toUuid(const QString &string) const
{
        return QUuid::fromString(string);
}
