#ifndef DARTSCORES_H
#define DARTSCORES_H

#include "idartsscores.h"

#include <QString>

class ServiceCollection;
class Score;
class IScoresCalculator;
class IDartsInputs;
class IDartsPlayers;
class IDartsIndexes;

class DartsScores : public IDartsScores{
public:
        DartsScores(ServiceCollection *services,const QString& initialScoreFilename);
        void initFromStorage() override;
        int initialScore() const override;
        void setInitialScore(const int& initialScore) override;
        bool saveState() override;
        int playerScore(const QString& name) const override;
        int calcRemaining(const DartsInput &input, const int &current) override;
        int calcScore(const DartsInput &input) const override;
        int calcScore(const QList<DartsInput> &inputs) const override;

private:
        int readInitialScoreFromStorage();

        // Member variables
        int _initialScore;
        QString _initialScoreFilename;
        ServiceCollection *_services;
};

#endif // DARTSCORES_H
