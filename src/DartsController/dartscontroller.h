#ifndef DARTSCONTROLLER_H
#define DARTSCONTROLLER_H

#include "src/DartsController/Finishes/idartsfinishes.h"
#include "src/DartsController/indexes/IDartsIndexes.h"
#include "src/DartsController/input/IDartsInputEvalutor.h"
#include "src/DartsController/input/IDartsInputs.h"
#include "src/DartsController/responses/IDartsInfoResponse.h"
#include "src/DartsController/scores/IDartsScores.h"
#include "src/DartsController/statistics/idartsstatistics.h"
#include <QObject>
#include <src/DartsController/players/IDartsPlayers.h>

class DartsController : public QObject {
        Q_OBJECT
public:
        DartsController();
        Q_INVOKABLE void init(const QStringList& playerNames);
        Q_INVOKABLE void initFromSaved();
        Q_INVOKABLE void saveState();
        Q_INVOKABLE QByteArray playerScores() const;
        Q_INVOKABLE QStringList playerNames() const;
        Q_INVOKABLE QByteArray turnInfo() const;
        Q_INVOKABLE QByteArray addInput(const QByteArray &inputAsJson);
        Q_INVOKABLE QByteArray undoTurn();
        Q_INVOKABLE QByteArray redoTurn();
private:
        // Services
        IDartsInputEvaluator* _evaluator = nullptr;
        IDartsIndexes* _indexes = nullptr;
        IDartsScores* _scores = nullptr;
        IDartsInputs* _inputs = nullptr;
        IDartsInfoResponse* _response = nullptr;
        IDartsPlayers* _players = nullptr;
        IDartsStatistics* _statistics = nullptr;
        IDartsFinishes* _finishes = nullptr;
};
#endif // FIVEHUNDREDANDONEGAME_H
