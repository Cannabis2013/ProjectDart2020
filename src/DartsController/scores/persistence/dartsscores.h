#ifndef DARTSCORES_H
#define DARTSCORES_H

#include "idartsscores.h"

class ServiceCollection;
class Score;
class IScoresCalculator;
class IDartsInputs;
class IDartsPlayers;
class IDartsIndexes;

class DartsScores : public IDartsScores{
public:
        void initFromStorage() override;
        int initialScore() const override;
        void setInitialScore(const int& initialScore) override;
        void setScores(const QList<Score>& scores) override;
        QList<Score> all() override;
        bool saveState() override;

private:
        QList<Score> _scores;
        QList<Score> readScoresFromStorage();
        int readInitialScoreFromStorage();

        // Member variables
        int _initialScore;
};

#endif // DARTSCORES_H
