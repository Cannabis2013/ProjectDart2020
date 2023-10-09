#ifndef DARTSSTATISTICS_H
#define DARTSSTATISTICS_H

#include "idartsstatistics.h"
#include "src/DartsController/input/IDartsInputs.h"
#include "src/DartsController/players/IDartsPlayers.h"
#include "src/DartsController/scores/IDartsScores.h"

class DartsStatistics : public IDartsStatistics {
public:
        DartsStatistics(IDartsInputs* inputs, IDartsPlayers* players, IDartsScores* scores);

        virtual double average() override;
        virtual int lowest() override;
        virtual int highest() override;
private:
        int scoreValue(const QString& mod, const int& point) const;
        int modMultiplier(QString mod) const;

        // Services
        IDartsInputs * const _inputs;
        IDartsPlayers * const _players;
        IDartsScores * const _scores;
};

#endif // DARTSSTATISTICS_H
