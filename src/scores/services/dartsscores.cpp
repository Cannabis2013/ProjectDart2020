#include "dartsscores.h"
#include "qjsondocument.h"
#include "qjsonobject.h"
#include "src/FileIO/filejsonio.h"
#include "src/input/services/idartsinputsfilter.h"
#include "src/players/services/iplayerfetcher.h"
#include "src/servicecollection.h"

DartsScores::DartsScores(ServiceCollection *services,const QString& initialScoreFilename)
    :  _initialScoreFilename(initialScoreFilename), _services(services)
{
}

int modMultiplier(QString mod)
{
    if(mod == "S")
        return 1;
    else if(mod == "D")
        return 2;
    else
        return 3;
}

void DartsScores::initFromStorage()
{
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

bool DartsScores::saveState()
{
    QJsonObject obj;
    obj["initialScore"] = _initialScore;
    return FileJsonIO("initialScore.dat").write(obj);
}

int DartsScores::readInitialScoreFromStorage()
{
    auto jsonDoc = FileJsonIO("initialScore.dat").readAsJson();
    if (!jsonDoc.isObject())
        return 0;
    return jsonDoc.object().value("initialScore").toInt(0);
}

int DartsScores::playerScore(const QString &name) const
{
    auto initialScore = _services->scores->initialScore();
    auto inputs = _services->inputsFilter->valids(name);
    auto score = calcScore(inputs);
    auto result = initialScore - score;
    return result;
}

int DartsScores::calcRemaining(const DartsInput &input, const int &current) {
    auto scoreValue = input.point() * modMultiplier(input.mod());
    return current - scoreValue;
}

int DartsScores::calcScore(const DartsInput &input) const {
    return input.point() * modMultiplier(input.mod());
}

int DartsScores::calcScore(const QList<DartsInput> &inputs) const {
    auto score = 0;
    for (const auto &input : inputs)
        score += calcScore(input);
    return !inputs.isEmpty() ? score : 0;
}
