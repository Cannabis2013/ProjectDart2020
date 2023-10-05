#ifndef TURNINFO_H
#define TURNINFO_H

#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qstring.h>

class TurnInfo
{
public:
        TurnInfo(const QString& currentPlayer, int currentScore,
                 bool canUndo, bool canRedo) :
                _currentPlayer(currentPlayer),
                _currentScore(currentScore),
                _canUndo(canUndo),
                _canRedo(canRedo)
        {}

        int currentScore() const
        {
                return _currentScore;
        }

        QString currentPlayer() const
        {
                return _currentPlayer;
        }

        QByteArray toJson(){
                QJsonObject jsonObj;
                jsonObj["currentPlayer"] = _currentPlayer;
                jsonObj["currentPlayerScore"] = _currentScore;
                jsonObj["type"] = "turnInfo";
                jsonObj["canUndo"] = _canUndo;
                jsonObj["canRedo"] = _canRedo;
                auto jsonDoc = new QJsonDocument(jsonObj);
                return jsonDoc->toJson(QJsonDocument::Compact);
        }

private:
        QString _currentPlayer;
        int _currentScore;
        bool _canUndo;
        bool _canRedo;
};

#endif // TURNINFO_H
