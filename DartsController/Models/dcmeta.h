#ifndef DCMETA_H
#define DCMETA_H
#include "dcindex.h"
#include "dcinput.h"
#include <quuid.h>
struct DCMeta{
    int initRemScore;
    int status;
    int playersCount;
    QString playerName;
    QString winnerName;
    QUuid tournamentID;
    DCIndex index;
    DCInput lastInput;
};
#endif // DCMETAINFO_H
