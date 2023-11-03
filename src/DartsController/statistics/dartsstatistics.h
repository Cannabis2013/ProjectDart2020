#ifndef DARTSSTATISTICS_H
#define DARTSSTATISTICS_H

#include "idartsstatistics.h"
#include "src/DartsController/indexes/idartsindexes.h"
#include "src/DartsController/input/IDartsInputs.h"
#include "src/DartsController/scores/idartsscores.h"

class DartsStatistics : public IDartsStatistics {
public:
        DartsStatistics(IDartsInputs* inputs, IDartsScores* scores, IDartsIndexes* indexes);

        virtual Statistics statistics(const QString& name) const override;

private:
        QList<Input> getInputs(const QString& name) const;
        double average(int initialScore, int score, int count) const;
        int lowest(const QList<Input>& inputs) const;
        int highest(const QList<Input>& inputs) const;
        int scoreValue(const QString& mod, const int& point) const;
        int modMultiplier(QString mod) const;

        // Services
        IDartsInputs* const _inputs;
        IDartsScores * const _scores;
        IDartsIndexes* const _indexes;
};

#endif // DARTSSTATISTICS_H
