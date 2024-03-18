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
        bool anyInputs(const QString& name, const int& throwIndex) const override;
        QList<Input> all() const override;
        virtual QList<Input> inputs(const QString& name) const override;
        QList<Input> inputs(const QString& name, const int& throwIndex) const override;
        bool saveState() override;

private:
        QList<Input> _inputs;

        // Services
        InputsIO* _inputsIO;
};

#endif // DARTINPUTS_H
