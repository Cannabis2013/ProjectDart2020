#ifndef DIPTVALS_H
#define DIPTVALS_H
#include <quuid.h>
struct DIptVals
{
    int point = -1;
    int score = -1;
    int min = -1;
    int max = -1;
    double mid = -1;
    int roundIndex = 0;
    int setIndex = 0;
    int attempt = 0;
    int modKeyCode = -1;
    int remainingScore = -1;
    bool inGame = false;
    bool approved = false;
    QString playerName;
};
#endif // DIPTVALS_H
