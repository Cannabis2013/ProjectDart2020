#ifndef IDARTSINFORESPONSE_H
#define IDARTSINFORESPONSE_H

#include <qbytearray.h>

class IDartsInfoResponse
{
public:
        virtual QByteArray currentTurnInfo() = 0;
};

#endif // IDARTSINFORESPONSE_H
