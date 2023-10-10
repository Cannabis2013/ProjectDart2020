#ifndef IDARTINDEXES_H
#define IDARTINDEXES_H

#include "DartsTurnIndex.h"

class IDartsIndexes
{
public:
        virtual void init(const int &playerCount) = 0;
        virtual void init() = 0;
        virtual bool next() = 0;
        virtual void skipturn() = 0;
        virtual bool undo() = 0;
        virtual bool redo() = 0;
        virtual bool canUndo() = 0;
        virtual bool canRedo() = 0;
        virtual bool saveState() = 0;
        virtual const DartsTurnIndex index() const = 0;
};

#endif // IDARTINDEXES_H
