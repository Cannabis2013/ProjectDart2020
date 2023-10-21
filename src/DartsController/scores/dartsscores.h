#ifndef DARTSCORES_H
#define DARTSCORES_H

#include "idartsscores.h"
#include "src/DartsController/indexes/IDartsIndexes.h"
#include "src/DartsController/input/IDartsInputs.h"
#include "src/DartsController/players/idartsplayers.h"
#include "src/DartsController/scores/Score.h"
#include "src/DartsController/scores/dartsPlayerScore.h"
#include "src/DartsController/scores/scoresio.h"

class DartsScores : public IDartsScores
{
public:
        DartsScores(IDartsIndexes* indexes,
            IDartsPlayers* players,
            IDartsInputs* inputs)
            : _indexes(indexes)
            , _players(players)
            , _inputs(inputs)
        {
                _scoresIO = new ScoresIO("playerScores.dat");
        }
        void init() override;
        void initFromFile() override;
        void reset() override;
        int initialScore() const override;
        DartsPlayerScores update() override;
        DartsPlayerScore score() override;
        DartsPlayerScore score(const QString& name) override;
        DartsPlayerScores scores() override {return DartsPlayerScores(_scores);}
        bool saveState() override;

private:
        QList<Score> _scores;

        // Helpers
        ScoresIO* _scoresIO;

        // Services
        IDartsIndexes* const _indexes;
        IDartsPlayers* const _players;
        IDartsInputs* const _inputs;
};

#endif // DARTSCORES_H
