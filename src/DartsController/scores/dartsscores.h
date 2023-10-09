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
#include <QMap>
#include <QVector>

class DartsScores : public IDartsScores
{
public:
        DartsScores(IDartsIndexes *indexes, IDartsPlayers *players, IDartsInputs *inputs);
        void init() override;
        void initFromFile() override {_scores = _scoresIO->fromFile();}
        void reset() override;
        DartsPlayerScore update(const Input& input) override;
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
        IDartsIndexes *_indexes;
        IDartsPlayers* _players;
};

#endif // DARTSCORES_H
