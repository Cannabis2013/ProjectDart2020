#ifndef DCINITIALIZECONTROLLER_H
#define DCINITIALIZECONTROLLER_H
#include <qvector.h>
#include "InitSLAs/idcinitialize.h"
#include "Models/dcinput.h"
#include "Models/dcplayer.h"
#include "Models/dcmeta.h"
class DCServices;
class DCInitializeController : public IDCInitialize
{
public:
    // Typedefinitions
    typedef QVector<DCPlayer> Players;
    typedef QVector<DCInput> Inputs;
    // Constructor
    DCInitializeController(DCServices *services);
    // Load method
    void init(const QUuid &tournamentId, AbsDartsCtx *ctx) override;
    // Getters
private:
    void initMeta(const DCMeta &meta);
    void initPlayerDetails(const QVector<DCPlayer> &players, const DCMeta &meta);
    void initScores(const QVector<DCInput> &inputs);
    void initStatus();
    QVector<DCPlayer> updatePlayers(const QVector<DCPlayer> &players, const int &remScore);
    DCMeta _meta;
    Players _players;
    Inputs _inputs;
    DCServices *_services;
};

#endif // DCLOADMODELS_H
