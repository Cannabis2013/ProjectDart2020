#ifndef DCMETA_H
#define DCMETA_H
#include "dcindex.h"
#include <quuid.h>
struct DCMeta{
    bool entryRestricted;
    int initRemScore;
    int status;
    int playersCount;
    QString playerName;
    QString winnerName;
    QUuid tournamentID;
    DCIndex index;
};
#endif // DCMETAINFO_H
