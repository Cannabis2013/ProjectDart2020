#ifndef DCMETA_H
#define DCMETA_H

#include <quuid.h>

namespace DCBuilding {
    struct DCMeta
    {
        QUuid tournamentId;
        QUuid winnerId;
        int keyPoint;
        int inputHint;
        int displayHint;
    };
}


#endif // DARTSCONTROLLERENTITY_H
