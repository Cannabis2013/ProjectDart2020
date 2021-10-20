#ifndef DCINPUTSTATS_H
#define DCINPUTSTATS_H
#include <quuid.h>
struct DCInputStat{
    QUuid id;
    int lowest = 0;
    int highest = 0;
    double average = 0;
};
#endif // DCINPUTSTATS_H
