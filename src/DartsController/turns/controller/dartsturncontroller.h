#ifndef DARTSTURNCONTROLLER_H
#define DARTSTURNCONTROLLER_H

#include "iturncontroller.h"

#include <QObject>

class ServiceCollection;
class IDartsStatus;
class IDartsInputTrimmer;
class IDartsInputs;
class IDartsPlayers;
class IDartsScores;
class IDartsIndexes;

class DartsTurnController : public QObject, public ITurnController {
        Q_OBJECT
public:
        DartsTurnController(ServiceCollection* services);

        Q_INVOKABLE void undo() override;
        Q_INVOKABLE void redo() override;
        Q_INVOKABLE void skip() override;
        Q_INVOKABLE bool canUndo() const override;
        Q_INVOKABLE bool canRedo() const override;
        Q_INVOKABLE int playerTurn() const override;
        Q_INVOKABLE int playerNumber() const override;

private:
        void undoTurn();
        void redoTurn();

        // Services
        ServiceCollection* const _services;
};

#endif // DARTSTURNCONTROLLER_H
