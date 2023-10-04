#ifndef DARTSCONTROLLER_H
#define DARTSCONTROLLER_H

#include <QObject>
#include <src/DartsController/players/IDartPlayers.h>
#include "src/DartsController/indexes/IDartIndexes.h"
#include "src/DartsController/input/IDartInputEvalutor.h"
#include "src/DartsController/input/IDartInputs.h"
#include "src/DartsController/responses/IDartsInfoResponse.h"
#include "src/DartsController/scores/IDartsScores.h"

class DartsController : public QObject {
        Q_OBJECT
public:
        DartsController();
        Q_INVOKABLE void init(const QStringList& playerNames);
        Q_INVOKABLE void initFromSaved();
        Q_INVOKABLE QByteArray initialValues() const;
        Q_INVOKABLE QStringList playerNames() const;
        Q_INVOKABLE QByteArray turnInfo() const;
        Q_INVOKABLE QByteArray addInput(const QByteArray &inputAsJson);
        Q_INVOKABLE QByteArray undoTurn();
        Q_INVOKABLE QByteArray redoTurn();
        Q_INVOKABLE bool reset();
private:
        // Services
        IDartInputEvaluator *_evaluator = nullptr;
        IDartIndexes *_indexes = nullptr;
        IDartsScores *_scores = nullptr;
        IDartInputs *_inputs = nullptr;
        IDartsInfoResponse *_response = nullptr;
        IDartPlayers *_players = nullptr;
};
#endif // FIVEHUNDREDANDONEGAME_H
