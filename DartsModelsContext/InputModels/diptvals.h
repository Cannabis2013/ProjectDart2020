#ifndef DIPTVALS_H
#define DIPTVALS_H
#include <quuid.h>
struct DIptVals
{
    int point = 0;
    int score = 0;
    int min;
    int max;
    double mid;
    int roundIndex = 0;
    int setIndex = 0;
    int attempt = 0;
    int modKeyCode;
    int remainingScore;
    bool inGame = false;
    bool approved = false;
    QString playerName;
};
#endif // DIPTVALS_H
