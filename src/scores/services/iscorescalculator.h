#ifndef ISCORESCALCULATOR_H
#define ISCORESCALCULATOR_H

// QTC_TEMP
template <typename t>
class QList;
class DartsInput;
class QString;
class Score;

class IScoresCalculator {
public:
    virtual int score(const QList<DartsInput> &inputs) const = 0;
    virtual int score(const DartsInput &input) const = 0;
    virtual int remaining(const DartsInput &input, const int &current) = 0;
    virtual Score calculate(const QString &name, const QList<DartsInput> &inputs, const int &initial)
        = 0;
};

#endif // ISCORESCALCULATOR_H
