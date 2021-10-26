#ifndef DCPLAYERSTAT_H
#define DCPLAYERSTAT_H
#include <quuid.h>
struct DCPlayerStat{
    QUuid playerId;
    int min = -1;
    int max = -1;
    double middle = 0;
};
#endif // DCPLAYERSTAT_H
