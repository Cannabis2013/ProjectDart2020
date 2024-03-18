#include "dartsstatistics.h"
#include "src/DartsController/input/models/Input.h"
#include "src/DartsController/input/services/idartsinputsfilter.h"
#include "src/DartsController/players/models/dartsplayer.h"
#include "src/DartsController/players/persistences/idartsplayers.h"
#include "src/DartsController/scores/models/Score.h"
#include "src/DartsController/scores/persistence/idartsscores.h"
#include "src/DartsController/scores/services/idartsscoresfetch.h"
#include "src/DartsController/scores/services/iscorescalculator.h"
#include "src/DartsController/servicecollection.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QList>

DartsStatistics::DartsStatistics(ServiceCollection* services)
    : _services(services)
{
}

QByteArray DartsStatistics::playerOne() const
{
        auto players = _services->players->all();
        auto name = players.first().name();
        auto obj = playerReport(name);
        return QJsonDocument(obj).toJson(QJsonDocument::Compact);
}

QByteArray DartsStatistics::playerTwo() const
{
        auto players = _services->players->all();
        auto name = players.last().name();
        auto obj = playerReport(name);
        return QJsonDocument(obj).toJson(QJsonDocument::Compact);
}

QJsonObject DartsStatistics::playerReport(const QString& name) const
{
        QJsonObject jsonObj;
        auto score = _services->scoresFetch->score(name);
        auto playerInputs = _services->inputsFilter->validFromName(name);
        jsonObj["average"] = average(_services->scores->initialScore(), score.value(), playerInputs.count());
        jsonObj["low"] = lowest(playerInputs);
        jsonObj["high"] = highest(playerInputs);
        jsonObj["throwCount"] = playerInputs.size();
        jsonObj["name"] = name;
        return jsonObj;
}

double DartsStatistics::average(int initialScore, int score, int count) const
{
        if (count <= 0)
                return 0;
        auto playerPoints = initialScore - score;
        auto avg = (double)playerPoints * 3 / count;
        int quantizied = avg * 100;
        return (double)quantizied / 100;
}

int DartsStatistics::lowest(const QList<Input>& inputs) const
{
        if (inputs.length() < 3)
                return 0;
        auto lowest = 180;
        auto sum = 0;
        for (int index = 0; index < inputs.length(); ++index) {
                auto input = inputs.at(index);
                auto score = _services->calculator->score(input.mod(), input.point());
                sum += score;
                if ((index + 1) % 3 == 0) {
                        lowest = sum < lowest ? sum : lowest;
                        sum = 0;
                }
        }
        return lowest;
}

int DartsStatistics::highest(const QList<Input>& inputs) const
{
        if (inputs.length() < 3)
                return 0;
        auto highest = 0;
        auto sum = 0;
        for (int index = 0; index < inputs.length(); ++index) {
                auto input = inputs.at(index);
                auto score = _services->calculator->score(input.mod(), input.point());
                sum += score;
                if ((index + 1) % 3 == 0) {
                        highest = sum > highest ? sum : highest;
                        sum = 0;
                }
        }
        return highest;
}
