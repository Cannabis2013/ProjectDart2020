#ifndef DARTSSTATSREPORT_H
#define DARTSSTATSREPORT_H

#include "istatsreport.h"

template <typename T>
class QList;
class Input;
class IScoresCalculator;
class IDartsIndexes;
class IDartsScores;
class IDartsInputs;
class IDartsPlayers;
class QJsonArray;
class QJsonObject;
class QString;

class DartsStatsReport : public IStatsReport {
public:
        DartsStatsReport(IDartsInputs* inputs,
            IDartsScores* scores,
            IDartsIndexes* indexes,
            IScoresCalculator* calculator,
            IDartsPlayers* players);
        QJsonArray report() const;

private:
        // Private member methods
        QJsonObject playerReport(const QString& name) const;
        QList<Input> getInputs(const QString& name) const;
        double average(int initialScore, int score, int count) const;
        int lowest(const QList<Input>& inputs) const;
        int highest(const QList<Input>& inputs) const;

        // Services
        IDartsInputs* const _inputs;
        IDartsScores * const _scores;
        IDartsIndexes* const _indexes;
        IScoresCalculator* const _calculator;
        IDartsPlayers* const _players;
};

#endif // DARTSSTATSREPORT_H
