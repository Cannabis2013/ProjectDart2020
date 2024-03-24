#ifndef DARTINPUTS_H
#define DARTINPUTS_H

#include "idartsinputs.h"

class ServiceCollection;
class InputsIO;
class IDartsPlayers;
class IDartsIndexes;

class DartsInputs : public IDartsInputs {
public:
        DartsInputs(const QString& filename);
        void init() override;
        void setInputs(const QList<DartsInput>& inputs) override;
        void initFromFile() override;
        QList<DartsInput> all() const override;
        bool saveState() override;

private:
        QList<DartsInput> _inputs;
        QString _filename;
};

#endif // DARTINPUTS_H
