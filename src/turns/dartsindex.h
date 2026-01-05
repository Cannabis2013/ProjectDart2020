#ifndef DARTINDEX_H
#define DARTINDEX_H

#include "qjsonobject.h"
#include <qbytearray.h>
#include <qjsondocument.h>

class DartsIndex {
public:
  DartsIndex (const QByteArray &json)
  {
    auto jsonDoc = QJsonDocument::fromJson (json);
    auto jsonObj = jsonDoc.object ();
    playersCount = jsonObj.value("playersCount").toInt(2);
    playerIndex = jsonObj.value("turnIndex").toInt();
    turnCount = jsonObj.value ("totalTurns").toInt ();
    roundIndex = jsonObj.value ("roundIndex").toInt ();
    throwCount = jsonObj.value ("currentThrows").toInt ();
    availableThrows = jsonObj.value ("totalThrows").toInt ();
  }

  DartsIndex (const int& playersCount) {
      this->playersCount = playersCount;
  }

  DartsIndex(){}

  QByteArray
  toJson () const
  {
    QJsonObject jsonObj;
    jsonObj["playersCount"] = playersCount;
    jsonObj["turnIndex"] = playerIndex;
    jsonObj["totalTurns"] = turnCount;
    jsonObj["roundIndex"] = roundIndex;
    jsonObj["currentThrows"] = throwCount;
    jsonObj["totalThrows"] = availableThrows;
    auto jsonDoc = new QJsonDocument (jsonObj);
    return jsonDoc->toJson (QJsonDocument::Compact);
  }

  int playersCount = 2;
  int playerIndex = 0;
  int turnCount = 0;
  int roundIndex = 1;
  int throwCount = 0;
  int availableThrows = 0;
};

#endif // DARTINDEX_H
