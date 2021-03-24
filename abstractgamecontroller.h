#ifndef ABSTRACTGAMECONTROLLER_H
#define ABSTRACTGAMECONTROLLER_H

#include <QObject>
#include <quuid.h>
#include "iresponseinterface.h"

class AbstractGameController : public QObject,
        public IResponseInterface<QVariantList>
{
    Q_OBJECT
public slots:
    /*
     * Start/stop game
     */
    virtual void start() = 0;
    virtual void stop() = 0 ;
    /*
     * Recieve and evaluate UI input
     */
    virtual void handleAndProcessUserInput(const int &point, const int &modifierKeyCode) = 0;
    /*
     * Handle requests from UI
     */
    virtual void handleRequestFromUI() = 0;
    /*
     * Undo/redo turn
     */
    virtual QUuid undoTurn() = 0;
    virtual QUuid redoTurn() = 0;

    virtual void handleRequestForCurrentTournamentMetaData() = 0;
    virtual void handleRequestForSingleThrowPlayerScores() = 0;
    virtual void handleRequestFTPPlayerScores() = 0;
    virtual void handleScoreAddedToDataContext(const QUuid &playerID,
                                                      const int &point,
                                                      const int &score) = 0;
    virtual void handleScoreHintUpdated(const QUuid &playerID, const int &point,const int &score) = 0;
    virtual void handleTournamentResetSuccess() = 0;
    virtual void handleResetTournament() = 0;
    /*
     * Set initial state
     */
    virtual void handleWakeUpRequest() = 0;
    /*
     * Handle persist model request
     */
    virtual void handleRequestPersistCurrentState() = 0;
signals:
    void transmitResponse(const int &status, const QVariantList &args) override;
    void sendCurrentTournamentId(const QUuid &tournament);
    void requestFTPScores(const QUuid &tournament);
    void requestTournamentIndexes(const QUuid &tournament);
    void requestAddScore(const QUuid &tournamentID,
                   const QUuid &playerID,
                   const QVector<int> &dataValues,
                   const bool &isWinnerDetermined);
    void winnerDetermined(const QUuid &tournament, const QUuid &player);
    void requestUpdateContext(const QUuid &tournamentID,
                              const int &roundIndex,
                              const int &setIndex);
    void requestSetModelHint(const QUuid &tournament,
                             const QUuid &player,
                             const int &roundIndex,
                             const int &throwIndex,
                             const int &hint);
    void requestResetTournament(const QUuid &tournament);
    void requestPersistModelState();
};

#endif // ABSTRACTGAMECONTROLLER_H
