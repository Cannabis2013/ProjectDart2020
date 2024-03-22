#ifndef DARTSSCORESUPDATE_H
#define DARTSSCORESUPDATE_H

#include "iscoresupdate.h"
#include "qlist.h"

class ScoresIO;
class Score;
class ServiceCollection;

class DartsScoresUpdate : public IScoresUpdate {
public:
        DartsScoresUpdate(ServiceCollection* services);
        void initPlayerScores(const int& initialScore) override;
        void resetPlayerScores() override;
        void updatePlayerScores() override;

private:
        QList<Score> freshScores(const int& initialScore) const;

        QList<Score> updatedScores(const int& initialScore) const;
        ServiceCollection* const _services;
};

#endif // DARTSSCORESUPDATE_H
