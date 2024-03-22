#ifndef DARTINDEXES_H
#define DARTINDEXES_H

#include "idartsindexes.h"
#include "src/turns/models/dartsindex.h"

class IndexesIO;
class DartsIndexes : public IDartsIndexes {
public:
        DartsIndexes();
        void init() override;
        void initFromFile() override;
        virtual void reset() override;
        void next() override;
        void undo() override;
        void redo() override;
        bool canUndo() override;
        bool canRedo() override;
        bool saveState() override;
        const DartsTurnIndex index() const override;
        void skipturn() override;

private:
        void nextThrow();
        DartsIndex _indexes;

        // Helpers
        IndexesIO* _indexesIO;
};

#endif // DARTINDEXES_H
