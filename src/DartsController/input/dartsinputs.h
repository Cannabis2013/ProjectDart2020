#ifndef DARTINPUTS_H
#define DARTINPUTS_H

#include "idartsinputs.h"

#include <QList>

class ServiceCollection;
class InputsIO;
class IDartsPlayers;
class IDartsIndexes;

class DartsInputs : public IDartsInputs {
public:
        DartsInputs(ServiceCollection* services);
        void init() override { _inputs = QList<Input>(); }
        void setInputs(const QList<Input>& inputs) override { _inputs = inputs; }
        void initFromFile() override;
        bool anyInputs(const QString& name, const int& throwIndex) const override;
        const QList<Input>& inputs() const override { return _inputs; }
        virtual QList<Input> inputs(const QString& name) const override;
        QList<Input> inputs(const QString& name, const int& throwIndex) const override;
        void remove(const std::function<bool(const Input&)>& predicate) override;
        bool saveState() override;
        Input save(Input input) override;

private:
        QList<Input> _inputs;

        // Services
        ServiceCollection* const _services;
        InputsIO* _inputsIO;
};

#endif // DARTINPUTS_H
