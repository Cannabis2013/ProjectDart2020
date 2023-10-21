#ifndef DARTINDEXES_H
#define DARTINDEXES_H

#include "IDartsIndexes.h"
#include "dartsindex.h"
#include "src/DartsController/indexes/indexesio.h"

    class DartsIndexes : public IDartsIndexes {
public:
        DartsIndexes();

        void init(const int& playerCount) override;
        void initFromFile() override;
        bool next() override;
        bool undo() override;
        bool redo() override;
        bool canUndo() override;
        bool canRedo() override;
        virtual bool saveState() override;
        const DartsTurnIndex index() const override;
        virtual void skipturn() override;

private:
        void nextTurn();
        DartsIndex _indexes;

        // Helpers
        IndexesIO* _indexesIO;
};

#endif // DARTINDEXES_H
