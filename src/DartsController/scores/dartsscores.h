#ifndef DARTSCORES_H
#define DARTSCORES_H

#include "IDartsScores.h"
#include "src/DartsController/indexes/IDartsIndexes.h"
#include "src/DartsController/input/IDartsInputs.h"
#include "src/DartsController/players/IDartsPlayers.h"
#include "src/DartsController/scores/Score.h"
#include "src/DartsController/scores/dartsPlayerScore.h"
#include "src/DartsController/scores/scorescalculator.h"
#include "src/DartsController/scores/scoresio.h"
#include "src/DartsController/status/IDartsStatus.h"
#include <QMap>
#include <QVector>

class DartsScores : public IDartsScores
{
public:
        DartsScores(IDartsIndexes* indexes,
            IDartsPlayers* players,
            IDartsInputs* inputs,
            IDartsStatus* status);
        void init() override;
        void initFromFile() override;
        void reset() override;
        DartsPlayerScore update(const Input& input) override;
        virtual int initialScore() const override;
        DartsPlayerScores update() override;
        DartsPlayerScore score() override;
        DartsPlayerScores scores() override {return DartsPlayerScores(_scores);}
        bool saveState() override;

private:
        QList<Score> _scores;

        // Helpers4
        ScoresIO *_scoresIO;
        ScoresCalculator *_calculator;

        // Services
        IDartsIndexes* const _indexes;
        IDartsPlayers* const _players;
        IDartsStatus* const _status;
};

#endif // DARTSCORES_H
