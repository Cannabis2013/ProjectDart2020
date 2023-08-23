#ifndef SNAPSHOT_H
#define SNAPSHOT_H
#include <qstring.h>

#include <DartsStatistics/Contracts/Players/Models/playerstats.h>

struct SnapShot
{
        QString name;
        int score;
        int keyCode;
        PlayerStats stats;
};

#endif // INPUT_H
