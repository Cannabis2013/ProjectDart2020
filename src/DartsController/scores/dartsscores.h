#ifndef DARTSCORES_H
#define DARTSCORES_H

#include "idartsscores.h"

#include <QList>

class Score;
class ScoresIO;
class IScoresCalculator;
class IDartsInputs;
class IDartsPlayers;
class IDartsIndexes;

class DartsScores : public IDartsScores{
public:
        DartsScores(IDartsIndexes* indexes, IDartsPlayers* players, IDartsInputs* inputs, IScoresCalculator* calculator);
        void init(const int& initialScore) override;
        void initFromFile() override;
        int initialScore() const override;
        virtual void reset() override;
        void update() override;
        DartsPlayerScore score() override;
        DartsPlayerScore score(const QString& name) override;
        DartsPlayerScores scores() override;
        bool saveState() override;

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
