#ifndef DARTINDEXES_H
#define DARTINDEXES_H

#include "IDartsIndexes.h"
#include "dartsindex.h"

class DartsIndexes : public IDartsIndexes
{
public:
        DartsIndexes();
        virtual void init(const int& playerCount) override;
        virtual void init() override;
        virtual bool next() override;
        virtual bool undo() override;
        virtual bool redo() override;
        virtual bool canUndo() override;
        virtual bool canRedo() override;
        virtual void reset() override;
        virtual int turnIndex() override;
        virtual const DartTurnIndex index() const override;

private:
        void saveIndexes();

        DartsIndex _indexes;
};

#endif // DARTINDEXES_H
