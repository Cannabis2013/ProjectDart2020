#ifndef DARTSCORES_H
#define DARTSCORES_H

#include "idartsscores.h"
#include "src/DartsController/indexes/idartsindexes.h"
#include "src/DartsController/input/IDartsInputs.h"
#include "src/DartsController/players/idartsplayers.h"
#include "src/DartsController/scores/Score.h"
#include "src/DartsController/scores/dartsPlayerScore.h"
#include "src/DartsController/scores/iscorescalculator.h"
#include "src/DartsController/scores/scoresio.h"

class DartsScores : public IDartsScores{
public:
        DartsScores(IDartsIndexes* indexes, IDartsPlayers* players, IDartsInputs* inputs, IScoresCalculator* calculator);
        void init(const int& initialScore) override;
        void initFromFile() override;
        int initialScore() const override { return _initialScore; }
        virtual void reset() override;
        DartsPlayerScores update() override;
        DartsPlayerScore score() override;
        DartsPlayerScore score(const QString& name) override;
        DartsPlayerScores scores() override {return DartsPlayerScores(_scores);}
        bool saveState() override { return _scoresIO->toFile(_scores, _initialScore); }

private:
        QList<Score> _scores;

        // Helpers
        ScoresIO* _scoresIO;

        // Services
        IDartsIndexes* const _indexes;
        IDartsPlayers* const _players;
        IDartsInputs* const _inputs;
        IScoresCalculator* const _calculator;
        // Member variables
        int _initialScore;
};

#endif // DARTSCORES_H
