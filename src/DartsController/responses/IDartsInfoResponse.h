#ifndef IDARTSINFORESPONSE_H
#define IDARTSINFORESPONSE_H

#include "TurnInfo.h"
#include <qbytearray.h>

class IDartsInfoResponse
{
public:
        virtual TurnInfo currentTurnInfo() = 0;
};

#endif // IDARTSINFORESPONSE_H
