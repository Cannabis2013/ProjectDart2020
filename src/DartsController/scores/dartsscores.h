#ifndef DARTSCORES_H
#define DARTSCORES_H

#include "IDartsScores.h"
#include "src/DartsController/indexes/IDartsIndexes.h"
#include "src/DartsController/input/IDartInputs.h"
#include "src/DartsController/players/IDartPlayers.h"
#include "src/DartsController/scores/DartsInternalScore.h"
#include "src/DartsController/scores/dartsPlayerScore.h"
#include "src/DartsController/scores/dartsscorescalculator.h"
#include "src/DartsController/scores/scoresio.h"

#include <QMap>
#include <QVector>

class DartsScores : public IDartsScores
{
public:
    DartsScores(IDartsIndexes *indexes, IDartPlayers *players, IDartInputs *inputs);
        virtual void init() override;
        virtual void initFromFile() override {_scores = _scoresIO->fromFile();}
        virtual void reset() override;
        virtual DartsPlayerScore update(DartsInput input) override;
        virtual DartsPlayerScores update() override;
        virtual DartsPlayerScore score() override;
        virtual DartsPlayerScores scores() override {return DartsPlayerScores(_scores);}
private:
        QList<DartsInternalScore> _scores;

        // Helpers
        DartsScoresCalculator *_calculator;
        ScoresIO *_scoresIO;

        // Services
        IDartsIndexes *_indexes;
        IDartPlayers *_players;
        IDartInputs *_inputs;
};

#endif // DARTSCORES_H
