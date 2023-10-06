#ifndef DARTSCORE_H
#define DARTSCORE_H

#include "src/DartsController/scores/DartsInternalScore.h"
#include <QJsonDocument>
#include <qjsonobject.h>
#include <QJsonArray>
#include <qstring.h>

class DartsPlayerScores
{
public:
        DartsPlayerScores(const QList<DartsInternalScore> &scores) :
                _playerScores(scores)
        {}

        DartsPlayerScores(){}

        QByteArray toJson(){
                QJsonArray jsonArr;
                for (const auto &score : qAsConst(_playerScores))
                        jsonArr << score.toJsonObject();
                auto jsonDoc = new QJsonDocument(jsonArr);
                return jsonDoc->toJson(QJsonDocument::Compact);
        }

        const QList<DartsInternalScore> playerScores()
        {
                return _playerScores;
        }
private:
        const QList<DartsInternalScore> _playerScores;
};

#endif // DARTSCORE_H
