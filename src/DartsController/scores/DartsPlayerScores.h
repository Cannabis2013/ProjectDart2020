#ifndef DARTSCORE_H
#define DARTSCORE_H

#include "src/DartsController/scores/Score.h"
#include <QJsonDocument>
#include <qjsonobject.h>
#include <QJsonArray>
#include <qstring.h>

class DartsPlayerScores
{
public:
    DartsPlayerScores(const QList<Score> &scores) :
                _playerScores(scores)
        {}

        DartsPlayerScores(){}

        QByteArray toJson(){
                QJsonArray jsonArr;
                for (const auto& score : std::as_const(_playerScores))
                        jsonArr << score.toJsonObject();
                auto jsonDoc = new QJsonDocument(jsonArr);
                return jsonDoc->toJson(QJsonDocument::Compact);
        }

        const QList<Score>& playerScores()
        {
                return _playerScores;
        }
private:
        QList<Score> _playerScores;
};

#endif // DARTSCORE_H
