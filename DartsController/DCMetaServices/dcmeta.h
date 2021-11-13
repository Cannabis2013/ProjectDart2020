#ifndef DCMETA_H
#define DCMETA_H
#include <quuid.h>
struct DCMeta{
    QUuid tournamentId;
    int initialRemainingScore;
    int status;
    int inputHint;
    QUuid currentPlayerId;
    QString currentPlayerName;
    QUuid winnerId;
    QString winnerName;
};
#endif // DCMETAINFO_H
