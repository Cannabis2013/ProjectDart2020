#ifndef DARTINPUTS_H
#define DARTINPUTS_H

#include "IDartInputs.h"
#include "src/DartsController/indexes/IDartIndexes.h"

class DartInputs : public IDartInputs
{
public:
        DartInputs(IDartIndexes *indexes);
        virtual void clear() override;
        virtual bool save(DartInput input) override;
        virtual QList<DartInput> inputs() override;
        virtual QList<DartInput> inputs(const QString& playerName, const int& turnIndex) override;
private:
        bool writeToFile();
        void initFromFile();

        QList<DartInput> _inputs;

        // Services
        IDartIndexes *_indexes;
};

#endif // DARTINPUTS_H
