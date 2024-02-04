#include "dartsstatistics.h"

#include "src/DartsController/indexes/idartsindexes.h"
#include "src/DartsController/input/idartsinputs.h"
#include "src/DartsController/scores/dartsPlayerScore.h"
#include "src/DartsController/scores/idartsscores.h"
#include "src/DartsController/scores/iscorescalculator.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QList>

DartsStatistics::DartsStatistics(IDartsInputs* inputs,
    IDartsScores* scores, IDartsIndexes* indexes, IScoresCalculator* calculator)
    : _inputs(inputs)
    , _scores(scores)
    , _indexes(indexes)
    , _calculator(calculator)
{
}

QJsonObject DartsStatistics::report(const QString& name) const
{
        QJsonObject jsonObj;
        auto score = _scores->score(name);
        auto inputs = getInputs(name);
        jsonObj["average"] = average(_scores->initialScore(), score.playerScore(), inputs.count());
        jsonObj["low"] = lowest(inputs);
        jsonObj["high"] = highest(inputs);
        jsonObj["throwCount"] = inputs.size();
        jsonObj["name"] = name;
        return jsonObj;
}

QList<Input> DartsStatistics::getInputs(const QString& name) const
{
        auto throwIndex = _indexes->index().throwIndex();
        return _inputs->inputs(name, throwIndex);
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
        if (inputs.count() <= 0)
                return 0;
        auto lowest = 60;
        for (const auto &input : inputs) {
                auto score = _calculator->score(input.mod(), input.point());
                lowest = score < lowest ? score : lowest;
        }
        return lowest;
}

int DartsStatistics::highest(const QList<Input>& inputs) const
{
        auto highest = 0;
        for (const auto &input : inputs) {
                auto score = _calculator->score(input.mod(), input.point());
                highest = score > highest ? score : highest;
        }
        return highest;
}
