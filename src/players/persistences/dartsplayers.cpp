#include <QJsonArray>
#include <QJsonValue>
#include <QRandomGenerator>
#include "dartsplayers.h"
#include "src/FileIO/filejsonio.h"
#include <qjsondocument.h>

DartsPlayers::DartsPlayers(const QString& filepath)
    : _storagePath(filepath)
{
  _available = std::initializer_list<DartsPlayer>{
    {"Van Gerwen", "qrc:/pictures/Ressources/Pictures/VanGerwin.gif", "NL"},
    {"Peter Wright", "qrc:/pictures/Ressources/Pictures/SnakeBite.png", "EN"},
    {"Luke Littler", "qrc:/pictures/Ressources/Pictures/lukeLittler.gif", "EN"},
    {"Gerwin Price", "qrc:/pictures/Ressources/Pictures/gerwinPrice.gif", "EN"},
    {"Luke Humphries", "qrc:/pictures/Ressources/Pictures/lukeHumphries.gif", "EN"},
    {"Benjamin Drue Reus", "qrc:/pictures/Ressources/Pictures/benjamin.jpeg", "DK"}};
}

void DartsPlayers::init(const QStringList &names)
{
  _players.clear();
  for (const auto &name : names) {
    for (const auto &player : std::as_const(_available)) {
      if (player.name() == name)
        _players.append(player);
    }
  }
}

void DartsPlayers::initFromFile()
{
    QList<DartsPlayer> players;
    auto jsonDoc = FileJsonIO(_storagePath).readAsJson();
    if (!jsonDoc.isArray())
      return;
    const auto arr = jsonDoc.array();
    for (const auto &jsonObj : arr)
      players << DartsPlayer(jsonObj.toObject());
    _players = players;
}

QList<DartsPlayer>& DartsPlayers::all()
{
    return _players;
}

bool DartsPlayers::saveState()
{
  QJsonArray arr;
  for (auto &player : _players)
    arr.append(player.jsonObject());
  return FileJsonIO(_storagePath).write(arr);
}

QList<DartsPlayer> &DartsPlayers::available()
{
  return _available;
}

int DartsPlayers::count()
{
  return _players.count();
}
