#ifndef IDSCINDEXES_H
#define IDSCINDEXES_H
#include "ijson.h"
#include <qbytearray.h>
namespace DSCContext
{
    class IDSCIndexes : public IJson<QByteArray>
    {
    public:
        virtual int totalTurns() const = 0;
        virtual int turnIndex() const = 0;
        virtual int roundIndex() const = 0;
        virtual int setIndex() const = 0;
        virtual QByteArray toJson() const override = 0;
    };
}

#endif // IDARTSMULTIATTEMPTINDEXES_H
