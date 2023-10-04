#ifndef IDARTINDEXES_H
#define IDARTINDEXES_H

#include "DartTurnIndex.h"

class IDartIndexes
{
public:
        virtual void init(const int &playerCount) = 0;
        virtual void initFromExternalContext(const int &playerCount) = 0;
        virtual bool next() = 0;
        virtual bool previous() = 0;
        virtual int turnIndex() = 0;
        virtual void reset() = 0;
    virtual const DartTurnIndex index() const = 0;
};

#endif // IDARTINDEXES_H
