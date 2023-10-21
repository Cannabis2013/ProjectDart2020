#ifndef DARTSCONTROLLER_H
#define DARTSCONTROLLER_H

#include "src/DartsController/Finishes/dartsfinishes.h"
#include "src/DartsController/Finishes/idartsfinishes.h"
#include "src/DartsController/indexes/IDartsIndexes.h"
#include "src/DartsController/indexes/dartsindexes.h"
#include "src/DartsController/input/IDartsInputs.h"
#include "src/DartsController/input/dartsinputadder.h"
#include "src/DartsController/input/dartsinputs.h"
#include "src/DartsController/input/idartsinputadder.h"
#include "src/DartsController/players/dartsplayers.h"
#include "src/DartsController/responses/idartsinforesponse.h"
#include "src/DartsController/scores/dartsscores.h"
#include "src/DartsController/scores/idartsscores.h"
#include "src/DartsController/statistics/dartsstatistics.h"
#include "src/DartsController/statistics/idartsstatistics.h"
#include "src/DartsController/status/dartsstatus.h"
#include "src/DartsController/status/idartsstatus.h"
#include "src/DartsController/validation/dartsevaluators.h"
#include "src/DartsController/validation/idartsevaluator.h"
#include <QObject>
#include <src/DartsController/players/idartsplayers.h>
#include <src/DartsController/responses/dartsturnvalues.h>

class DartsController : public QObject {
        Q_OBJECT
public:
        DartsController()
        {
                _status = new DartsStatus();
                _indexes = new DartsIndexes();
                _finishes = new DartsFinishes();
                _players = new DartsPlayers(_indexes);
                _inputs = new DartsInputs(_indexes, _players);
                _scores = new DartsScores(_indexes, _players, _inputs);
                _statistics = new DartsStatistics(_inputs, _scores, _indexes);
                _turnValues = new DartsTurnValues(_players, _indexes, _statistics, _finishes, _scores, _status);
                _adder = new DartsInputAdder(_inputs, &_evaluator, _indexes, _status);
                _evaluators = new DartsEvaluators(_scores, _players, _status);
        }
        Q_INVOKABLE void init(const QStringList& playerNames, const int& mode);
        Q_INVOKABLE void initFromSaved();
        Q_INVOKABLE void saveState();
        Q_INVOKABLE QByteArray playerScores() const;
        Q_INVOKABLE QStringList playerNames() const;
        Q_INVOKABLE QByteArray turnInfo() const;
        Q_INVOKABLE void addInput(const QString& mod, const int& point);
        Q_INVOKABLE void undoTurn();
        Q_INVOKABLE void redoTurn();

private:
        // Services
        IDartsEvaluator* _evaluator = nullptr;
        IDartsIndexes* _indexes = nullptr;
        IDartsScores* _scores = nullptr;
        IDartsInputs* _inputs = nullptr;
        IDartsInfoResponse* _turnValues = nullptr;
        IDartsPlayers* _players = nullptr;
        IDartsStatistics* _statistics = nullptr;
        IDartsFinishes* _finishes = nullptr;
        IDartsStatus* _status = nullptr;
        IDartsInputAdder* _adder = nullptr;
        DartsEvaluators* _evaluators = nullptr;
};
#endif // FIVEHUNDREDANDONEGAME_H
