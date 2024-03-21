#ifndef ISTATSCALCULATOR_H
#define ISTATSCALCULATOR_H

class QString;

class IStatsCalculator {
public:
        virtual double middle(const QString& name) const = 0;
        virtual int lowest(const QString& name) const = 0;
        virtual int highest(const QString& name) const = 0;
};

#endif // ISTATSCALCULATOR_H
