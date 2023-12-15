#ifndef DARTINPUTEVALUATOR_H
#define DARTINPUTEVALUATOR_H

#include "idartsevaluator.h"
#include "src/DartsController/players/idartsplayers.h"
#include "src/DartsController/scores/idartsscores.h"
#include "src/DartsController/status/idartsstatus.h"
#include <QPair>
#include <iostream>

using namespace std;

class DartsProfessionalEvaluator : public IDartsEvaluator {
public:
        DartsProfessionalEvaluator(IDartsScores* scores, IDartsPlayers* players, IDartsStatus* status)
            : _scores(scores)
            , _players(players)
            , _status(status)
        {
        }
        void init() override;
        bool evaluateInput(const QString& mod, const int& point) override;
        void evaluateScoreCondition() override;

private:
        bool isAllowed(const QString& mod);
        bool isValid(const QString& mod, const int& point);
        bool isWithinBounds(const int& remainingScore);
        int remainingScore(const QString& mod, const int& point) const;
        int modMultiplier(QString mod) const;

        // Services
        IDartsScores* const _scores;
        IDartsPlayers* const _players;
        IDartsStatus* const _status;

        // Member variables
        const QStringList AllowedMods = std::initializer_list<QString>({"S","D","T"});
        const int MaxPoint = 60;
        QList<QPair<QString, bool>> allowances;
};

#endif // DARTINPUTEVALUATOR_H
