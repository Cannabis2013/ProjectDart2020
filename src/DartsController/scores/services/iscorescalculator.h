#ifndef ISCORESCALCULATOR_H
#define ISCORESCALCULATOR_H

// QTC_TEMP
template <typename t>
class QList;
class Input;
class QString;
class Score;

class IScoresCalculator {
public:
        virtual int score(const QString& mod, const int& point) const = 0;
        virtual int remaining(const QString& mod, const int& point, const int& current) = 0;
        virtual Score calculate(const QString& name, const QList<Input>& inputs, const int& initial) = 0;
};

#endif // ISCORESCALCULATOR_H