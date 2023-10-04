#ifndef DARTSCORES_H
#define DARTSCORES_H

#include "IDartsScores.h"
#include "src/DartsController/indexes/IDartIndexes.h"
#include "src/DartsController/input/IDartInputs.h"
#include "src/DartsController/players/IDartPlayers.h"

#include <QVector>

class DartsScores : public IDartsScores
{
public:
        DartsScores(IDartIndexes *indexes, IDartPlayers *players, IDartInputs *inputs);
        virtual void init(const int& playersCount) override;
        virtual void reset() override;
        virtual DartScore update(DartInput input) override;
        virtual DartScore update() override;
        virtual int score() override;
        virtual QVector<int> scores() override;
private:
        int totalScore(const QList<DartInput> &inputs);
        int inputScore(const DartInput &input) const;
        int modMultiplier(QString mod) const;

        QVector<int> _scores;

        // Services
        IDartIndexes *_indexes;
        IDartPlayers *_players;
        IDartInputs *_inputs;

};

#endif // DARTSCORES_H
