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
        DartsScores(const QString& scoresFilename, const QString& initialScoreFilename);

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
        QString _scoresFilename;
        QString _initialScoreFilename;
};

#endif // DARTSCORES_H
