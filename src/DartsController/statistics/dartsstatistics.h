#ifndef DARTSSTATISTICS_H
#define DARTSSTATISTICS_H

#include "idartsstatistics.h"
#include "src/DartsController/indexes/idartsindexes.h"
#include "src/DartsController/input/IDartsInputs.h"
#include "src/DartsController/players/idartsplayers.h"
#include "src/DartsController/scores/idartsscores.h"
#include "src/DartsController/scores/iscorescalculator.h"
#include "src/DartsController/statistics/statistics.h"

class DartsStatistics : public IDartsStatistics {
public:
        DartsStatistics(IDartsInputs* inputs,
            IDartsScores* scores,
            IDartsIndexes* indexes,
            IDartsPlayers* players,
            IScoresCalculator* calculator);
        QByteArray report() const override;

private:
        // Private member methods
        Statistics statistics(const QString& name) const;
        QList<Input> getInputs(const QString& name) const;
        double average(int initialScore, int score, int count) const;
        int lowest(const QList<Input>& inputs) const;
        int highest(const QList<Input>& inputs) const;

        // Services
        IDartsInputs* const _inputs;
        IDartsScores * const _scores;
        IDartsIndexes* const _indexes;
        IDartsPlayers* const _players;
        IScoresCalculator* const _calculator;
};

#endif // DARTSSTATISTICS_H
