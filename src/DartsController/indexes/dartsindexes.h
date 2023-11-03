#ifndef DARTINDEXES_H
#define DARTINDEXES_H

#include "idartsindexes.h"
#include "dartsindex.h"
#include "src/DartsController/indexes/indexesio.h"

class DartsIndexes : public IDartsIndexes {
public:
        DartsIndexes() { _indexesIO = new IndexesIO("indexes.dat"); }

        void init(const int& playerCount) override { _indexes = DartsIndex(playerCount); }
        void initFromFile() override { _indexes = _indexesIO->loadIndexes(); }
        virtual void reset() override;
        bool next() override;
        bool undo() override;
        bool redo() override;
        bool canUndo() override { return _indexes.throwIndex > 0; }
        bool canRedo() override { return _indexes.throwIndex < _indexes.totalTurns; }
        virtual bool saveState() override { return _indexesIO->saveIndexes(_indexes); }
        const DartsTurnIndex index() const override { return DartsTurnIndex(_indexes); }
        virtual void skipturn() override;

private:
        void nextTurn();
        DartsIndex _indexes;

        // Helpers
        IndexesIO* _indexesIO;
};

#endif // DARTINDEXES_H
