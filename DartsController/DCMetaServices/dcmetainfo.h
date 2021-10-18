#ifndef DCMETAINFO_H
#define DCMETAINFO_H

#include <quuid.h>

struct DCMetaInfo{
    QUuid tournamentId;
    QUuid currentPlayerId;
    QString currentPlayerName;
    QUuid winnerId;
    QString winnerName;
};
#endif // DCMETAINFO_H
