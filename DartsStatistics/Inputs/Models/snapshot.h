#ifndef SNAPSHOT_H
#define SNAPSHOT_H
#include <qstring.h>
#include "Players/Models/currentstats.h"
struct SnapShot
{
    QString name;
    int score;
    int keyCode;
    CurrentStat stats;
};

#endif // INPUT_H
