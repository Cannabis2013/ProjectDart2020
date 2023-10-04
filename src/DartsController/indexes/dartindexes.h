#ifndef DARTINDEXES_H
#define DARTINDEXES_H

#include "IDartIndexes.h"
#include "dartindex.h"

class DartIndexes : public IDartIndexes
{
public:
        DartIndexes();
        virtual void init(const int& playerCount) override;
        virtual void initFromExternalContext(const int &playerCount) override;
        virtual bool next() override;
        virtual bool previous() override;
        virtual void reset() override;
        virtual int turnIndex() override;
        virtual const DartTurnIndex index() const override;

private:
        void saveIndexes();

        DartIndex _indexes;
        int playersCount;
};

#endif // DARTINDEXES_H
