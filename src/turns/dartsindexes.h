#ifndef DARTINDEXES_H
#define DARTINDEXES_H

#include "idartsindexes.h"
#include "src/turns/dartsindex.h"

class IndexesIO;
class DartsIndexes : public IDartsIndexes {
public:
        DartsIndexes();
        void init(const int& playersCount) override;
        void initFromFile() override;
        virtual void reset() override;
        void next() override;
        void undo() override;
        void redo() override;
        bool canUndo() override;
        bool canRedo() override;
        bool saveState() override;
        const DartsTurnIndex index() const override;

private:
        void nextThrow();
        DartsIndex _indexes;
        int _playersCount;

        // Helpers
        IndexesIO* _indexesIO;
};

#endif // DARTINDEXES_H
