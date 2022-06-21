#ifndef CURRENTSTAT_H
#define CURRENTSTAT_H

#include <qstring.h>

struct CurrentStat
{
    QString name;
    int accScore = 0;
    int n = 0; // The number of reported throws/scoress. Ex. : n = 2, if player has made 2 inputs.
    int min = 0; // Minimum score
    int mid = 0; // Middle score
    int max = 0; // Maximum score
    int q1 = -1; // First quartile
    int q2 = -1; // Median
    int q3 = -1; // Third quartile
    double fRatio = 0.0; // Total number of terminal finishes divided by the total number of possible finishes
};
#endif // PLAYERSTAT_H
