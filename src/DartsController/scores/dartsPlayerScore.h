#ifndef DARTSPLAYERSCORE_H
#define DARTSPLAYERSCORE_H

#include "src/DartsController/scores/DartsInternalScore.h"
#include <QString>
#include <qjsondocument.h>
#include <qjsonobject.h>


class DartsPlayerScore{
public:
        DartsPlayerScore(const QString& playerName, int score) : _playerName(playerName),
                _playerScore(score)
        {}

        DartsPlayerScore(DartsInternalScore score){
                _playerName = score.name();
                _playerScore = score.score();
        }

        DartsPlayerScore(){}

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


#endif // DARTSPLAYERSCORE_H
