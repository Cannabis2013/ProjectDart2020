#ifndef DCMETA_H
#define DCMETA_H
#include <quuid.h>
#include <DartsController/DCIndexSLAs/dcindex.h>
struct DCMeta{
    bool entryRestricted;
    int initRemScore;
    int status;
    int playersCount;
    QString playerName;
    QString winnerName;
    QUuid tournamentId;
    DCIndex index;
};
#endif // DCMETAINFO_H
