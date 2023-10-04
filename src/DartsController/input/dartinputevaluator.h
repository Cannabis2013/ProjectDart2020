#ifndef DARTINPUTEVALUATOR_H
#define DARTINPUTEVALUATOR_H

#include "IDartInputEvalutor.h"
#include "src/DartsController/scores/IDartsScores.h"
#include <iostream>
using namespace std;

class DartInputEvaluator : public IDartInputEvaluator
{
public:
    DartInputEvaluator(IDartsScores* scores);
        virtual bool isValid(const DartInput &input) override;
        virtual bool isWithinBounds(const DartInput &input) override;
private:
        int inputScore(const DartInput &input) const;
        int modMultiplier(QString mod) const;

        // Services
        IDartsScores* _scores;

        // Member variables
        const QStringList AllowedMods = std::initializer_list<QString>({"S","D","T"});
        const int MaxPoint = 60;
};

#endif // DARTINPUTEVALUATOR_H
