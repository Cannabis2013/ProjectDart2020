#ifndef DCMETA_H
#define DCMETA_H
#include <quuid.h>
struct DCMeta{
    QUuid tournamentId;
    int initialRemainingScore;
    int status;
    QString playerName;
    QUuid winnerId;
    QString winnerName;
};
#endif // DCMETAINFO_H
