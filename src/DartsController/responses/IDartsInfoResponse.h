#ifndef IDARTSINFORESPONSE_H
#define IDARTSINFORESPONSE_H

#include "TurnInfo.h"
#include "src/DartsController/responses/winnerInfo.h"

#include <qbytearray.h>

class IDartsInfoResponse
{
public:
        virtual TurnInfo currentTurnInfo() = 0;
        virtual WinnerInfo winnerInfo() = 0;
};

#endif // IDARTSINFORESPONSE_H
