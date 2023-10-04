#ifndef TURNINFO_H
#define TURNINFO_H

#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qstring.h>

class TurnInfo
{
public:
        TurnInfo(const QString& currentPlayer, int currentScore) :
                _currentPlayer(currentPlayer),
                _currentScore(currentScore)
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
                jsonObj["player"] = _currentPlayer;
                jsonObj["score"] = _currentScore;
                jsonObj["type"] = "turnInfo";
                auto jsonDoc = new QJsonDocument(jsonObj);
                return jsonDoc->toJson(QJsonDocument::Compact);
        }

private:
        QString _currentPlayer;
        int _currentScore;
};

#endif // TURNINFO_H
