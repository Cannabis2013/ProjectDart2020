#ifndef DCMETA_H
#define DCMETA_H
#include <quuid.h>
struct DCMeta{
    QUuid tournamentId;
    int inputHint;
    int initialRemainingScore;
    int status;
    QUuid currentPlayerId;
    QString currentPlayerName;
    QUuid winnerId;
    QString winnerName;
};
#endif // DCMETAINFO_H
