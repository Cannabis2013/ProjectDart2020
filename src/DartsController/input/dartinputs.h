#ifndef DARTINPUTS_H
#define DARTINPUTS_H

#include "IDartInputs.h"
#include "src/DartsController/indexes/IDartsIndexes.h"
#include "src/DartsController/input/inputsio.h"

class DartInputs : public IDartInputs
{
public:
    DartInputs(IDartsIndexes *indexes);
        virtual void init() override;
        virtual void clear() override;
        virtual bool save(DartInput input) override;
        virtual QList<DartInput> inputs() override;
        virtual QList<DartInput> inputs(const QString& playerName, const int& turnIndex) override;
private:

        QList<DartInput> _inputs;

        // Services
        IDartsIndexes *_indexes;
        InputsIO *_inputsIO;
};

#endif // DARTINPUTS_H
