#ifndef DARTSOVERTHROWEVALUATOR_H
#define DARTSOVERTHROWEVALUATOR_H

#include "idartsevaluator.h"
#include "src/DartsController/players/IDartsPlayers.h"
#include "src/DartsController/scores/IDartsScores.h"
#include "src/DartsController/status/IDartsStatus.h"
#include "src/DartsController/validation/idartsevaluator.h"
#include <QList>

class DartsOverthrowEvaluator : public IDartsEvaluator {
public:
        DartsOverthrowEvaluator(IDartsScores* scores, IDartsPlayers* players, IDartsStatus* status)
            : _scores(scores)
            , _players(players)
            , _status(status)
        {
        }

        virtual bool evaluatorInput(const QString& mod, const int& point) override;
        virtual void evaluateScoreCondition() override;

private:
        bool isValid(const QString& mod, const int& point) const;

        // Services
        IDartsScores* const _scores;
        IDartsPlayers* const _players;
        IDartsStatus* const _status;

        // Member variables
        const QStringList AllowedMods = std::initializer_list<QString>({ "S", "D", "T" });
        const int MaxPoint = 60;
};

#endif // DARTSOVERTHROWEVALUATOR_H
