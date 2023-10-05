#ifndef DARTSCORES_H
#define DARTSCORES_H

#include "IDartsScores.h"
#include "src/DartsController/indexes/IDartsIndexes.h"
#include "src/DartsController/input/IDartInputs.h"
#include "src/DartsController/players/IDartPlayers.h"
#include "src/DartsController/scores/scoresio.h"

#include <QVector>

class DartsScores : public IDartsScores
{
public:
    DartsScores(IDartsIndexes *indexes, IDartPlayers *players, IDartInputs *inputs);
        virtual void init(const int& playersCount) override;
        virtual void init() override;
        virtual void reset() override;
        virtual DartsScore update(DartInput input) override;
        virtual DartsScore update() override;
        virtual DartsScore score() override;
        virtual QVector<int> scores() override;
private:
        int totalScore(const QList<DartInput> &inputs);
        int inputScore(const DartInput &input) const;
        int modMultiplier(QString mod) const;

        QVector<int> _scores;

        // Helpers
        ScoresIO *_scoresIO;

        // Services
        IDartsIndexes *_indexes;
        IDartPlayers *_players;
        IDartInputs *_inputs;
};

#endif // DARTSCORES_H
