#ifndef FTPCONTROLLER_H
#define FTPCONTROLLER_H

#include "abstractgamecontroller.h"

/*
 * This class is more like a signal interface that ftp based tournaments derive
 */


class AbstractDartsController : public AbstractGameController
{
    Q_OBJECT
public slots:
    virtual void initializeControllerIndexes(const QByteArray&) = 0;
    virtual void initializeControllerPlayerDetails(const QByteArray&) = 0;
    virtual void initializeControllerWinnerIdAndName(const QByteArray&) = 0;
    virtual void undoSuccess(const QByteArray&) = 0;
    virtual void redoSuccess(const QByteArray&) = 0;
signals:
    void isReadyAndAwaitsInput(const QByteArray& json);
    void requestDartsTournamentDetails(const QUuid& tournamentId);
    void initializedAndAwaitsInput(const bool& canUndo,
                                   const bool& canRedo,
                                   const int& roundIndex,
                                   const int& setIndex,
                                   const int& attemptIndex,
                                   const int& score,
                                   const QString& targetRow);
    void controllerInitializedAndReady();
    void requestDartsTournamentIndexes(const QUuid &tournament);
    void controllerInitialized(const int &displayHint);
};

#endif // FTPCONTROLLER_H
