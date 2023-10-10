#ifndef DARTINPUTEVALUATOR_H
#define DARTINPUTEVALUATOR_H

#include "IDartsInputEvalutor.h"
#include "src/DartsController/scores/IDartsScores.h"
#include <iostream>
using namespace std;

class DartsInputEvaluator : public IDartsInputEvaluator
{
public:
        DartsInputEvaluator(IDartsScores* scores);
        virtual bool isValid(const QString &mod, const int &point) override;
        virtual bool isWithinBounds(const QString &mod, const int &point) override;

private:
        int inputScore(const QString &mod, const int &point) const;
        int modMultiplier(QString mod) const;
        bool validEndThrow(const QString& mod, const int& point) const;

        // Services
        IDartsScores* _scores;

        // Member variables
        const QStringList AllowedMods = std::initializer_list<QString>({"S","D","T"});
        const int MaxPoint = 60;
};

#endif // DARTINPUTEVALUATOR_H
