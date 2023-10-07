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
        virtual bool isValid(const QString &mod, const int &point) override;
        virtual bool isWithinBounds(const QString &mod, const int &point) override;
private:
        int inputScore(const QString &mod, const int &point) const;
        int modMultiplier(QString mod) const;

        // Services
        IDartsScores* _scores;

        // Member variables
        const QStringList AllowedMods = std::initializer_list<QString>({"S","D","T"});
        const int MaxPoint = 60;
};

#endif // DARTINPUTEVALUATOR_H
