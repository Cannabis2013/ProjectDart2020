#ifndef STATS_H
#define STATS_H
#include <qstring.h>
struct Stats
{
    QString name;
    int min; // Minimum score
    int mid; // Middle score
    int max; // Maximum score
    int q1; // First quartile
    int q2; // Median
    int q3; // Third quartile
    double fRatio; // Total number of finishes divided by the total number of possible finishes
};

#endif // STATS_H
