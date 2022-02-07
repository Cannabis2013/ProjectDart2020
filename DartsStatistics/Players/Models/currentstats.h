#ifndef CURRENTSTATS_H
#define CURRENTSTATS_H
#include <qstring.h>
namespace Statistics {
    struct PlayerStat;
}
struct CurrentStats
{
    QString name;
    int accScore = -1;
    int n = 0; // The index of player inputs. Ex. : n = 2, if player has made 2 inputs.
    int min = -1; // Minimum score
    int mid = -1; // Middle score
    int max = -1; // Maximum score
    int q1 = -1; // First quartile
    int q2 = -1; // Median
    int q3 = -1; // Third quartile
    double fRatio = 0.0; // Total number of terminal finishes divided by the total number of possible finishes
};
#endif // PLAYERSTAT_H
