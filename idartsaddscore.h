#ifndef IDARTSADDSCORE_H
#define IDARTSADDSCORE_H

#include <idcscoresservice.h>
#include <quuid.h>

class IDartsAddScore
{
public:
    virtual int addPlayerScore(const QUuid& id, const int &score, IDCScoresService *scoresService) const = 0;
};

#endif // IDARTSADDSCORE_H
