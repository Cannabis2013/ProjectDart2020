#ifndef DARTSCORES_H
#define DARTSCORES_H

#include "IDartsScores.h"
#include "src/DartsController/indexes/IDartsIndexes.h"
#include "src/DartsController/input/IDartsInputs.h"
#include "src/DartsController/players/IDartPlayers.h"
#include "src/DartsController/scores/DartsInternalScore.h"
#include "src/DartsController/scores/dartsPlayerScore.h"
#include "src/DartsController/scores/scoresio.h"

#include <QMap>
#include <QVector>

class DartsScores : public IDartsScores
{
public:
    DartsScores(IDartsIndexes *indexes, IDartPlayers *players, IDartsInputs *inputs);
        virtual void init() override;
        virtual void initFromFile() override {_scores = _scoresIO->fromFile();}
        virtual void reset() override;
    virtual DartsPlayerScore update(const Input& input) override;
        virtual DartsPlayerScores update() override;
        virtual DartsPlayerScore score() override;
        virtual DartsPlayerScores scores() override {return DartsPlayerScores(_scores);}
private:
            QList<DartsInternalScore> calculatedScores();
            DartsInternalScore calculatedScore(const DartsInputResponse& input, DartsInternalScore &current);
            int inputScore(const QString& mod, const int& point) const;
            int modMultiplier(QString mod) const;

        QList<DartsInternalScore> _scores;

        // Helpers4
        ScoresIO *_scoresIO;

        // Services
        IDartsIndexes *_indexes;
        IDartPlayers *_players;
        IDartsInputs *_inputs;
};

#endif // DARTSCORES_H
