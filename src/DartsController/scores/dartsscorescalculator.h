#ifndef DARTSSCORESCALCULATOR_H
#define DARTSSCORESCALCULATOR_H


#include "src/DartsController/indexes/IDartsIndexes.h"
#include "src/DartsController/input/IDartInputs.h"
#include "src/DartsController/players/IDartPlayers.h"
#include "src/DartsController/scores/DartsInternalScore.h"
class DartsScoresCalculator
{
public:
        DartsScoresCalculator(IDartsIndexes *indexes, IDartPlayers *players,IDartInputs *inputs);
        QList<DartsInternalScore> calculatedScores();
        DartsInternalScore calculatedScore(const DartsInput &input, DartsInternalScore &current);
private:
        int inputScore(const DartsInput &input) const;
        int modMultiplier(QString mod) const;

        IDartsIndexes *_indexes;
        IDartPlayers *_players;
        IDartInputs *_inputs;
};

#endif // DARTSSCORESCALCULATOR_H
