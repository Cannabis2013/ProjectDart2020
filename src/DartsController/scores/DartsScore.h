#ifndef DARTSCORE_H
#define DARTSCORE_H

#include <QJsonDocument>
#include <qjsonobject.h>
#include <qstring.h>

class DartsScore
{
public:
        DartsScore(const QString& playerName, int score) : _playerName(playerName),
                _playerScore(score)
        {}

        DartsScore(){}

        int playerScore() const
        {
                return _playerScore;
        }

        QString playerName() const
        {
                return _playerName;
        }

        QByteArray toJson(){
                QJsonObject jsonObj;
                jsonObj["playerName"] = _playerName;
                jsonObj["playerScore"] = _playerScore;
                auto jsonDoc = new QJsonDocument(jsonObj);
                return jsonDoc->toJson(QJsonDocument::Compact);
        }

private:
        QString _playerName;
        int _playerScore;
};

#endif // DARTSCORE_H
