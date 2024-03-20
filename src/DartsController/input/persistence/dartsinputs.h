#ifndef DARTINPUTS_H
#define DARTINPUTS_H

#include "idartsinputs.h"

class ServiceCollection;
class InputsIO;
class IDartsPlayers;
class IDartsIndexes;

class DartsInputs : public IDartsInputs {
public:
        DartsInputs();
        void init() override { _inputs = QList<Input>(); }
        void setInputs(const QList<Input>& inputs) override { _inputs = inputs; }
        void initFromFile() override;
        QList<Input> all() const override;
        bool saveState() override;

private:
        QList<Input> _inputs;
};

#endif // DARTINPUTS_H
