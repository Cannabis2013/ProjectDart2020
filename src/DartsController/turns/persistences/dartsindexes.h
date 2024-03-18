#ifndef DARTINDEXES_H
#define DARTINDEXES_H

#include "idartsindexes.h"
#include "indexesio.h"
#include "src/DartsController/turns/models/dartsindex.h"

class DartsIndexes : public IDartsIndexes {
public:
        DartsIndexes();
        void init(const int& playerCount) override { _indexes = DartsIndex(playerCount); }
        void initFromFile() override { _indexes = _indexesIO->loadIndexes(); }
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
        void nextTurn();
        DartsIndex _indexes;

        // Helpers
        IndexesIO* _indexesIO;
};

#endif // DARTINDEXES_H
