#ifndef PLAYERSCORESINIT_H
#define PLAYERSCORESINIT_H

#include "qvector.h"
#include "src/FileIO/filejsonio.h"

#include <QJsonArray>
#include <QJsonDocument>

class ScoresIO{
public:
        ScoresIO(const QString &filePath):
                _filePath((filePath)){
        }
        QVector<int> fromFile(){
                auto json = jsonFromFile(_filePath);
                auto jsonArr = toJsonArray(json);
                return toScores(jsonArr);
        }

        bool toFile(const QVector<int> &scores){
                auto json = toJson(scores);
                return jsonToFile(json,_filePath);
        }

private:
        QByteArray toJson(const QVector<int> &scores){
                QJsonArray jsonArr;
                for (const auto &score : qAsConst(scores))
                        jsonArr << score;
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

        QVector<int> toScores(const  QJsonArray &jsonArr){
                QVector<int> scores;
                for (const auto &value : jsonArr)
                        scores << value.toInt(-1);
                return scores;
        }

        const QString _filePath;
};

#endif // PLAYERSCORESINIT_H
