#ifndef DCINDEX_H
#define DCINDEX_H

#include <qjsondocument.h>
#include <qjsonobject.h>

struct DCIndex
{
    int totalTurns = 0;
    int turnIndex = 0;
    int roundIndex = 1;
    int setIndex = 0;
    int attemptIndex = 0;
};
#endif // DARTSSINGLEATTEMPTINDEXES_H
