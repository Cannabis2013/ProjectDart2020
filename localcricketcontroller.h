#ifndef LOCALCRICKETCONTROLLER_H
#define LOCALCRICKETCONTROLLER_H

#include "abstractgamecontroller.h"

class LocalCricketController : public AbstractGameController
{
public:
    LocalCricketController();

    // AbstractGameController interface
public slots:
    virtual void start() override;
    virtual void stop() override;
    virtual void handleAndProcessUserInput(const QByteArray &json) override;
    virtual void handleRequestFromUI() override;
    virtual QUuid undoTurn() override;
    virtual QUuid redoTurn() override;
    virtual void handleRequestForCurrentTournamentMetaData() override;
    virtual void handleScoreAddedToDataContext(const QByteArray &json) override;
    virtual void handleScoreHintUpdated(const QByteArray &) override;
    virtual void handleResetTournament() override;
    virtual void beginInitialize() override;
    virtual void handleRequestPersistCurrentState() override;
};

#endif // LOCALCRICKETCONTROLLER_H
