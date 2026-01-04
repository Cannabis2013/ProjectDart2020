#include "dartsreminings.h"
#include "qjsondocument.h"
#include "qjsonobject.h"
#include "src/FileIO/filejsonio.h"
#include "src/input/services/idartsinputsfilter.h"
#include "src/servicecollection.h"

DartsReminings::DartsReminings(ServiceCollection *services,const QString& initialScoreFilename)
    :  _filename(initialScoreFilename), _services(services)
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

void DartsReminings::initFromStorage()
{
    _initialRemaining = readRemainingFromFile();
}

int DartsReminings::initialRemaining() const
{
    return _initialRemaining;
}

void DartsReminings::setInitialRemaining(const int& initialScore)
{
    _initialRemaining = initialScore;
}

bool DartsReminings::saveState()
{
    QJsonObject obj;
    obj["initialScore"] = _initialRemaining;
    return FileJsonIO("initialScore.dat").write(obj);
}

int DartsReminings::readRemainingFromFile()
{
    auto jsonDoc = FileJsonIO("initialScore.dat").readAsJson();
    if (!jsonDoc.isObject())
        return 0;
    return jsonDoc.object().value("initialScore").toInt(0);
}

int DartsReminings::fromPlayerName(const QString &name) const
{
    auto initialScore = _services->scores->initialRemaining();
    auto inputs = _services->inputsFilter->valids(name);
    auto score = calculateRemaining(inputs);
    auto result = initialScore - score;
    return result >= 0 ? result : 0;
}

int DartsReminings::inputValue(const DartsInput &input) const
{
    return input.point() * modMultiplier(input.mod());
}

int DartsReminings::calculateRemaining(const QList<DartsInput> &inputs) const {
    auto score = 0;
    for (const auto &input : inputs)
        score += inputValue(input);
    return !inputs.isEmpty() ? score : 0;
}
