#ifndef SCORESCALCULATOR_H
#define SCORESCALCULATOR_H

#include "src/DartsController/scores/iscorescalculator.h"
#include <QStringList>

class DartsCalculator : public IScoresCalculator {
public:
        bool isValid(const int& point, const QString& mod) const override;
        int remaining(const QString& mod, const int& point, const int& current) override;
        Score calculate(const QString& name, const QList<Input>& inputs, const int& initial) override;
        Score calculate(const Input& input, const Score& score, const QString& name) override;
        int score(const QString& mod, const int& point) const override;

private:
        int modMultiplier(QString mod) const;
        const QStringList AllowedMods = std::initializer_list<QString>({ "S", "D", "T" });
        const int MaxPoint = 60;
};

#endif // SCORESCALCULATOR_H
