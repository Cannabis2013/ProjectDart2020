#ifndef DARTSOVERTHROWEVALUATOR_H
#define DARTSOVERTHROWEVALUATOR_H

#include "abstractdartsevaluator.h"
#include "src/DartsController/players/idartsplayers.h"
#include "src/DartsController/scores/idartsscores.h"
#include "src/DartsController/status/idartsstatus.h"
#include "src/DartsController/validation/abstractdartsevaluator.h"
#include <QList>

class DartsBeginnerValidator : public AbstractDartsEvaluator {
public:
        DartsBeginnerValidator(IDartsScores* scores, IDartsPlayers* players, IDartsStatus* status)
            : _scores(scores)
            , _players(players)
            , _status(status)
        {
        }

        bool evaluateInput(const QString& mod, const int& point) override;
        void evaluateWinnerCondition() override;
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
