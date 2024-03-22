#include "dartsscores.h"
#include "qjsonarray.h"
#include "qjsondocument.h"
#include "src/scores/models/Score.h"
#include "src/FileIO/filejsonio.h"

DartsScores::DartsScores(const QString& scoresFilename, const QString& initialScoreFilename)
    : _scoresFilename(scoresFilename)
    , _initialScoreFilename(initialScoreFilename)
{
}

void DartsScores::initFromStorage()
{
        _scores = readScoresFromStorage();
        _initialScore = readInitialScoreFromStorage();
}

int DartsScores::initialScore() const
{
        return _initialScore;
}

void DartsScores::setInitialScore(const int& initialScore)
{
        _initialScore = initialScore;
}

QList<Score> DartsScores::all()
{
        return _scores;
}

bool DartsScores::saveState()
{
        QJsonArray arr;
        for (const auto& score : _scores)
                arr << score.jsonObject();
        FileJsonIO("scores.dat").writeAsJson(arr);
        QJsonObject obj;
        obj["initialScore"] = _initialScore;
        return FileJsonIO("initialScore.dat").writeAsJson(obj);
}

QList<Score> DartsScores::readScoresFromStorage()
{
        auto jsonDoc = FileJsonIO("scores.dat").readAsJson();
        QList<Score> scores;
        if (!jsonDoc.isArray())
                return scores;
        auto arr = jsonDoc.array();
        for (const auto& jsonVal : arr)
                scores << jsonVal.toObject();
        return scores;
}

int DartsScores::readInitialScoreFromStorage()
{
        auto jsonDoc = FileJsonIO("initialScore.dat").readAsJson();
        if (!jsonDoc.isObject())
                return 0;
        return jsonDoc.object().value("initialScore").toInt(0);
}

void DartsScores::setScores(const QList<Score>& scores)
{
        _scores = scores;
}
