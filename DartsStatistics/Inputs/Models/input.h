#ifndef INPUT_H
#define INPUT_H
#include <qstring.h>
#include "Players/Models/currentstats.h"
struct Input
{
    QString name;
    int score;
    int keyCode;
    CurrentStats stats;
};

#endif // INPUT_H
