#ifndef IDCPLAYERSERVICE_H
#define IDCPLAYERSERVICE_H

#include "idcscoresservice.h"
#include "idcindexservice.h"

class IDCPlayerService
{
public:
    virtual QString currentPlayerName() const = 0;
    virtual QUuid currentPlayerId() const = 0;
};
#endif // IDCPLAYERSERVICE_H
