#ifndef PLAYERSCORESINIT_H
#define PLAYERSCORESINIT_H

#include "src/DartsController/scores/DartsInternalScore.h"
#include "src/FileIO/filejsonio.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

class ScoresIO{
public:
        ScoresIO(const QString &filePath):
                _filePath((filePath)){
        }
        QList<DartsInternalScore> fromFile(){
                auto json = jsonFromFile(_filePath);
                auto jsonArr = toJsonArray(json);
                return toScores(jsonArr);
        }

        bool toFile(const QList<DartsInternalScore> &scores){
                auto json = toJson(scores);
                return jsonToFile(json,_filePath);
        }

private:
        QByteArray toJson(const QList<DartsInternalScore> &scores){
                QJsonArray jsonArr;
                for (const auto &score : qAsConst(scores))
                        jsonArr << score.toJsonObject();
                auto jsonDoc = new QJsonDocument(jsonArr);
                return jsonDoc->toJson(QJsonDocument::Compact);
        }

        bool jsonToFile(const QByteArray &json, const QString &filePath){
                FileJsonIO out(filePath);
                return out.write(json);
        }

        QByteArray jsonFromFile(const QString &filePath){
                FileJsonIO in(filePath);
                return in.read();
        }

        QJsonArray toJsonArray(const QByteArray &json) const{
                auto jsonDoc = QJsonDocument::fromJson(json);
                if(!jsonDoc.isArray())
                        return QJsonArray();
                return jsonDoc.array();
        }

        QList<DartsInternalScore> toScores(const  QJsonArray &jsonArr){
                QList<DartsInternalScore> scores;
                for (const auto &value : jsonArr)
                        scores << DartsInternalScore(value.toObject());
                return scores;
        }

        const QString _filePath;
};

#endif // PLAYERSCORESINIT_H
