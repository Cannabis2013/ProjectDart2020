#ifndef DARTSCORES_H
#define DARTSCORES_H

#include "idartsscores.h"

#include <QList>

class ServiceCollection;
class Score;
class ScoresIO;
class IScoresCalculator;
class IDartsInputs;
class IDartsPlayers;
class IDartsIndexes;

class DartsScores : public IDartsScores{
public:
        DartsScores(ServiceCollection* services);
        void init(const int& initialScore) override;
        void initFromFile() override;
        int initialScore() const override;
        virtual void reset() override;
        void update() override;
        Score score() override;
        Score score(const QString& name) override;
        QList<Score> scores() override;
        bool saveState() override;

private:
        QList<Score> _scores;

        // Helpers
        ScoresIO* _scoresIO;

        // Services
        ServiceCollection* _services;
        // Member variables
        int _initialScore;
};

#endif // DARTSCORES_H
