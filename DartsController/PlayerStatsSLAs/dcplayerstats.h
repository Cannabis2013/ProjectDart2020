#ifndef DCPLAYERSTATS_H
#define DCPLAYERSTATS_H
#include <quuid.h>
struct DCPlayerStats{
    QString name;
    int min = -1;
    int max = -1;
    double middle = 0;
};
#endif // DCPLAYERSTATS_H
