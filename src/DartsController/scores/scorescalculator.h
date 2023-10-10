#ifndef SCORESCALCULATOR_H
#define SCORESCALCULATOR_H

#include "src/DartsController/input/IDartsInputs.h"
#include "src/DartsController/scores/Score.h"

class ScoresCalculator
{
public:
        ScoresCalculator(IDartsInputs* inputs);

        QList<Score> calculatedScores(const QStringList& names, const int& initialScore, const int& throwIndex);
        Score calculatedScore(const Input& input, const Score& score, const QString& name);
private:
        int inputScore(const QString& mod, const int& point) const;
        int modMultiplier(QString mod) const;
        // Services
        IDartsInputs* const _inputs;
};

#endif // SCORESCALCULATOR_H
