#ifndef PLAYERSTAT_H
#define PLAYERSTAT_H
#include <qstring.h>
namespace Statistics {
    struct PlayerStat;
}
struct PlayerStat
{
    QString name;
    int accumulatedScore = 0;
    int n; // The index of player inputs. Ex. : n = 2, if player has made 2 inputs.
    int min; // Minimum score
    int mid; // Middle score
    int max; // Maximum score
    int q1; // First quartile
    int q2; // Median
    int q3; // Third quartile
    double fRatio; // Total number of terminal finishes divided by the total number of possible finishes
};
#endif // PLAYERSTAT_H
