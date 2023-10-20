#ifndef DARTINPUTEVALUATOR_H
#define DARTINPUTEVALUATOR_H

#include "idartsevaluator.h"
#include "src/DartsController/players/IDartsPlayers.h"
#include "src/DartsController/scores/IDartsScores.h"
#include "src/DartsController/status/IDartsStatus.h"
#include <iostream>

using namespace std;

class DartsOfficialValidator : public IDartsEvaluator {
public:
        DartsOfficialValidator(IDartsScores* scores, IDartsPlayers* players, IDartsStatus* status)
            : _scores(scores)
            , _players(players)
            , _status(status)
        {
        }
        bool evaluatorInput(const QString& mod, const int& point) override;
        virtual void evaluateScoreCondition() override;

private:
        bool isValid(const QString& mod, const int& point);
        bool isWithinBounds(const int& remainingScore);
        bool isWinnerShot(const int& remainingScore, const QString& mod, const int& point);
        int remainingScore(const QString& mod, const int& point) const;
        int inputScore(const QString &mod, const int &point) const;
        int modMultiplier(QString mod) const;
        bool validEndThrow(const QString& mod, const int& point) const;

        // Services
        IDartsScores* const _scores;
        IDartsPlayers* const _players;
        IDartsStatus* const _status;

        // Member variables
        const QStringList AllowedMods = std::initializer_list<QString>({"S","D","T"});
        const int MaxPoint = 60;
};

#endif // DARTINPUTEVALUATOR_H
