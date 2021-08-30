#ifndef IDPCINDEXES_H
#define IDPCINDEXES_H

#include "ijson.h"
#include <qbytearray.h>

namespace DPCContext
{
    class IDPCIndexes : public IJson<QByteArray>
    {
    public:
        virtual int totalTurns() const = 0;
        virtual int turnIndex() const = 0;
        virtual int roundIndex() const = 0;
        virtual int setIndex() const = 0;
        virtual int attemptIndex() const = 0;
        virtual QByteArray toJson() const override = 0;
    };
}


#endif // IDARTSSINGLEATTEMPTINDEXES_H
