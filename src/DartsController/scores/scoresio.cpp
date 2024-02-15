#include "scoresio.h"
#include "src/FileIO/filejsonio.h"

ScoresIO::ScoresIO(const QString& filePath)
    : _filePath((filePath))
{
}

DartsInitialValues ScoresIO::fromFile()
{
        auto json = jsonFromFile(_filePath);
        auto jsonObj = toObject(json);
        if (jsonObj == QJsonObject())
                return {};
        return toValues(jsonObj);
}

bool ScoresIO::toFile(const QList<Score>& scores, const int& initialValue)
{
        auto json = toJson(scores, initialValue);
        return jsonToFile(json, _filePath);
}

DartsInitialValues ScoresIO::toValues(const QJsonObject& jsonObj)
{
        auto scores = toScores(jsonObj["scores"].toArray());
        auto initialValue = jsonObj["initialValue"].toInt(-1);
        return { scores, initialValue };
}

QByteArray ScoresIO::toJson(const QList<Score>& scores, const int& initialValue)
{
        QJsonObject jsonObj;
        jsonObj["scores"] = toArray(scores);
        jsonObj["initialValue"] = initialValue;
        auto jsonDoc = new QJsonDocument(jsonObj);
        return jsonDoc->toJson(QJsonDocument::Compact);
}

QJsonObject ScoresIO::toObject(const QByteArray& json)
{
        auto jsonDoc = QJsonDocument::fromJson(json);
        if (!jsonDoc.isObject())
                return QJsonObject();
        return jsonDoc.object();
}

QJsonArray ScoresIO::toArray(const QList<Score>& scores)
{
        QJsonArray jsonArr;
        for (const auto& score : scores)
                jsonArr << score.jsonObject();
        return jsonArr;
}

bool ScoresIO::jsonToFile(const QByteArray& json, const QString& filePath)
{
        FileJsonIO out(filePath);
        return out.write(json);
}

QByteArray ScoresIO::jsonFromFile(const QString& filePath)
{
        FileJsonIO in(filePath);
        return in.read();
}

QList<Score> ScoresIO::toScores(const QJsonArray& jsonArr)
{
        QList<Score> scores;
        for (const auto& value : jsonArr)
                scores << Score(value.toObject());
        return scores;
}
