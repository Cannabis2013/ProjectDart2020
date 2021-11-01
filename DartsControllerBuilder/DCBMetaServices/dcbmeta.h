#ifndef DCBMETA_H
#define DCBMETA_H
#include <quuid.h>
struct DCBMeta
{
    QUuid tournamentId;
    QUuid winnerId;
    int keyPoint;
    int inputHint;
};


#endif // DARTSCONTROLLERENTITY_H
