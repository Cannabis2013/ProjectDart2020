#ifndef DCMETA_H
#define DCMETA_H
#include <quuid.h>
struct DCMeta{
    QUuid tournamentId;
    int initRemScore;
    int status;
    QString playerName;
    QString winnerName;
};
#endif // DCMETAINFO_H
