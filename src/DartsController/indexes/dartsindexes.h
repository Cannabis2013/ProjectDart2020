#ifndef DARTINDEXES_H
#define DARTINDEXES_H

#include "IDartsIndexes.h"
#include "dartsindex.h"
#include "src/DartsController/indexes/indexesio.h"

class DartsIndexes : public IDartsIndexes
{
public:
        DartsIndexes();

        void init(const int& playerCount) override;
        void init() override;
        bool next() override;
        bool undo() override;
        bool redo() override;
        bool canUndo() override;
        bool canRedo() override;
        void reset() override;
        virtual int playerIndex() override;
        virtual bool saveState() override;
        int turnIndex() override;
        const DartsTurnIndex index() const override;
private:
        DartsIndex _indexes;

        // Helpers
        IndexesIO *_indexesIO;
};

#endif // DARTINDEXES_H
