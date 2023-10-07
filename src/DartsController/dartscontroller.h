#ifndef DARTSCONTROLLER_H
#define DARTSCONTROLLER_H

#include <QObject>
#include <src/DartsController/players/IDartPlayers.h>
#include "src/DartsController/indexes/IDartsIndexes.h"
#include "src/DartsController/input/IDartInputEvalutor.h"
#include "src/DartsController/input/IDartsInputs.h"
#include "src/DartsController/responses/IDartsInfoResponse.h"
#include "src/DartsController/scores/IDartsScores.h"

class DartsController : public QObject {
        Q_OBJECT
public:
        DartsController();
        Q_INVOKABLE void init(const QStringList& playerNames);
        Q_INVOKABLE void initFromSaved();
        Q_INVOKABLE QByteArray playerScores() const;
        Q_INVOKABLE QStringList playerNames() const;
        Q_INVOKABLE QByteArray turnInfo() const;
        Q_INVOKABLE QByteArray addInput(const QByteArray &inputAsJson);
        Q_INVOKABLE QByteArray undoTurn();
        Q_INVOKABLE QByteArray redoTurn();
private:
        // Services
        IDartInputEvaluator *_evaluator = nullptr;
        IDartsIndexes *_indexes = nullptr;
        IDartsScores *_scores = nullptr;
        IDartsInputs *_inputs = nullptr;
        IDartsInfoResponse *_response = nullptr;
        IDartPlayers *_players = nullptr;
};
#endif // FIVEHUNDREDANDONEGAME_H
