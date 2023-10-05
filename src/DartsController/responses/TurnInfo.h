#ifndef TURNINFO_H
#define TURNINFO_H

#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qstring.h>

class TurnInfo
{
public:
        TurnInfo(const QString& currentPlayer,
                 bool canUndo, bool canRedo) :
                _currentPlayer(currentPlayer),
                _canUndo(canUndo),
                _canRedo(canRedo)
        {}

        QString currentPlayer() const
        {
                return _currentPlayer;
        }

        QByteArray toJson(){
                QJsonObject jsonObj;
                jsonObj["currentPlayerName"] = _currentPlayer;
                jsonObj["type"] = "turnInfo";
                jsonObj["canUndo"] = _canUndo;
                jsonObj["canRedo"] = _canRedo;
                auto jsonDoc = new QJsonDocument(jsonObj);
                return jsonDoc->toJson(QJsonDocument::Compact);
        }

private:
        QString _currentPlayer;
        bool _canUndo;
        bool _canRedo;
};

#endif // TURNINFO_H
