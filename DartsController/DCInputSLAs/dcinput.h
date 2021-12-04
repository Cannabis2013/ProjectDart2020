#ifndef DCINPUT_H
#define DCINPUT_H
#include <QUuid>
struct DCInput
{
    int point = 0;
    int score = 0;
    int modKeyCode = -1;
    int remScore;
    int min = 0;
    int max = 0;
    double mid = 0;
    int roundIndex = 1;
    int setIndex = 0;
    int attempt = 0;
    bool inGame = false;
    bool approved = false;
    QString playerName;
};

#endif // DCINPUT_H
