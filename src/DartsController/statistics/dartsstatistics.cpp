#include "dartsstatistics.h"
#include <QJsonArray>
#include <QJsonDocument>

DartsStatistics::DartsStatistics(IDartsInputs* inputs, IDartsScores* scores, IDartsIndexes* indexes, IDartsPlayers* players, IScoresCalculator* calculator)
    : _inputs(inputs)
    , _scores(scores)
    , _indexes(indexes)
    , _players(players)
    , _calculator(calculator)
{
}

QByteArray DartsStatistics::report() const
{
        QJsonArray arr;
        auto names = _players->names();
        for (const auto& name : std::as_const(names))
                arr << statistics(name).toJsonobject();
        return QJsonDocument(arr).toJson(QJsonDocument::Compact);
}

Statistics DartsStatistics::statistics(const QString& name) const
{
        auto score = _scores->score(name);
        auto inputs = getInputs(name);
        auto avg = average(_scores->initialScore(), score.playerScore(), inputs.count());
        auto low = lowest(inputs);
        auto high = highest(inputs);
        return Statistics(name, avg, low, high);
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
