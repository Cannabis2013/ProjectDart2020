#ifndef IDARTINDEXES_H
#define IDARTINDEXES_H

class DartsTurnIndex;

class IDartsIndexes {
public:
        virtual void init() = 0;
        virtual void initFromFile() = 0;
        virtual void reset() = 0;
        virtual void next() = 0;
        virtual void skipturn() = 0;
        virtual void undo() = 0;
        virtual void redo() = 0;
        virtual bool canUndo() = 0;
        virtual bool canRedo() = 0;
        virtual bool saveState() = 0;
        virtual const DartsTurnIndex index() const = 0;
};

#endif // IDARTINDEXES_H
