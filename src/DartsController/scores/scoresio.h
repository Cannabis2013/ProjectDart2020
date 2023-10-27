#ifndef PLAYERSCORESINIT_H
#define PLAYERSCORESINIT_H

#include "src/DartsController/scores/Score.h"
#include "src/DartsController/scores/dartsinitialvalues.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

class ScoresIO{
public:
        ScoresIO(const QString& filePath);
        DartsInitialValues fromFile();

        bool toFile(const QList<Score>& scores, const int& initialValue);

private:
        DartsInitialValues toValues(const QJsonObject& jsonObj);
        QByteArray toJson(const QList<Score>& scores, const int& initialValue);

        QJsonObject toObject(const QByteArray& json);
        QJsonArray toArray(const QList<Score>& scores);

        bool jsonToFile(const QByteArray& json, const QString& filePath);

        QByteArray jsonFromFile(const QString& filePath);

        QList<Score> toScores(const QJsonArray& jsonArr);

        const QString _filePath;
};

#endif // PLAYERSCORESINIT_H
