#ifndef DCSTATSMODEL_H
#define DCSTATSMODEL_H
#include <quuid.h>
struct DCStatsModel{
    QString name;
    int min = -1;
    int max = -1;
    double middle = 0;
};
#endif // DCPLAYERSTATS_H
