#include "dcgetscoresasjson.h"
#include "ServicesProvider/dcservices.h"
#include <qjsonarray.h>
#include <qjsondocument.h>
#include "Models/dcplayer.h"

DCGetScoresAsJson::DCGetScoresAsJson(DCServices *services)
{
    _playerManager = services->playerServices()->playerManager();
    _playerToJson = services->playerServices()->playerToJson();
}

QByteArray DCGetScoresAsJson::get() const
{
    QJsonArray arr;
    auto players = _playerManager->players();
    for (const auto &player : players)
        arr << _playerToJson->convert(player);
    return toByteArray(arr);
}

QByteArray DCGetScoresAsJson::toByteArray(const QJsonArray &arr) const
{
    QJsonDocument jsonDoc(arr);
    auto byteArray = jsonDoc.toJson();
    return byteArray;
}
